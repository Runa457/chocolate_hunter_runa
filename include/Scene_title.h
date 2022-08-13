#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene.h"
#include "Effect_transition.h"

#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace Runa::Scene
{

class Title final : public Scene_Root
{
public:
    Title(bn::sprite_text_generator& text_generator);
    ~Title();
    bn::optional<Scene_Type> Update();

private:
    enum class Menu : char
    {
        Main_game_start,
        Introduction,
        Options,
        Credits,
        Back_to_logo,
        Num_menu
    };

    static constexpr int NUM_MENU_OPTIONS = static_cast<int>(Menu::Num_menu);
    static constexpr bn::string_view MENU_LISTS[NUM_MENU_OPTIONS] =
        {"Start", "Introdunction", "Options", "Credits", "Back to title"};

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 20> _menu_text;

    bn::sprite_ptr _cursor;
    //bn::regular_bg_ptr bg;

    Menu _current_menu = Menu::Main_game_start;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 15;

    /**
     * @brief Handles menu cursor movement when pressing up / down button.
     */
    void Press_up_down();

    /**
     * @brief Updates cursor position.
     * @param Cursor movement direction. +1: downward, -1: upward.
     */
    void Cursor_update(int move_direction);

    bn::optional<Scene_Type> Get_next_scene();

    /**
     * @brief Prints menu texts.
     */
    void PrintText();
};

} // namespace Runa::Scene

#endif // SCENE_TITLE_H
