#ifndef GAME_BATTLE_H
#define GAME_BATTLE_H

#include "Game.h"
#include "Battle_sequence.h"

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
    enum class State
    {
        Start_turn,
        Action_select,
        Target_select,
        Confirm,
        Turn_action,
        End_turn
    };

    void Print_text();

    /**
     * @brief Called at start of battle.
     * Create sprite of enemies.
     */
    void Battle_start();
    bool Action_select(); // bool -> state
    bool Target_select(); // same
    bool Confirm();
    void Turn_action();

    /**
     * @brief Called at end of battle.
     * @return Returns true if last sequence is ended.
     */
    bool Battle_end();

    Status& _status;
    State _state;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 20> _battle_text;
    bn::vector<bn::sprite_ptr, 5> _damage_text;

    bn::unique_ptr<Battle_Sequence>& _battle_sq;
    bn::vector<Enemy::Enemy, 3>& _enemies;
    short _num_enemies;
    bn::vector<bn::sprite_ptr, 3> _enemy_sprite;
    bn::vector<bn::sprite_ptr, 3> _enemy_hp_sprite;

    bn::sprite_ptr _cursor;
    /**
     * @brief false : melee type, true : magic type
     */
    short _enemy_x[3] = {-60, 0, 60};
    bool _attack_type;
    short _target_index;
};

} // namespace Runa::Game

#endif // GAME_BATTLE_H
