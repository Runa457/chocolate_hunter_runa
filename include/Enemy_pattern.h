#ifndef ENEMY_PATTERN_H
#define ENEMY_PATTERN_H

#include "Game_battle_action.h"

namespace Runa::Game::Enemy
{

enum Pattern_index : short
{
    Bash,
    Guard,
    Bash_Guard,
    Boss_1,
};

class Enemy_pattern
{
public:
    constexpr Enemy_pattern(int length, const Action::Action_index* actions) :
        _length(length), _actions(actions)
    {}

    const Action::Action_index& Get_action(int turn)const
    {
        return _actions[turn % _length];
    }

protected:
    int _length;
    const Action::Action_index* _actions;

};

const Enemy_pattern& Get_enemy_pattern_data(Pattern_index index);

} // namespace Runa::Game::Enemy

#endif // ENEMY_PATTERN_H
