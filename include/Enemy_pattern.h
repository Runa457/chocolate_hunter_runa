#ifndef ENEMY_PATTERN_H
#define ENEMY_PATTERN_H

#include "Game_battle_action.h"

namespace Runa::Game::Enemy
{

enum class Pattern_index : short
{
    Slash,
    Bash,
    Throw,
    TripleSlash,

    Guard_Slash,
    Charge_Bash,
    Charge_Confusion,
    Charge_Fire,
    Charge_Ice,
    Charge_Lightning,

    Quicksand,
    FireIce,

    Explosion,

    Confusion,

    Guard,
    Heal,
    AreaHeal,

    Charge_AreaHeal,

    Healer,

    Pawn_Black,
    Pawn_White,
    Knight_Black,
    Knight_White,
    Bishop_Black,
    Bishop_White,
    Rook_Black,
    Rook_White,
    Queen_Black,
    Queen_White,
    King_Black,
    King_White,

    Boss_1,
    Boss_2,
    Boss_3,
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
