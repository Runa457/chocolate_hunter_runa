#include "Battle_sequence.h"

#include "bn_random.h"

namespace Runa::Game
{

Battle_Sequence::Battle_Sequence(int player_level, bool is_boss) :
    _is_boss(is_boss),
    _current_sequence(1),
    _total_choco(0),
    _total_enemy(0)
{
    bn::random randint;
    _num_sequence = randint.get_int(1, 3);
    for (int i = 0; i < _num_sequence; i++)
    {
        _enemys.push_back(bn::vector<Enemy::Enemy, 3>());
        int num_enemy = randint.get_int(1, 3);
        for (int j = 0; j < num_enemy; j++)
        {
            _enemys[i].push_back(Enemy::Enemy(0, player_level - randint.get_int(3)));
            _total_choco += _enemys[i][j].Get_choco();
        }
        _total_enemy += num_enemy;
    }
}
Battle_Sequence::~Battle_Sequence() {}

} // namespace Runa::Game
