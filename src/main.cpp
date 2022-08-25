#include "bn_core.h"

#include "Scene.h"
#include "Scene_logo.h"
#include "Scene_title.h"
#include "Scene_game.h"
#include "Scene_option.h"
#include "Scene_credits.h"
#include "Scene_introduction.h"

#include "Status.h"

#include "bn_sprite_text_generator.h"
#include "bn_random.h"

#include "common_variable_8x16_sprite_font.h"

// for debug; from sym_merged <- delete at end
#include <bn_fixed_point.h>
#include <bn_format.h>
#include <bn_keypad.h>
#include <bn_music.h>
#include <bn_sprite_ptr.h>
#include <bn_string.h>
#include <bn_vector.h>
//

using namespace Runa;

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_bg_priority(1);
    bn::random random_generator;

    /**
     * @brief Game data.
     */
    Status status;
    bn::unique_ptr<Scene::Scene_Root> scene(new Scene::Logo(text_generator));

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

// for debug; from sym_merged <- delete at end
    constexpr int IWRAM_BYTES = 32'768, EWRAM_BYTES = 262'144;
    int resourceUsageUpdateCountDown = 1;
    bn::vector<bn::sprite_ptr, 24> resourceUsageSprites;
    bool isDebugViewOn = false;
//

    while(true)
    {
        if (scene) nextscene = scene->Update();

// for debug; from sym_merged <- delete at end
        if (bn::keypad::select_pressed())
        {
            isDebugViewOn = !isDebugViewOn;
            if (!isDebugViewOn)
            {
                resourceUsageSprites.clear();
            }
        }
        if (isDebugViewOn && --resourceUsageUpdateCountDown <= 0)
        {
            text_generator.set_left_alignment();
            resourceUsageSprites.clear();
            text_generator.generate({-120, -70}, bn::format<9>("CPU: {}%", (bn::core::last_cpu_usage() * 100).integer()),
                              resourceUsageSprites);

            const int iwramUsedPercent =
                (bn::fixed(bn::memory::used_static_iwram() + bn::memory::used_stack_iwram()) / IWRAM_BYTES * 100)
                    .integer();
            const int ewramUsedPercent =
                (bn::fixed(EWRAM_BYTES - bn::memory::available_alloc_ewram()) / EWRAM_BYTES * 100).integer();
            const int iwramFree = IWRAM_BYTES - bn::memory::used_static_iwram() - bn::memory::used_stack_iwram();
            const int ewramFree = bn::memory::available_alloc_ewram();

            text_generator.generate({-120, -58}, bn::format<20>("IW: {}% {}", iwramUsedPercent, iwramFree),
                              resourceUsageSprites);
            text_generator.generate({-120, -46},
                              bn::format<20>("EW: {}% {}", ewramUsedPercent, ewramFree), resourceUsageSprites);
            resourceUsageUpdateCountDown = 5;
        }
//

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
                scene.reset(new Scene::Logo(text_generator));
                break;
            case Scene::Scene_Type::Title:
                scene.reset(new Scene::Title(text_generator));
                break;
            case Scene::Scene_Type::Introduction:
                scene.reset(new Scene::Introduction(text_generator));
                break;
            case Scene::Scene_Type::Main_game:
                scene.reset(new Scene::Game(text_generator, random_generator, status));
                break;
            case Scene::Scene_Type::Options:
                scene.reset(new Scene::Option(text_generator, status));
                break;
            case Scene::Scene_Type::Credits:
                scene.reset(new Scene::Credits(text_generator));
                break;
            default:
                BN_ERROR("Unknown Scene type: ", (int)*nextscene);
            }
        }
    }
}
