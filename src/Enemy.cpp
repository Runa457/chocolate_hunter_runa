#include "Enemy.h"
#include "bn_sprite_ptr.h"

namespace Runa::Game::Enemy
{

Enemy::Enemy(int _index, short _level) :
    _base_data(Get_enemy_base_data(_index)),
    level(_level)
{
    Init();
}
Enemy::~Enemy() {}

void Enemy::Init()
{
    // hp = 10% increase per level
    maxhp = hp = _base_data.base_maxhp * (100 + level * 10) / 100;
    // atk, def, int = 5% increase per level
    int atk = _base_data.base_atk * (100 + level * 5) / 100;
    int def = _base_data.base_def * (100 + level * 5) / 100;
    int inteligence = _base_data.base_atk * (100 + level * 5) / 100;
    // spd = 3% increase per level
    spd = _base_data.base_spd * (100 + level * 3) / 100;

    _stats = ActorStats(atk, 0, def, 0, inteligence, Status_effect::None);
}

const bn::string_view& Enemy::Get_name() { return _base_data.name; }
const short& Enemy::Get_level() { return level; }
int Enemy::Get_hp() { return hp; }
const int& Enemy::Get_spd() { return spd; }
int Enemy::Get_exp()
{
    // exp = 5% increase per level
    return (int)_base_data.base_exp * (100 + level * 5) / 100;
}
short Enemy::Get_choco() { return _base_data.base_choco; }

bool Enemy::Hp_change(short increment)
{
    hp += increment;
    if (hp > maxhp) { hp = maxhp; }
    else if (hp <= 0) { hp = 0; return true; }
    return false;
}

bool Enemy::Is_dead() { return hp <= 0; }

void Enemy::Sprite_create(short x, short y, bn::ivector<bn::sprite_ptr>& sprite)
{
    sprite.push_back(bn::sprite_ptr(_base_data.sprite_item.create_sprite(x, y)));
}

} // namespace Runa::Game::Enemy
