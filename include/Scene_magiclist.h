#ifndef SCENE_MAGICLIST_H
#define SCENE_MAGICLIST_H

#include "Game_battle_action.h"
#include "Scene.h"
#include "Status.h"
#include "Effect_transition.h"

#include "bn_regular_bg_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_ptr.h"

namespace Runa::Scene
{

class Magic_list final: public Scene_Root
{
public:
    Magic_list(bn::sprite_text_generator& text_generator, Status& status);
    ~Magic_list();
    bn::optional<Scene_Type> Update();

private:
    bn::sprite_text_generator& _text_generator;
    Status& _status;
    bn::regular_bg_ptr _bg_codex;

    bn::vector<bn::sprite_ptr, 70> _description_text;
    bn::vector<bn::sprite_ptr, 5> _page_text;
    bn::sprite_ptr _magic_graphic;
    bn::sprite_animate_action<11> _magic_effect;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 15;

    int _current_page = 0;
    const Runa::Game::Action::Action* _action = nullptr;
    /**
     * @brief Check if magic is learned and print codex
     */
    void Print_magic_codex();
};

} // namespace Runa::Scene

#endif // SCENE_MAGICLIST_H
