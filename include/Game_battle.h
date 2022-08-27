#ifndef GAME_BATTLE_H
#define GAME_BATTLE_H

#include "Effect_camera.h"
#include "Game.h"
#include "Battle_sequence.h"
#include "Game_battle_function.h"

#include "bn_sprite_animate_actions.h"

namespace Runa::Game
{

class Battle final : public Game_Root
{
public:
    Battle(bn::sprite_text_generator& text_generator,
           bn::random& random_generator,
           Status& status,
           bn::unique_ptr<Battle_Sequence>& battle_sq);
    ~Battle();
    bn::optional<Game_Type> Update();

private:
    enum class State : char
    {
        Start_turn,
        Action_select,
        Magic_select,
        Target_select,
        Confirm,
        Turn_action,
        Effect_action,
        End_turn,
        End_battle
    };

    enum Next_action : char
    {
        Slash,
        Guard,
        Magic
    };

    /**
     * @brief Called at start of battle.
     * Create sprite of enemies.
     */
    void Battle_start();
    State Action_select();
    State Target_select();
    State Magic_select();

    /**
     * @brief Confirm current action.
     * Speed check & ordering happens here.
     * @return Next state
     */
    State Confirm();
    /**
     * @brief Decides attack order.
     */
    void Action_order_decision();
    void Turn_action();
    /**
     * @brief Action_execute
     * @param -1 if attacker is player
     * @param -1 if defender is player
     */
    void Action_execute(int attacker_idx, int defender_idx);
    /**
     * @brief Handles attack effects.
     * @param x coordinate of defender.
     * @param y coordinate of defender.
     * @param damage
     * @param Action
     */
    void Attack_effect(int x, int y, int damage,
                       const Action::Action* action);
    bool Effect_action();
    void Camera_action();
    /**
     * @brief Handles enemy dead effect and move target index to next.
     * @param index
     */
    void Enemy_dead(short index);

    void Print_magic_information();
    /**
     * @brief Prints enemy level, name and stats.
     */
    void Print_enemy_information();

    /**
     * @brief Called at end of battle.
     * Gain exp, chocolate.
     */
    void Battle_end();

    Status& _status;
    bn::random& _random;

    State _state;
    short _action_order_index = 0;
    bn::vector<bn::pair<int, short>, 4> _action_order;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 30> _battle_text;
    bn::vector<bn::sprite_ptr, 5> _damage_text;
    bn::vector<bn::sprite_ptr, 6> _turn_text;

    short _current_turn = 0;

    bn::unique_ptr<Battle_Sequence>& _battle_sq;
    bn::vector<Enemy::Enemy, 3>& _enemies;
    short _num_enemies = 3;
    bn::vector<bn::sprite_ptr, 3> _enemy_sprite;
    //bn::sprite_ptr _player_sprite;
    //bn::vector<bn::sprite_ptr, 3> _enemy_hp_sprite;

    bn::sprite_ptr _sword_attack_icon;
    bn::sprite_ptr _shield_icon;
    bn::sprite_ptr _magic_attack_icon;
    bn::sprite_ptr _cursor;
    short _enemy_x[3] = {-60, 0, 60};

    Next_action _attack_type = Next_action::Slash;
    int _magic_index = 0;
    short _target_index = 0;
    int _left_hit = 0;

    bn::sprite_ptr _attack_effect_sprite;
    bn::sprite_animate_action<9> _attack_effect;

    Effect::Transition _text_end;
    Effect::Transition _enemy_end;
    int _effect_cooltime = 10;
    int _damage_text_cooltime = 10;
    int _enemy_dead_cooltime = 10;

    Effect::Camera _camera;
};

} // namespace Runa::Game

#endif // GAME_BATTLE_H
