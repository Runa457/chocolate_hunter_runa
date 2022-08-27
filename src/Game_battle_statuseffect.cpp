#include "Game_battle_statuseffect.h"

namespace Runa::Game
{

Status_effect::Status_effect() :
    _index(Status_effect_index::None),
    _inner_index{Status_effect_index::None, Status_effect_index::None, Status_effect_index::None},
    _duration{0, 0, 0}
{}

Status_effect::~Status_effect() {}

Status_effect_index Status_effect::Get_status_effect() { return _index; }

void Status_effect::Set_status_effect(Status_effect_index next_status, int turns)
{
    // check if status effect is already active
    for (int i = 0; i < 3; i++)
    {
        if (_inner_index[i] == next_status)
        {
            _duration[i] += turns;
            return;
        }
    }
    // check if status effect could be cancelled
    for (int i = 0; i < 3; i++)
    {
        int temp = _inner_index[i] + next_status;
        if ((temp == 3) || (temp == 12) || (temp == 48))
        {
            _inner_index[i] = Status_effect_index::None;
            _duration[i] = 0;
            return;
        }
    }
    // check if there is room for new status effect
    for (int i = 0; i < 3; i++)
    {
        if (_inner_index[i] == Status_effect_index::None)
        {
            _inner_index[i] = next_status;
            _duration[i] = turns;
        }
    }
    _index = static_cast<Status_effect_index>(_inner_index[0] | _inner_index[1] | _inner_index[2]);
}
void Status_effect::Remove_status_effect()
{
    for (int i = 0; i < 3; i++)
    {
        _inner_index[i] = Status_effect_index::None;
        _duration[i] = 0;
    }
    _index = Status_effect_index::None;
}
void Status_effect::Turn_passed()
{
    for (int i = 0; i < 3; i++)
    {
        if (--_duration[i] <= 0)
        {
            _index = static_cast<Status_effect_index>(_index - _inner_index[i]);
            _inner_index[i] = Status_effect_index::None;
        }
    }
    _index = static_cast<Status_effect_index>(_inner_index[0] | _inner_index[1] | _inner_index[2]);
}

} // namespace Runa::Game
