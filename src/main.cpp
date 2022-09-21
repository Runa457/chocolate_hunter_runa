#include "bn_core.h"

#include "Scene.h"
#include "Scene_logo.h"
#include "Scene_title.h"
#include "Scene_game.h"
#include "Scene_option.h"
#include "Scene_credits.h"
#include "Scene_enemylist.h"
#include "Scene_magiclist.h"
#include "Scene_introduction.h"

#include "Status.h"

#include "bn_music.h"
#include "bn_sprite_text_generator.h"
#include "bn_random.h"
#include "bn_regular_bg_actions.h"

#include "common_variable_8x16_sprite_font.h"
#include "bn_regular_bg_items_bg_main.h"

using namespace Runa;

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_bg_priority(0);
    bn::random random_generator;

    /**
     * @brief Game data.
     */
    Status status;
    bn::unique_ptr<Scene::Scene_Root> scene(new Scene::Logo(text_generator));

    bn::optional<bn::regular_bg_ptr> bg_main;
    bn::optional<bn::regular_bg_move_by_action> bg_main_action;

    /**
     * @brief Parameter for changing scene.
     * value is returned from scene->Update function.
     * nullopt - current scene is maintained.
     * else - scene changes.
     */
    bn::optional<Scene::Scene_Type> nextscene;

    /**
     * @brief Scene transition delay time.
     */
    int scene_change_wait = 0;

    while(true)
    {
        if (bg_main && bg_main_action) { bg_main_action->update(); }

        if (scene) nextscene = scene->Update();

        bn::core::update();
        random_generator.update();

        if (nextscene)
        {
            if (scene)
            {
                scene.reset();
                scene_change_wait = 10;
            }

            if (--scene_change_wait) { continue; }

            switch (*nextscene)
            {
            case Scene::Scene_Type::Logo:
                bg_main.reset();
                bg_main_action.reset();
                bn::music::stop();
                scene.reset(new Scene::Logo(text_generator));
                break;
            case Scene::Scene_Type::Title:
                if (!bg_main)
                {
                    bg_main = bn::regular_bg_items::bg_main.create_bg(0, 0);
                    bg_main->set_blending_enabled(false);
                    bg_main->set_visible(true);
                    bg_main->set_priority(3);
                    bg_main_action = bn::regular_bg_move_by_action(*bg_main, -0.5, 0.5);
                }
                scene.reset(new Scene::Title(text_generator));
                break;
            case Scene::Scene_Type::Introduction:
                scene.reset(new Scene::Introduction(text_generator));
                break;
            case Scene::Scene_Type::Main_game:
                bg_main.reset();
                bg_main_action.reset();
                bn::music::stop();
                scene.reset(new Scene::Game(text_generator, random_generator, status));
                break;
            case Scene::Scene_Type::Options:
                scene.reset(new Scene::Option(text_generator, status));
                break;
            case Scene::Scene_Type::Credits:
                scene.reset(new Scene::Credits(text_generator));
                break;
            case Scene::Scene_Type::Enemy_list:
                scene.reset(new Scene::Enemy_list(text_generator, status));
                break;
            case Scene::Scene_Type::Magic_list:
                scene.reset(new Scene::Magic_list(text_generator, status));
                break;
            default:
                BN_ERROR("Unknown Scene type: ", (int)*nextscene);
            }
        }
    }
}
