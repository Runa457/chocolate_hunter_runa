#include "Enemy.h"

namespace Runa::Game::Enemy
{

Enemy::Enemy(int _index, short _level) :
    _base_data(Get_enemy_base_data(_index)),
    level(_level)
{
    Init();
}

void Enemy::Init()
{
    // hp = 5% increase per level
    maxhp = hp = _base_data.base_maxhp * (100 + level * 5) / 100;
    // atk, def = 10% increase per level
    atk = _base_data.base_atk * (100 + level * 10) / 100;
    def = _base_data.base_def * (100 + level * 10) / 100;
    // spd = 1% increase per level
    spd = _base_data.base_spd * (100 + level * 1) / 100;
}
int Enemy::Get_exp()
{
    // exp = 10% increase per level
    return _base_data.base_exp * (100 + level * 10) / 100;
}
int Enemy::Get_choco()
{
    return _base_data.base_choco;
}
bool Enemy::Hp_change(short increment)
{
    hp += increment;
    if (hp > maxhp) { hp = maxhp; }
    else if (hp <= 0) { return true; }
    return false;
}

} // namespace Runa::Game::Enemy