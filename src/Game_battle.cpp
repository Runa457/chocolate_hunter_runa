#include "Game_battle.h"
#include "Stats_data.h"

#include "bn_format.h"
#include "bn_algorithm.h"

#include "bn_sprite_items_cursor_0.h"

namespace Runa::Game
{

Battle::Battle(bn::sprite_text_generator& text_generator,
               Status& status,
               bn::unique_ptr<Battle_Sequence>& battle_sq) :
    _text_generator(text_generator),
    _status(status),
    _state(State::Start_turn),
    _action_order(0),
    _battle_sq(battle_sq),
    _enemies(battle_sq->Get_current_enemies()),
    _num_enemies(3),
    _cursor(bn::sprite_items::cursor_0.create_sprite(94, 56)),
    _attack_type(false),
    _target_index(0),
    _enemy_end(static_cast<Effect::Type>(Effect::Type::Transparency | Effect::Type::Sprite_mosaic),
               Effect::Direction::Out, 20),
    _text_end(Effect::Type::Transparency, Effect::Direction::Out, 15)
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
        break;
    case State::Action_select:
        _cursor.set_item(bn::sprite_items::cursor_0);
        _cursor.set_visible(true);

        _state = Action_select();
        if (_state == State::Target_select) { Print_enemy_information(); }
        break;
    case State::Target_select:
        _cursor.set_item(bn::sprite_items::cursor_0); // <- cursor_1

        _state = Target_select();
        switch (_state)
        {
        case State::Action_select:
            _battle_text.clear();
            break;
        case State::Confirm:
            _cursor.set_visible(false);
            _battle_text.clear();
            _text_generator.set_center_alignment();
            _text_generator.generate(0, 10, "Confirm?", _battle_text);
            _text_generator.generate(0, 20, "A: YES B: NO", _battle_text);
            _text_generator.set_left_alignment();
            break;
        default:
            break;
        }
        break;
    case State::Confirm:
        _state = Confirm();
        switch (_state)
        {
        case State::Action_select:
        case State::Turn_action:
            _battle_text.clear();
            break;
        default:
            break;
        }
        break;
    case State::Turn_action:
        Turn_action();
        _state = State::Effect_action;
        break;
    case State::Effect_action:
        if (Effect_action())
        {
            if (_action_order == _enemies.size() + 1)
            {
                _action_order = 0;
                _state = State::End_turn;
            }
            else { _state = State::Turn_action; }
        }
        break;
    case State::End_turn:
        if (_status.turn_end()) { return Game_Type::Exit; }
        if (_status.Get_hp() <= 0) { return Game_Type::Exit; }

        if (_num_enemies <= 0)
        {
            Battle_end();
            _state = State::End_battle;
        }
        else { _state = State::Start_turn; }
        break;
    case State::End_battle:
        if (bn::keypad::a_pressed())
        {
            _battle_text.clear();
            return (_battle_sq->To_next_seq()) ? Game_Type::Rest : Game_Type::Battle; //<-Rest
        }
        break;
    }
    return bn::nullopt;
}

Battle::State Battle::Action_select()
{
    if (bn::keypad::a_pressed()) { return State::Target_select; }
    else if (bn::keypad::up_pressed() || bn::keypad::down_pressed())
    {
        _attack_type = (_attack_type) ? false : true;
    }
    _cursor.set_position(94, (_attack_type) ? 72 : 56);
    return State::Action_select;
}
Battle::State Battle::Target_select()
{
    if (bn::keypad::a_pressed()) { return State::Confirm; }
    if (bn::keypad::b_pressed()) { return State::Action_select; }
    else if (bn::keypad::left_pressed())
    {
        do {
        _target_index = (_target_index + _enemies.size() - 1) % _enemies.size();
        } while (_enemies[_target_index].Is_dead());
        Print_enemy_information();
    }
    else if (bn::keypad::right_pressed())
    {
        do {
        _target_index = (_target_index + 1) % _enemies.size();
        } while (_enemies[_target_index].Is_dead());
        Print_enemy_information();
    }
    _cursor.set_position(_enemy_x[_target_index], -30);
    return State::Target_select;
}
void Battle::Print_enemy_information()
{
    _battle_text.clear();
    _text_generator.set_center_alignment();
    _text_generator.generate(0, -60, bn::format<15>("Lv {} {}", _enemies[_target_index].Get_level(), _enemies[_target_index].Get_name()), _battle_text);
    _text_generator.generate(0, -50, bn::format<10>("Hp {}", _enemies[_target_index].Get_hp()), _battle_text);
    // debug line ; stats
    _text_generator.generate(0, -40, bn::format<20>("A {} D {} S {}", _enemies[_target_index].Get_atk(), _enemies[_target_index].Get_def(), _enemies[_target_index].Get_spd()), _battle_text);
    _text_generator.set_left_alignment();
}

Battle::State Battle::Confirm()
{
    if (bn::keypad::a_pressed())
    {
        _attack_order.clear();
        _attack_order.push_back({Get_spd_data(_status.Get_level()), -1});
        for (int i = 0; i < _enemies.size(); i++)
        {
            _attack_order.push_back({_enemies[i].Get_spd(), i});
        }
        bn::sort(_attack_order.rbegin(), _attack_order.rend());
        return State::Turn_action;
    }
    if (bn::keypad::b_pressed()) { return State::Action_select; }
    return State::Confirm;//
}
void Battle::Turn_action()
{
    int level = _status.Get_level();
    int damage;
    short index = _attack_order[_action_order].second;

    _text_generator.set_center_alignment();

    if (index == -1) // player attack
    {
        if (_attack_type)
        {
            if (!_status.Mp_change(-5)) { _attack_type = false; }
        }
        damage = Damage_calculator(Get_str_data(level), Get_weapon_data(_status.Get_weapon()), _enemies[_target_index].Get_def(), 0, Get_int_data(level), _attack_type); // enemy weapon/armor level?

        _text_generator.generate(_enemy_x[_target_index], -30, bn::format<5>("{}", damage), _damage_text);
        for (bn::sprite_ptr& text : _damage_text)
        {
            text.set_blending_enabled   (true);
        }
        _text_end.Start();

        _enemies[_target_index].Hp_change(-damage);
    }
    else if (!_enemies[index].Is_dead()) // enemy attack
    {
        damage = Damage_calculator(_enemies[index].Get_atk(), 0, Get_def_data(level), Get_armor_data(_status.Get_armor()), 0, false);

        _text_generator.generate(-90, 40, bn::format<5>("{}", damage), _damage_text);
        for (bn::sprite_ptr& text : _damage_text)
        {
            text.set_blending_enabled(true);
        }
        _text_end.Start();

        _status.Hp_change(-damage);
    }

    _text_generator.set_left_alignment();
    ++_action_order;
}

int Battle::Damage_calculator(int str, int weapon, int def, int armor, int inte, bool type)
{
    int base = (type) ? inte * 2 : str;
    int dmg = (base + weapon + 1) / (def + 1);
    dmg = dmg + (base * base / 3 + weapon + 1) / (def + armor + 1);
    dmg = dmg + weapon - armor;
    dmg = bn::max(1, dmg);
    return dmg;
}

bool Battle::Effect_action()
{
    switch (_text_end.Get_state())
    {
    case Effect::State::Waiting:
        return true;
    case Effect::State::Ongoing:
        _text_end.Update();
        break;
    case Effect::State::Done:
        _damage_text.clear();

        for (int i = 0; i < _enemies.size(); i++)
        {
            if (_enemies[i].Is_dead()) { Enemy_dead(i); }
        }

        switch (_enemy_end.Get_state())
        {
        case Effect::State::Waiting:
            _text_end.Reset();
            return true;
            break;
        case Effect::State::Ongoing:
            _enemy_end.Update();
            break;
        case Effect::State::Done:
            for (int i = 0; i < _enemies.size(); i++)
            {
                if (_enemies[i].Is_dead()) { _enemy_sprite[i].set_visible(false); }
            }
            _text_end.Reset();
            _enemy_end.Reset();
            break;
        default: break;
        }

        break;
    default: break;
    }
    return false;
}

void Battle::Enemy_dead(short index)
{
    if (_enemy_end.Get_state() != Effect::State::Waiting
            || !_enemy_sprite[index].visible()) { return; }

    _enemy_sprite[index].set_blending_enabled(true);
    _enemy_sprite[index].set_mosaic_enabled(true);
    _enemy_end.Start();

    if (--_num_enemies <= 0) { return; }
    do {
    _target_index = (_target_index + 1) % _enemies.size();
    } while (_enemies[_target_index].Is_dead());
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
void Battle::Battle_end()
{
    int xp = 0;
    int choco = 0;

    for (Enemy::Enemy& enemy : _enemies)
    {
        xp += enemy.Get_exp();
        choco += enemy.Get_choco();
    }
    _text_generator.set_center_alignment();
    _text_generator.generate(0, 10, "Victory!", _battle_text);
    _text_generator.generate(0, 20, bn::format<35>("Gain {} exp, {} chocolates.", xp, choco), _battle_text);
    _text_generator.set_left_alignment();

    _status.Exp_earn(xp);
    _status.Choco_earn(choco);

    if (_battle_sq->Get_is_boss()) { /* stratum++; */ }
}

} // namespace Runa::Scene
