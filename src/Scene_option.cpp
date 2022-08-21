#include "Scene_option.h"

#include "bn_sprite_items_cursor_0.h"

namespace Runa::Scene
{

namespace
{
constexpr int NUM_OPTION = 12;
constexpr bn::string_view OPTION_LIST[NUM_OPTION] = {
    "-Option-",
    "",
    "",
    "  Delete save data",
    "  Placeholder",
    "",
    "",
    "",
    "",
    "",
    "",
    "Press B to return"
};
constexpr int OPTION_X = -100;
constexpr int OPTION_Y = -64;
constexpr int OPTION_Y_INT = 12;

} // namespace

Option::Option(bn::sprite_text_generator& text_generator, Status& status) :
    _text_generator(text_generator),
    _status(status),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES),
    _cursor(bn::sprite_items::cursor_0.create_sprite(OPTION_X, OPTION_Y + OPTION_Y_INT * 3))
{
    for (int i = 0; i < NUM_OPTION; i++)
    {
        _text_generator.generate(OPTION_X, OPTION_Y + OPTION_Y_INT * i, OPTION_LIST[i], _option_text);
    }
    for (bn::sprite_ptr& text_sprite : _option_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    _scene_start.Start();
}
Option::~Option() {}

bn::optional<Scene_Type> Option::Update()
{
    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        break;
    case Effect::State::Done:
        switch (_scene_end.Get_state())
        {
        case Effect::State::Waiting:
            if (_current_option == Options::Confirm_delete_save)
            {
                if (bn::keypad::a_pressed())
                {
                    bn::sound_items::sfx_menu_selected.play();

                    _confirm_text.clear();
                    _text_generator.set_right_alignment();
                    _text_generator.generate(112, OPTION_Y + OPTION_Y_INT * 1, "Save deleted.", _confirm_text);
                    _text_generator.set_left_alignment();

                    _status.Init();
                    _status.Write();
                    _current_option = Options::Delete_save;
                }
                else if (bn::keypad::b_pressed())
                {
                    bn::sound_items::sfx_menu_cancelled.play();

                    _confirm_text.clear();
                    _current_option = Options::Delete_save;
                }
            }
            else
            {
                Press_up_down();
                if (bn::keypad::a_pressed()) { Press_a(); }
                if (bn::keypad::b_pressed())
                {
                    bn::sound_items::sfx_menu_cancelled.play();
                    _scene_end.Start();
                }
            }
            break;
        case Effect::State::Ongoing:
            _scene_end.Update();
            break;
        case Effect::State::Done:
            return Scene_Type::Title;
            break;
        default: break;
        }
        break;
    default: break;
    }
    return bn::nullopt;
}

void Option::Press_up_down()
{
    if (bn::keypad::up_pressed()) Cursor_update(-1);
    else if (bn::keypad::down_pressed()) Cursor_update(1);
}
void Option::Press_a()
{
    bn::sound_items::sfx_menu_selected.play();
    switch (_current_option)
    {
    case Delete_save:
        _confirm_text.clear();
        _text_generator.set_right_alignment();
        _text_generator.generate(112, OPTION_Y + OPTION_Y_INT * 1, "Are you sure to delete save file?", _confirm_text);
        _text_generator.generate(112, OPTION_Y + OPTION_Y_INT * 2, "A: YES B: NO", _confirm_text);
        _text_generator.set_left_alignment();

        _current_option = Options::Confirm_delete_save;
        break;
    case Placeholder:
        break;
    default:
        break;
    }
}
void Option::Cursor_update(int move_direction)
{
    bn::sound_items::sfx_menu_move.play();
    _current_option = static_cast<Options>((_current_option + 2 + move_direction) % 2);
    _cursor.set_position(OPTION_X, OPTION_Y + OPTION_Y_INT * (_current_option + 3));
}

} // namespace Runa::Scene
