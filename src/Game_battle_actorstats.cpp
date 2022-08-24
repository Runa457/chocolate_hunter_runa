#include "Game_battle_actorstats.h"

namespace Runa::Game
{

ActorStats::ActorStats() :
    _atk(0), _weapon(0), _def(0), _armor(0),
    _intelligence(0), _status_effect(Status_effect::None)
{}
ActorStats::ActorStats(int atk, int weapon, int def, int armor,
                       int intelligence, Status_effect status_effect):
    _atk(atk), _weapon(weapon), _def(def), _armor(armor),
    _intelligence(intelligence), _status_effect(status_effect)
{}

ActorStats::~ActorStats() {}

int ActorStats::Get_atk() { return _atk; }
int ActorStats::Get_weapon() { return _weapon; }
int ActorStats::Get_def() { return _def; }
int ActorStats::Get_armor() { return _armor; }
int ActorStats::Get_int() { return _intelligence; }
Status_effect ActorStats::Get_status_effect() { return _status_effect; }

void ActorStats::Set_status_effect(Status_effect next_status)
{
    _status_effect = static_cast<Status_effect>(_status_effect | next_status); // << todo: status cancelled/ done
}

} // namespace Runa::Game
