#include "Game_battle.h"

#include "bn_sprite_items_cursor_0.h"

namespace Runa::Game
{

Battle::Battle(bn::sprite_text_generator& text_generator,
               Status& status,
               bn::unique_ptr<Battle_Sequence>& battle_sq) :
    _text_generator(text_generator),
    _status(status),
    _battle_sq(battle_sq),
    _enemies(battle_sq->Get_current_enemies()),
    _num_enemies(3),
    _state(State::Start_turn),
    _cursor(bn::sprite_items::cursor_0.create_sprite(94, 56)),
    _attack_type(false),
    _target_index(0)
{
    _cursor.set_visible(false);
    Battle_start();
}
Battle::~Battle() {}

bn::optional<Game_Type> Battle::Update()
{
    switch (_state)
    {
    case State::Start_turn:
        _state = State::Action_select;
        _cursor.set_position(94, (_attack_type) ? 72 : 56);
        _cursor.set_visible(true);
        break;
    case State::Action_select:
        if (Action_select())
        {
            _state = State::Target_select;
            _cursor.set_item(bn::sprite_items::cursor_0);
            _cursor.set_position(94, (_attack_type) ? 112 : 96);
        }
        break;
    case State::Target_select:
        if (Target_select())
        {
            _state = State::Confirm;
            _cursor.set_visible(false);
        }
        break;
    case State::Confirm:
        if (Confirm()) { _state = State::Turn_action; }
        else { _state = State::Action_select; }
        break;
    case State::Turn_action:
        break;
    case State::End_turn:
        _status.turn_end();
        if (_num_enemies <= 0)
        {
            if (Battle_end()) { return Game_Type::Rest; }
            else { return Game_Type::Battle; }
        }
        break;
    }
    return bn::nullopt;
}

void Battle::Print_text()
{
}

bool Battle::Action_select()
{
    if (bn::keypad::a_pressed()) { return true; }
    else if (bn::keypad::up_pressed() || bn::keypad::down_pressed())
    {
        _attack_type = (_attack_type) ? false : true;
        _cursor.set_position(94, (_attack_type) ? 72 : 56);
    }
    return false;
}
bool Battle::Target_select()
{
    if (bn::keypad::a_pressed()) { return true; }
    else if (bn::keypad::left_pressed())
    {
        do {
        _target_index = (_target_index + _enemies.size() - 1) % _enemies.size();
        } while (_enemies[_target_index].Hp_change(0));
    }
    else if (bn::keypad::right_pressed())
    {
        do {
        _target_index = (_target_index + 1) % _enemies.size();
        } while (_enemies[_target_index].Hp_change(0));
    }
    _cursor.set_position(_enemy_x[_target_index], -30);
    return false;
}
bool Battle::Confirm()
{
    return true;//
}
void Battle::Battle_start()
{
    _num_enemies = _enemies.size();
    switch (_num_enemies)
    {
    case 1:
        _enemy_x[0] = 0;
        break;
    case 2:
        _enemy_x[0] = -40;
        _enemy_x[1] = 40;
    case 3: break;
    default:
        BN_ERROR("Invalid enemy number", _num_enemies);
        break;
    }

    for (int i = 0; i < _num_enemies; i++)
    {
        _enemies[i].Sprite_create(_enemy_x[i], -12, _enemy_sprite);
        //enemy_hpbar;
    }
}
bool Battle::Battle_end()
{
    // exp, choco gain
    if (_battle_sq->Get_is_boss()) { /* stratum++; */ }
    return _battle_sq->To_next_seq();
}

} // namespace Runa::Scene
