#ifndef BATTLE_SEQUENCE_H
#define BATTLE_SEQUENCE_H

#include "Enemy.h"

#include "bn_vector.h"

namespace Runa::Game
{

class Battle_Sequence
{
public:
    Battle_Sequence(int player_level, bool is_boss); // short stratum_num
    ~Battle_Sequence();

private:
    bool _is_boss;
    int _num_sequence;
    int _current_sequence;
    int _total_choco;
    int _total_enemy;

    bn::vector<bn::vector<Enemy::Enemy, 3>, 3> _enemys;

};

} // namespace Runa::Game

#endif // BATTLE_SEQUENCE_H
