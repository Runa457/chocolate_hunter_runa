#ifndef SCENE_OPTION_H
#define SCENE_OPTION_H

#include "Scene.h"
#include "Status.h"
#include "Effect_transition.h"

#include "bn_sprite_ptr.h"

namespace Runa::Scene
{

class Option final: public Scene_Root
{
public:
    Option(bn::sprite_text_generator& text_generator, Status& status);
    ~Option();
    bn::optional<Scene_Type> Update();

private:
    enum Options : char
    {
        Delete_save,
        Placeholder,
        Confirm_delete_save = 255
    };

    Status& _status;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 50> _option_text;
    bn::vector<bn::sprite_ptr, 10> _confirm_text;

    bn::sprite_ptr _cursor;
    Options _current_option = Options::Delete_save;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 15;

    /**
     * @brief Handles menu cursor movement when pressing up / down button.
     */
    void Press_up_down();
    /**
     * @brief Handles when option is selected.
     */
    void Press_a();

    /**
     * @brief Updates cursor position.
     * @param Cursor movement direction. +1: downward, -1: upward.
     */
    void Cursor_update(int move_direction);
};

} // namespace Runa::Scene


#endif // SCENE_OPTION_H
