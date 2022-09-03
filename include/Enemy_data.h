#ifndef ENEMY_DATA_H
#define ENEMY_DATA_H

#include "Enemy_pattern.h"

#include "bn_sprite_item.h"
#include "bn_string_view.h"

namespace Runa::Game::Enemy
{

struct Element_weakness
{
public:
    constexpr Element_weakness() :
        _weakness{0}
    {}
    constexpr Element_weakness(int physical, int fire, int ice, int lightning) :
        _weakness{100, physical, fire, ice, lightning}
    {}

    int Get_weakness(int index)const { return _weakness[index]; }
private:

    int _weakness[10];
};

class Enemy_data
{
public:
    constexpr Enemy_data(const bn::sprite_item& _sprite_item, bn::string_view _name,
                         short _base_exp, short _base_choco,
                         short _base_maxhp, short _base_atk, short _base_def, short _base_spd,
                         Pattern_index _pattern_index,
                         int physical, int fire, int ice, int lightning) :
        sprite_item(_sprite_item),
        name(_name),
        base_exp(_base_exp), base_choco(_base_choco),
        base_maxhp(_base_maxhp), base_atk(_base_atk), base_def(_base_def), base_spd(_base_spd),
        pattern_index(_pattern_index),
        element_weak(physical, fire, ice, lightning)
    {}

    const bn::sprite_item& sprite_item;
    bn::string_view name;
    short base_exp, base_choco;
    short base_maxhp;
    short base_atk, base_def, base_spd;
    Pattern_index pattern_index;
    const Element_weakness element_weak;
    //AI_type ai;
};

const Enemy_data& Get_enemy_base_data(int index);

} // namespace Runa::Game::Enemy

#endif // ENEMY_DATA_H
