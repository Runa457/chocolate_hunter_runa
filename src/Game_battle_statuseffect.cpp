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
            if (_duration[i] <= 0)
            {
                _inner_index[i] = Status_effect_index::None;
                _duration[i] = 0;
            }
            return;
        }
    }
    if (turns < 0) { return; }
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

const bn::string_view Print_status_effect(Status_effect_index status)
{
    switch (status)
    {
    case Status_effect_index::None:
        return "None";
    case Status_effect_index::Attack_up:
        return "Atk. Up";
    case Status_effect_index::Attack_down:
        return "Atk. Down";
    case Status_effect_index::Defence_up:
        return "Def. Up";
    case Status_effect_index::Defence_down:
        return "Def. Down";
    case Status_effect_index::Speed_up:
        return "Spd. Up";
    case Status_effect_index::Speed_down:
        return "Spd. Down";
    case Status_effect_index::Charge:
        return "Charge";
    case Status_effect_index::Guard:
        return "Guard";
    case Status_effect_index::Bleeding:
        return "Bleeding";
    case Status_effect_index::Poison:
        return "Poison";
    case Status_effect_index::Regenerate:
        return "Regen";
    default:
        BN_ERROR("Not implemented status effect");
        break;
    }
}

} // namespace Runa::Game
