#ifndef GAME_BATTLE_H
#define GAME_BATTLE_H

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
    void Turn_action();
    bool Effect_action();
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
    State _state;
    short _action_order;
    bn::vector<bn::pair<int, short>, 4> _attack_order;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 30> _battle_text;
    bn::vector<bn::sprite_ptr, 5> _damage_text;
    bn::vector<bn::sprite_ptr, 6> _turn_text;

    short _current_turn = 0;

    bn::unique_ptr<Battle_Sequence>& _battle_sq;
    bn::vector<Enemy::Enemy, 3>& _enemies;
    short _num_enemies;
    bn::vector<bn::sprite_ptr, 3> _enemy_sprite;
    //bn::vector<bn::sprite_ptr, 3> _enemy_hp_sprite;

    bn::sprite_ptr _sword_attack_sprite;
    bn::sprite_ptr _magic_attack_sprite;
    bn::sprite_ptr _cursor;
    short _enemy_x[3] = {-60, 0, 60};
    /**
     * @brief false : melee type, true : magic type
     */
    bool _attack_type;
    Attack_type _attack_type_final;
    short _target_index;

    bn::sprite_ptr _attack_effect_sprite;
    bn::sprite_animate_action<9> _attack_effect;

    Effect::Transition _text_end;
    Effect::Transition _enemy_end;
    int _effect_cooltime = 1; //10;
    int _damage_text_cooltime = 10;
    int _enemy_dead_cooltime = 10;
};

} // namespace Runa::Game

#endif // GAME_BATTLE_H
