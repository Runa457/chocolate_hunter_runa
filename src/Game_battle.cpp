#include "Game_battle.h"

#include "bn_format.h"
#include "bn_algorithm.h"

#include "bn_sprite_items_select_cursor_square.h"
#include "bn_sprite_items_select_cursor_down.h"
#include "bn_sprite_items_icon_sword_attack.h"
#include "bn_sprite_items_icon_shield.h"
#include "bn_sprite_items_icon_magic_attack.h"
#include "bn_sprite_items_effect_sword.h"

//#include "bn_log.h"

namespace Runa::Game
{

namespace
{
constexpr int ATTACK_ICON_X = 76;
constexpr int ATTACK_ICON_Y = 58;
constexpr int ENEMY_Y = 0;
}

Battle::Battle(bn::sprite_text_generator& text_generator,
               bn::random& random_generator,
               Status& status,
               bn::unique_ptr<Battle_Sequence>& battle_sq) :
    _status(status),
    _random(random_generator),
    _state(State::Start_turn),
    _text_generator(text_generator),
    _battle_sq(battle_sq),
    _enemies(battle_sq->Get_current_enemies()),
    _sword_attack_icon(bn::sprite_items::icon_sword_attack.create_sprite(ATTACK_ICON_X, ATTACK_ICON_Y)),
    _shield_icon(bn::sprite_items::icon_shield.create_sprite(ATTACK_ICON_X+16, ATTACK_ICON_Y)),
    _magic_attack_icon(bn::sprite_items::icon_magic_attack.create_sprite(ATTACK_ICON_X+32, ATTACK_ICON_Y)),
    _cursor(bn::sprite_items::select_cursor_square.create_sprite(ATTACK_ICON_X, ATTACK_ICON_Y)),
    _attack_effect_sprite(bn::sprite_items::effect_sword.create_sprite(0, 0)),
    _attack_effect(bn::create_sprite_animate_action_once(_attack_effect_sprite, 1, bn::sprite_items::effect_sword.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8)),
    _text_end(Effect::Type::Transparency, Effect::Direction::Out, 15),
    _enemy_end(static_cast<Effect::Type>(Effect::Type::Transparency | Effect::Type::Sprite_mosaic), Effect::Direction::Out, 20),
    _camera()
{
    _cursor.set_visible(false);
    _attack_effect_sprite.set_z_order(-10);
    _attack_effect_sprite.set_visible(false);
    _sword_attack_icon.set_visible(false);
    _shield_icon.set_visible(false);
    _magic_attack_icon.set_visible(false);

    Battle_start();
}
Battle::~Battle() {}

bn::optional<Game_Type> Battle::Update()
{
    //BN_LOG((int)_state);
    switch (_state)
    {
    case State::Start_turn:
        _turn_text.clear();
        _text_generator.set_center_alignment();
        _text_generator.generate(0, -73, bn::format<8>("Turn {}", ++_current_turn), _turn_text);
        _state = State::Action_select;
        break;
    case State::Action_select:
        _cursor.set_item(bn::sprite_items::select_cursor_square);
        _cursor.set_visible(true);
        _sword_attack_icon.set_visible(true);
        _shield_icon.set_visible(true);
        _magic_attack_icon.set_visible(true);

        _state = Action_select();
        if (_state == State::Target_select)
        {
            Print_enemy_information();
            _sword_attack_icon.set_visible(false);
            _shield_icon.set_visible(false);
            _magic_attack_icon.set_visible(false);
            _status._stats.Set_action_type(&Action::Get_action_data(Action::Action_index::Slash));
        }
        if (_state == State::Magic_select)
        {
            _status._stats.Set_action_type(&Action::Get_magic_data(static_cast<Action::Magic_index>(_magic_index)));
            Print_magic_information();
            _sword_attack_icon.set_visible(false);
            _shield_icon.set_visible(false);
            _cursor.set_visible(false);
        }
        if (_state == State::Confirm)
        {
            _sword_attack_icon.set_visible(false);
            _shield_icon.set_visible(false);
            _magic_attack_icon.set_visible(false);
            _cursor.set_visible(false);
            Effect::Print_text(_text_generator, true, Effect::Alignment::Center,
                               0, 15, 10, _battle_text,
                               2, "Confirm?", "A: YES B: NO");
            _status._stats.Set_action_type(&Action::Get_action_data(Action::Action_index::Guard));
        }
        break;
    case State::Magic_select:
        _state = Magic_select();
        switch (_state)
        {
        case State::Action_select:
            _battle_text.clear();
            break;
        case State::Target_select:
            Print_enemy_information();
            _magic_attack_icon.set_visible(false);
            break;
        case State::Confirm:
            _magic_attack_icon.set_visible(false);
            Effect::Print_text(_text_generator, true, Effect::Alignment::Center,
                               0, 15, 10, _battle_text,
                               2, "Confirm?", "A: YES B: NO");
            break;
        default: break;
        }
        break;
    case State::Target_select:
        _cursor.set_item(bn::sprite_items::select_cursor_down);
        _cursor.set_visible(true);

        _state = Target_select();
        switch (_state)
        {
        case State::Action_select:
            _battle_text.clear();
            break;
        case State::Confirm:
            _cursor.set_visible(false);
            Effect::Print_text(_text_generator, true, Effect::Alignment::Center,
                               0, 15, 10, _battle_text,
                               2, "Confirm?", "A: YES B: NO");
            break;
        default: break;
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
            _battle_text.clear();

            _effect_cooltime = 10;
            _damage_text_cooltime = 10;
            _enemy_dead_cooltime = 10;

            if (_action_order_index >= _enemies.size() + 1)
            {
                _action_order_index = 0;
                _state = State::End_turn;
            }
            else { _state = State::Turn_action; }
        }
        break;
    case State::End_turn:
        if (_status.turn_end() || _status.Get_hp() <= 0) { return Game_Type::Exit; }

        if (_num_enemies <= 0)
        {
            Battle_end();
            _state = State::End_battle;
        }
        else
        {
            for (int i = 0; i < _enemies.size(); i++)
            {
                if (!_enemies[i].Is_dead())
                {
                    _enemies[i]._stats.Turn_passed();
                }
            }
            _status._stats.Turn_passed();
            _state = State::Start_turn;
        }
        break;
    case State::End_battle:
        if (bn::keypad::a_pressed())
        {
            bn::sound_items::sfx_menu_selected.play();

            _battle_text.clear();
            if (_battle_sq->To_next_seq()) { return Game_Type::Battle; }
            else
            {
                _status.Lower_multiplier();
                if (_battle_sq->Get_is_boss())
                {
                    _status.Next_stratum();
                }
                return Game_Type::Rest;
            }
        }
        break;
    default: break;
    }
    return bn::nullopt;
}

Battle::State Battle::Action_select()
{
    if (bn::keypad::a_pressed())
    {
        bn::sound_items::sfx_menu_selected.play();
        switch (_attack_type)
        {
        case Next_action::Slash:
            return State::Target_select;
        case Next_action::Guard:
            return State::Confirm;
        case Next_action::Magic:
            return State::Magic_select;
        default:
            BN_ERROR();
            break;
        }
    }
    if (bn::keypad::left_pressed())
    {
        bn::sound_items::sfx_menu_move.play();
        _attack_type = static_cast<Next_action>((_attack_type + 2) % 3);
    }
    else if (bn::keypad::right_pressed())
    {
        bn::sound_items::sfx_menu_move.play();
        _attack_type = static_cast<Next_action>((_attack_type + 1) % 3);
    }
    _cursor.set_position(ATTACK_ICON_X + 16 * (int)_attack_type, ATTACK_ICON_Y);
    return State::Action_select;
}
Battle::State Battle::Magic_select()
{
    if (bn::keypad::a_pressed())
    {
        if (_status.Get_mp() < _status._stats.Get_action_type()->_cost)
        {
            bn::sound_items::sfx_menu_denied.play();
            return State::Magic_select;
        }
        bn::sound_items::sfx_menu_selected.play();
        if (_status._stats.Get_action_type()->_target == Action::Target_type::Single_target)
        {
            return State::Target_select;
        }
        else { return State::Confirm; }
    }
    if (bn::keypad::b_pressed())
    {
        bn::sound_items::sfx_menu_cancelled.play();
        return State::Action_select;
    }
    if (bn::keypad::left_pressed())
    {
        if (_magic_index != 0)
        {
            --_magic_index;
            _status._stats.Set_action_type(&Action::Get_magic_data(static_cast<Action::Magic_index>(_magic_index)));
            bn::sound_items::sfx_menu_move.play();
            Print_magic_information();
        }
    }
    else if (bn::keypad::right_pressed())
    {
        if (static_cast<Action::Magic_index>(++_magic_index) == Action::Magic_index::END_OF_INDEX) { --_magic_index; }
        else
        {
            _status._stats.Set_action_type(&Action::Get_magic_data(static_cast<Action::Magic_index>(_magic_index)));
            bn::sound_items::sfx_menu_move.play();
            Print_magic_information();
        }
    }
    return State::Magic_select;
}
void Battle::Print_magic_information()
{
    const Action::Action* _action_type = _status._stats.Get_action_type();

    //Effect::Print_text(_text_generator, true, Effect::Alignment::Right, ATTACK_ICON_X, ATTACK_ICON_Y, 0, _battle_text, 1, "");
    _battle_text.clear();
    _text_generator.set_right_alignment();
    _text_generator.generate(ATTACK_ICON_X+40, ATTACK_ICON_Y-16, bn::format<20>("{} ({})", _action_type->_name, _action_type->_cost), _battle_text);

    bn::string_view target_type = "";
    switch (_action_type->_target)
    {
    case Action::Target_type::Self_target:
        target_type = "Self";
        break;
    case Action::Target_type::Single_target:
        target_type = "Single";
        break;
    case Action::Target_type::Multi_hit:
        target_type = "Multi";
        break;
    case Action::Target_type::Every_enemy_target:
        target_type = "Enemies";
        break;
    case Action::Target_type::Entire_target:
        target_type = "Entire";
        break;
    default:
        BN_ERROR();
        break;
    }
    _text_generator.generate(ATTACK_ICON_X+22, ATTACK_ICON_Y-4, bn::format<7>("{}", target_type), _battle_text);
}
Battle::State Battle::Target_select()
{
    if (bn::keypad::a_pressed())
    {
        bn::sound_items::sfx_menu_selected.play();
        return State::Confirm;
    }
    if (bn::keypad::b_pressed())
    {
        bn::sound_items::sfx_menu_cancelled.play();
        return State::Action_select;
    }
    if (bn::keypad::left_pressed())
    {
        bn::sound_items::sfx_menu_move.play();
        do {
        _target_index = (_target_index + _enemies.size() - 1) % _enemies.size();
        } while (_enemies[_target_index].Is_dead());
        Print_enemy_information();
    }
    else if (bn::keypad::right_pressed())
    {
        bn::sound_items::sfx_menu_move.play();
        do {
        _target_index = (_target_index + 1) % _enemies.size();
        } while (_enemies[_target_index].Is_dead());
        Print_enemy_information();
    }
    _cursor.set_position(_enemy_x[_target_index], -25);
    return State::Target_select;
}
void Battle::Print_enemy_information()
{
    _battle_text.clear();
    _text_generator.set_center_alignment();
    _text_generator.generate(0, -60, bn::format<20>("Lv {} {}", _enemies[_target_index].Get_level(), _enemies[_target_index].Get_name()), _battle_text);
    _text_generator.generate(0, -50, bn::format<10>("Hp {}", _enemies[_target_index].Get_hp()), _battle_text);
    // debug line ; stats
    _text_generator.generate(0, -40, bn::format<20>("A {} D {} S {}", _enemies[_target_index]._stats.Get_base_atk(), _enemies[_target_index]._stats.Get_base_def(), _enemies[_target_index]._stats.Get_base_spd()), _battle_text);
}

Battle::State Battle::Confirm()
{
    if (bn::keypad::a_pressed())
    {
        bn::sound_items::sfx_menu_selected.play();
        Action_order_decision();
        return State::Turn_action;
    }
    if (bn::keypad::b_pressed())
    {
        bn::sound_items::sfx_menu_cancelled.play();

        return State::Action_select;
    }
    return State::Confirm;//
}
void Battle::Action_order_decision()
{
    _action_order.clear();
    _action_order.push_back({_status._stats.Get_spd(), -1});
    for (int i = 0; i < _enemies.size(); i++)
    {
        _enemies[i].Set_action_type(_current_turn);
        _action_order.push_back({_enemies[i]._stats.Get_spd(), i});
    }
    bn::sort(_action_order.rbegin(), _action_order.rend());
}
void Battle::Turn_action()
{
    short index = _action_order[_action_order_index].second;
    ActorStats* attacker = nullptr;

    if (index == -1)
    {
        attacker = &_status._stats;
        if (_left_hit == 0) { _status.Mp_change(-attacker->Get_action_type()->_cost); }
    }
    else if (!_enemies[index].Is_dead()) { attacker = &_enemies[index]._stats; }
    else { ++_action_order_index; return; }

    switch (attacker->Get_action_type()->_target)
    {
    case Action::Target_type::Self_target:
        Action_execute(index, index);
        break;
    case Action::Target_type::Single_target:
        int j;
        j = (index == -1) ? _target_index : -1;
        Action_execute(index, j);
        break;
    case Action::Target_type::Multi_hit:
        if (_left_hit == 0) { _left_hit = 3; }
        if (index == -1)
        {
            if (_num_enemies == 0) { break; }
            int k = 0;
            do { k = _random.get_int(_enemies.size()); } while (_enemies[k].Is_dead());
            Action_execute(index, k);
        }
        else { Action_execute(index, -1); }
        if (--_left_hit > 0) { return; }
        break;
    case Action::Target_type::Every_enemy_target:
        if (_left_hit == 0) { _left_hit = 3; }
        if (_left_hit <= _enemies.size() && !_enemies[_left_hit-1].Is_dead())
        {
            Action_execute(index, _left_hit-1);
        }
        if (--_left_hit > 0) { return; }
        break;
    case Action::Target_type::Entire_target:
        if (_left_hit == 0) { _left_hit = 4; }
        if (_left_hit == 4) { Action_execute(index, -1); }
        else if (_left_hit <= _enemies.size() && !_enemies[_left_hit-1].Is_dead())
        {
            Action_execute(index, _left_hit-1);
        }
        if (--_left_hit > 0) { return; }
        break;
    default:
        BN_ERROR();
        break;
    }
    _left_hit = 0;
    ++_action_order_index;
}
void Battle::Action_execute(int attacker_idx, int defender_idx)
{
    ActorStats* attacker = nullptr;
    ActorStats* defender = nullptr;

    //BN_LOG("Action execute");

    if (attacker_idx == -1)
    {
        attacker = &_status._stats;
        //BN_LOG(attacker->Get_action_type()->_name);
        Effect::Print_text(_text_generator, false, Effect::Alignment::Center, -90, 72, 0,
                           _battle_text, 1, attacker->Get_action_type()->_name);
    }
    else
    {
        attacker = &_enemies[attacker_idx]._stats;
        //BN_LOG(attacker->Get_action_type()->_name);
        Effect::Print_text(_text_generator, false, Effect::Alignment::Center, _enemy_x[attacker_idx], ENEMY_Y+20, 0,
                           _battle_text, 1, attacker->Get_action_type()->_name);
    }

    if (defender_idx == -1) { defender = &_status._stats; }
    else { defender = &_enemies[defender_idx]._stats; }

    int damage = attack_function(attacker, defender, _random);

    if (attacker_idx == -1) { /*_camera.Set_attacker(_player_sprite);*/ }
    else { _camera.Set_attacker(_enemy_sprite[attacker_idx]); }

    if (defender_idx == -1)
    {
        _status.Hp_change(-damage);
        Attack_effect(-90, 57, damage, attacker->Get_action_type());
        //if (damage > 0) { _camera.Start_movement(_player_sprite); }
    }
    else
    {
        _enemies[defender_idx].Hp_change(-damage);
        Attack_effect(_enemy_x[defender_idx], ENEMY_Y, damage, attacker->Get_action_type());
        if (damage > 0) { _camera.Set_defender(_enemy_sprite[defender_idx]); }
    }
    _camera.Start_movement();
}
void Battle::Attack_effect(int x, int y, int damage,
                           const Action::Action* action)
{
    //BN_LOG("Action effect");

    _attack_effect_sprite.set_position(x, y);
    _attack_effect_sprite.set_visible(true);
    _attack_effect = bn::create_sprite_animate_action_once(_attack_effect_sprite, 1, action->_action_effect.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8);

    action->_action_sound.play();

    _text_generator.set_center_alignment();
    if (damage == 0) { return; }
    else if (damage > 0)
    {
        _text_generator.generate(x, y-25, bn::format<5>("{}", damage), _damage_text);
    }
    else if (damage < 0)
    {
        _text_generator.generate(x, y-25, bn::format<6>("+{}", -damage), _damage_text);
    }
    for (bn::sprite_ptr& text : _damage_text)
    {
        text.set_visible(false);
        text.set_blending_enabled(true);
    }
}
bool Battle::Effect_action()
{
    Camera_action();

    if (!_attack_effect.done())
    {
        _attack_effect.update();
        return false;
    }
    if (bn::keypad::a_held()) { _effect_cooltime = 0; }
    else if (--_effect_cooltime > 0) { return false; }

    //BN_LOG("_text_end.Get_state()");

    switch (_text_end.Get_state())
    {
    case Effect::State::Waiting:
        if (_damage_text.empty()) { return true; }
        else
        {
            for (bn::sprite_ptr& text : _damage_text) { text.set_visible(true); }
            //bn::sound_items::sfx_battle_sword.play();
            _text_end.Start();
        }
        return false;
    case Effect::State::Ongoing:
        _text_end.Update();
        return false;
    case Effect::State::Done:
        _damage_text.clear();
        break;
    default: break;
    }

    if (bn::keypad::a_held()) { _damage_text_cooltime = 0; }
    else if (--_damage_text_cooltime > 0) { return false; }

    for (int i = 0; i < _enemies.size(); i++)
    {
        if (_enemies[i].Is_dead()) { Enemy_dead(i); }
    }

    switch (_enemy_end.Get_state())
    {
    case Effect::State::Waiting:
        _text_end.Reset();
        return true;
    case Effect::State::Ongoing:
        _enemy_end.Update();
        return false;
    case Effect::State::Done:
        for (int i = 0; i < _enemies.size(); i++)
        {
            if (_enemies[i].Is_dead()) { _enemy_sprite[i].set_visible(false); }
        }
        if (bn::keypad::a_held()) { _enemy_dead_cooltime = 0; }
        else if (--_enemy_dead_cooltime > 0) { return false; }

        _enemy_end.Reset();
        break;
    default: break;
    }
    return false;
}
void Battle::Camera_action()
{
    _camera.Update();
}

void Battle::Enemy_dead(short index)
{
    if (_enemy_end.Get_state() != Effect::State::Waiting
            || !_enemy_sprite[index].visible()) { return; }

    bn::sound_items::sfx_battle_enemy_dead.play();

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
        _enemies[i].Sprite_create(_enemy_x[i], ENEMY_Y, _enemy_sprite);
        //enemy_hpbar;
    }
}
void Battle::Battle_end()
{
    _status._stats.Remove_status_effect();

    int xp = 0;
    int choco = 0;

    for (Enemy::Enemy& enemy : _enemies)
    {
        xp += enemy.Get_exp();
        choco += enemy.Get_choco();
    }
    int total_choco = (choco * _status.Get_multiplier() + 50) / 100;

    _text_generator.set_center_alignment();
    _text_generator.generate(0, 0, "Victory!", _battle_text);
    _text_generator.generate(0, 10, bn::format<25>("Gain {} experiences.", xp), _battle_text);
    _text_generator.generate(0, 20, bn::format<35>("Gain {}x{}% = {} chocolates.", choco, _status.Get_multiplier(), total_choco), _battle_text);

    _status.Exp_earn(xp);
    _status.Choco_earn(total_choco);
}

} // namespace Runa::Scene
