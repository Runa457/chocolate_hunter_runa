#include "Battle_sequence.h"
#include "Stats_data.h"

namespace Runa::Game
{

constexpr int MAXSTRATUM = 3;

Battle_Sequence::Battle_Sequence(bn::random& random_generator,
                                 int player_level, short stratum, bool is_boss) :
    _random(random_generator),
    _is_boss(is_boss),
    _current_sequence(0),
    _total_choco(0),
    _total_enemy(0)
{
    if (stratum > MAXSTRATUM) { stratum = MAXSTRATUM; }
    short enemy_index_start = Get_enemy_index(stratum-1) + 1;
    short enemy_index_end = Get_enemy_index(stratum);

    if (is_boss)
    {
        _num_sequence = 1;
        _total_enemy = 1;
        _enemies.push_back(bn::vector<Enemy::Enemy, 3>());
        _enemies[0].push_back(Enemy::Enemy(enemy_index_end, stratum * 10));
        _total_choco = _enemies[0][0].Get_choco();
    }
    else
    {
        _num_sequence = _random.get_int(1, 5);
        for (int i = 0; i < _num_sequence; i++)
        {
            _enemies.push_back(bn::vector<Enemy::Enemy, 3>());
            int num_enemy = _random.get_int(1, 4);
            for (int j = 0; j < num_enemy; j++)
            {
                int enemy_index = _random.get_int(enemy_index_start, enemy_index_end);
                int enemy_level = bn::min(bn::max((stratum - 1) * 10, player_level + _random.get_int(-1, 3)), stratum * 10 - 1);
                _enemies[i].push_back(Enemy::Enemy(enemy_index, enemy_level));
                _total_choco += _enemies[i][j].Get_choco();
            }
            _total_enemy += num_enemy;
        }
    }
}
Battle_Sequence::~Battle_Sequence() {}

bool Battle_Sequence::Get_is_boss() { return _is_boss; }
short Battle_Sequence::Get_curr_seq() { return _current_sequence; }
short Battle_Sequence::Get_num_seq() { return _num_sequence; }
int Battle_Sequence::Get_total_choco() { return _total_choco; }
int Battle_Sequence::Get_total_enemy() { return _total_enemy; }

bool Battle_Sequence::To_next_seq()
{
    return ++_current_sequence < _num_sequence;
}

bn::vector<Enemy::Enemy, 3>& Battle_Sequence::Get_current_enemies()
{
    return _enemies[_current_sequence];
}

} // namespace Runa::Game
