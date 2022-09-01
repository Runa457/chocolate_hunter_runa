#include "Game_battle_statuseffect.h"

namespace Runa::Game
{

Status_effect::Status_effect() :
    _inner_index{Status_effect_index::None},
    _duration{0}
{
    Remove_status_effect();
}

Status_effect::~Status_effect() {}

Status_effect_index Status_effect::Get_status_effect()
{
    Status_effect_index _index = Status_effect_index::None;
    for (int i = 0; i < MAX_STATUS_NUMBER; i++)
    {
        _index = static_cast<Status_effect_index>(_index | _inner_index[i]);
    }
    return _index;
}

void Status_effect::Set_status_effect(Status_effect_index next_status, int turns)
{
    // check if status effect is already active
    for (int i = 0; i < MAX_STATUS_NUMBER; i++)
    {
        if (_inner_index[i] == next_status)
        {
            _duration[i] += turns;
            return;
        }
    }
    // check if status effect could be cancelled
    for (int i = 0; i < MAX_STATUS_NUMBER; i++)
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
    for (int i = 0; i < MAX_STATUS_NUMBER; i++)
    {
        if (_inner_index[i] == Status_effect_index::None)
        {
            _inner_index[i] = next_status;
            _duration[i] = turns;
            return;
        }
    }
}
void Status_effect::Remove_status_effect()
{
    for (int i = 0; i < MAX_STATUS_NUMBER; i++)
    {
        _inner_index[i] = Status_effect_index::None;
        _duration[i] = 0;
    }
}
void Status_effect::Turn_passed()
{
    for (int i = 0; i < MAX_STATUS_NUMBER; i++)
    {
        if (--_duration[i] <= 0)
        {
            _inner_index[i] = Status_effect_index::None;
        }
    }
}

} // namespace Runa::Game
