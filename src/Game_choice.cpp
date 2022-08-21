#include "Game_choice.h"

#include "bn_sprite_items_select_battle.h"

#include "bn_format.h"

namespace Runa::Game
{

namespace
{
static constexpr int CURSOR_X = 60;
static constexpr int CURSOR_Y = -20;
}

Choice::Choice(bn::sprite_text_generator& text_generator,
               bn::random& random_generator,
               Status& status,
               bn::unique_ptr<Battle_Sequence>& battle_sq) :
    _random(random_generator),
    _text_generator(text_generator),
    _status(status),
    _cursor(bn::sprite_items::select_battle.create_sprite(0, CURSOR_Y)),
    _current_menu(Menu::Center),
    _sequence_option{},
    _next_sequence(battle_sq),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    _sequence_option[0].reset(new Battle_Sequence(_random, status.Get_level(), status.Get_stratum(), false));
    if (_status.Get_multiplier() <= 100)
        { _sequence_option[1].reset(new Battle_Sequence(_random, status.Get_level(), status.Get_stratum(), true)); }
    else { _sequence_option[1].reset(new Battle_Sequence(_random, status.Get_level(), status.Get_stratum(), false)); }
    _sequence_option[2].reset(new Battle_Sequence(_random, status.Get_level(), status.Get_stratum(), false));

    Print_text();

    _cursor.set_blending_enabled(true);
    for (bn::sprite_ptr& text_sprite : _text_sprite)
    {
        text_sprite.set_blending_enabled(true);
    }
    _scene_start.Start();
}
Choice::~Choice() {}

bn::optional<Game_Type> Choice::Update()
{
    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        Press_left_right();
        break;
    case Effect::State::Done:
        switch (_scene_end.Get_state())
        {
        case Effect::State::Waiting:
            Press_left_right();
            if (bn::keypad::a_pressed())
            {
                bn::sound_items::sfx_menu_selected.play(); //<- may different sfx?
                _scene_end.Start();
            }
            break;
        case Effect::State::Ongoing:
            _scene_end.Update();
            break;
        case Effect::State::Done:
            _next_sequence = bn::move(_sequence_option[_current_menu]);
            return Game_Type::Battle;
            break;
        default: break;
        }
        break;
    default: break;
    }
    return bn::nullopt;
}

void Choice::Print_text()
{
    _text_generator.set_center_alignment();
    for (int i = 0; i < 3; i++)
    {
        if (_sequence_option[i]->Get_is_boss())
        {
            _text_generator.generate((i-1)*CURSOR_X, -36, "-BOSS-", _text_sprite);
        }
        _text_generator.generate((i-1)*CURSOR_X, -6, bn::format<5>("S: {}", _sequence_option[i]->Get_num_seq()), _text_sprite);
        _text_generator.generate((i-1)*CURSOR_X, 4, bn::format<6>("E: {}", _sequence_option[i]->Get_total_enemy()), _text_sprite);
        _text_generator.generate((i-1)*CURSOR_X, 14, bn::format<10>("C: {}", _sequence_option[i]->Get_total_choco()), _text_sprite);
    }
    _text_generator.set_left_alignment();
}
void Choice::Press_left_right()
{
    if (bn::keypad::left_pressed()) Cursor_update(-1);
    else if (bn::keypad::right_pressed()) Cursor_update(1);
}
void Choice::Cursor_update(int move_direction)
{
    bn::sound_items::sfx_menu_move.play();
    _current_menu = static_cast<Menu>((_current_menu + 3 + move_direction) % 3);
    _cursor.set_position((_current_menu - 1)*CURSOR_X, CURSOR_Y);
}

} // namespace Runa::Scene
