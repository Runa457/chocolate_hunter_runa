#ifndef BATTLE_SEQUENCE_H
#define BATTLE_SEQUENCE_H

#include "Enemy.h"

#include "bn_vector.h"
#include "bn_random.h"

namespace Runa::Game
{

class Battle_Sequence
{
public:
    Battle_Sequence(bn::random& random_generator,
                    int player_level, short stratum, bool is_boss); // short stratum_num
    ~Battle_Sequence();

    bool Get_is_boss();
    short Get_curr_seq();
    short Get_num_seq();
    int Get_total_choco();
    int Get_total_enemy();

    /**
     * @brief Increase current sequence index by 1.
     * @return Return false if last sequence ends.
     */
    bool To_next_seq();

    bn::vector<Enemy::Enemy, 3>& Get_current_enemies();

private:
    bn::random& _random;

    bool _is_boss;
    short _num_sequence;
    short _current_sequence;
    int _total_choco;
    int _total_enemy;

    bn::vector<bn::vector<Enemy::Enemy, 3>, 5> _enemies;

};

} // namespace Runa::Game

#endif // BATTLE_SEQUENCE_H
