#ifndef ENEMY_PATTERN_H
#define ENEMY_PATTERN_H

#include "Game_battle_action.h"

namespace Runa::Game::Enemy
{

enum class Pattern_index : short
{
    Guard,
    Heal,
    Slash,
    Bash,
    Throw,
    TripleSlash,
    AreaHeal,

    Guard_Slash,
    Confusion,
    Charge_Bash,
    Charge_AreaHeal,

    Quicksand,

    Explosion,

    Boss_1,
    Boss_2,
};

class Enemy_pattern
{
public:
    constexpr Enemy_pattern(int length, const Action::Action_index* actions) :
        _length(length), _actions(actions)
    {}

    const Action::Action_index& Get_action(int turn)const
    {
        return _actions[(turn-1) % _length];
    }

protected:
    int _length;
    const Action::Action_index* _actions;

};

const Enemy_pattern& Get_enemy_pattern_data(Pattern_index index);

} // namespace Runa::Game::Enemy

#endif // ENEMY_PATTERN_H
