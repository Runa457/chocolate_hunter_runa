#include "Scene_option.h"

#include "bn_format.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sprite_items_cursor_0.h"

namespace Runa::Scene
{

namespace
{
constexpr int NUM_OPTION = 12;
constexpr bn::string_view OPTION_LIST[NUM_OPTION] = {
    "-Option & Codex-",
    "",
    "  Cookbook for Beginners",
    "  Grimoire of Runa",
    "", // Music Volume
    "", // Music Player
    "  Start new game",
    "",
    "",
    "",
    "",
    "Press B to return"
};
constexpr int OPTION_X = -100;
constexpr int OPTION_Y = -64;
constexpr int OPTION_Y_INT = 12;
constexpr int NUM_MUSIC = 5;
constexpr bn::music_item MUSIC_LIST[NUM_MUSIC] = {
    bn::music_items::my_street, // main menu
    bn::music_items::k_jose__tropical_feels, // 1st stratum
    bn::music_items::drozerix__crush, // boss battle
    bn::music_items::k_jose__merrily_strolling, // 2nd stratum
    bn::music_items::pxf_squarevox, // 3rd stratum
};
constexpr bn::string_view MUSIC_NAME[NUM_MUSIC] = {
    "Title screen",
    "1st stratum",
    "Boss battle",
    "2nd stratum",
    "3rd stratum",
};
constexpr int MUSIC_VOLUME[NUM_MUSIC] = {
    100, 100, 50, 50, 50
};

} // namespace

Option::Option(bn::sprite_text_generator& text_generator, Status& status) :
    _status(status),
    _text_generator(text_generator),
    _cursor(bn::sprite_items::cursor_0.create_sprite(OPTION_X, OPTION_Y + OPTION_Y_INT * 2)),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    switch (_status.Get_Max_stratum())
    {
    case 0:
    case 1:
        _max_music_index = _status.Get_Max_stratum();
        break;
    default:
        _max_music_index = _status.Get_Max_stratum() + 1;
        break;
    }
    if (_max_music_index >= NUM_MUSIC) { _max_music_index = NUM_MUSIC - 1; }
    //_max_music_index = NUM_MUSIC - 1;

    Effect::Print_text(_text_generator, true, Effect::Alignment::Left, OPTION_X, OPTION_Y, OPTION_Y_INT, _option_text, OPTION_LIST);
    for (bn::sprite_ptr& text_sprite : _option_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    Print_music_volume_text();
    Print_music_text();

    _cursor.set_blending_enabled(true);
    _scene_start.Start();
}
Option::~Option() {}

bn::optional<Scene_Type> Option::Update()
{
    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        return bn::nullopt;
    case Effect::State::Done:
        break;
    default: break;
    }

    switch (_scene_end.Get_state())
    {
    case Effect::State::Waiting:
        break;
    case Effect::State::Ongoing:
        _scene_end.Update();
        return bn::nullopt;
    case Effect::State::Done:
        if (_current_music_index != 0) { MUSIC_LIST[0].play(bn::fixed(_status.Get_Volume()) / 100, false); }
        return _nextscene;
    default: break;
    }

    if (_current_option == Options::Confirm_delete_save)
    {
        Save_delete_confirm();
    }
    else
    {
        Press_up_down();
        Press_left_right();
        if (bn::keypad::a_pressed())
        {
            _nextscene = Press_a();
            if (_nextscene) { _scene_end.Start(); }
        }
        else if (bn::keypad::b_pressed())
        {
            bn::sound_items::sfx_menu_cancelled.play();
            _status.WriteGlobal();
            _nextscene = Scene_Type::Title;
            _scene_end.Start();
        }
    }
    return bn::nullopt;
}

void Option::Press_up_down()
{
    if (bn::keypad::up_pressed()) Cursor_update(-1);
    else if (bn::keypad::down_pressed()) Cursor_update(1);
}
void Option::Press_left_right()
{
    if (bn::keypad::left_pressed() || bn::keypad::right_pressed())
    {
        switch (_current_option)
        {
        case Music_volume:
            if (bn::keypad::right_pressed()) { _status.Set_Volume(true); }
            else if (bn::keypad::left_pressed()) { _status.Set_Volume(false); }
            bn::music::set_volume(bn::fixed(_status.Get_Volume() * MUSIC_VOLUME[_current_music_index]) / 10000);
            Print_music_volume_text();
            break;
        case Music_player:
            if (bn::keypad::right_pressed() && _current_music_index < _max_music_index)
            {
                _current_music_index += 1;
            }
            else if (bn::keypad::left_pressed() && _current_music_index > 0)
            {
                _current_music_index -= 1;
            }
            MUSIC_LIST[_current_music_index].play(bn::fixed(_status.Get_Volume() * MUSIC_VOLUME[_current_music_index]) / 10000, _current_music_index != 0);
            Print_music_text();
            break;
        default:
            break;
        }
    }
}
void Option::Print_music_volume_text()
{
    _music_volume_text.clear();
    _text_generator.set_left_alignment();
    _text_generator.generate(OPTION_X, OPTION_Y + OPTION_Y_INT * 4, bn::format<22>("  Music Volume: {}%", _status.Get_Volume()), _music_volume_text);
    for (bn::sprite_ptr& text_sprite : _music_volume_text)
    {
        text_sprite.set_blending_enabled(true);
    }
}
void Option::Print_music_text()
{
    _music_text.clear();
    _text_generator.set_left_alignment();
    _text_generator.generate(OPTION_X, OPTION_Y + OPTION_Y_INT * 5, bn::format<30>("  Music Player: {}", MUSIC_NAME[_current_music_index]), _music_text);
    for (bn::sprite_ptr& text_sprite : _music_text)
    {
        text_sprite.set_blending_enabled(true);
    }
}
void Option::Save_delete_confirm()
{
    if (bn::keypad::a_pressed())
    {
        bn::sound_items::sfx_menu_selected.play();

        Effect::Print_text(_text_generator, true, Effect::Alignment::Right,
                           112, OPTION_Y + OPTION_Y_INT * 8, 0, _confirm_text,
                           1, "Save deleted.");
        for (bn::sprite_ptr& text_sprite : _confirm_text)
        {
            text_sprite.set_blending_enabled(true);
        }

        _status.Game_init();
        _status.Write();

        _nextscene = Scene_Type::Title;
        _scene_end.Start();
    }
    else if (bn::keypad::b_pressed())
    {
        bn::sound_items::sfx_menu_cancelled.play();

        _confirm_text.clear();
        _current_option = Options::Delete_save;
    }
}
bn::optional<Scene_Type> Option::Press_a()
{
    switch (_current_option)
    {
    case Delete_save:
        bn::sound_items::sfx_menu_selected.play();
        Effect::Print_text(_text_generator, true, Effect::Alignment::Right,
                           112, OPTION_Y + OPTION_Y_INT * 8, OPTION_Y_INT, _confirm_text,
                           3, "Are you sure to delete save file?", "Unlocked data will not be deleted.", "A: YES B: NO");

        _current_option = Options::Confirm_delete_save;
        break;
    case Enemy_list:
        bn::sound_items::sfx_menu_selected.play();
        return Scene_Type::Enemy_list;
    case Magic_list:
        bn::sound_items::sfx_menu_selected.play();
        return Scene_Type::Magic_list;
    default:
        break;
    }
    return bn::nullopt;
}
void Option::Cursor_update(int move_direction)
{
    bn::sound_items::sfx_menu_move.play();
    _current_option = static_cast<Options>((_current_option + 5 + move_direction) % 5);
    _cursor.set_position(OPTION_X, OPTION_Y + OPTION_Y_INT * (_current_option + 2));
}

} // namespace Runa::Scene
