#ifndef GAME_BATTLE_ACTION_H
#define GAME_BATTLE_ACTION_H

#include "bn_sprite_item.h"

namespace Runa::Game::Action
{

enum class Target_type : char
{
    None,
    Self_target,
    Single_target,
    Multi_target,
    Entire_target
};

enum class Action_type : char
{
    None,
    Normal_attack,
    Magic_attack,
    Status_attack,
};

class Action
{
public:
    constexpr Action(const bn::sprite_item& attack_effect,
                     Target_type target, Action_type action,
                     int multiplier, int status_chance) :
        _attack_effect(attack_effect),
        _target(target),
        _action(action),
        _multiplier(multiplier),
        _status_chance(status_chance)
    {}

    const bn::sprite_item& _attack_effect;
    Target_type _target;
    Action_type _action;
    int _multiplier;
    int _status_chance;
};

} // namespace Runa::Game


#endif // GAME_BATTLE_ACTION_H
