#include "Game_battle_actorstats.h"

namespace Runa::Game
{

ActorStats::ActorStats() :
    _atk(0), _weapon(0), _def(0), _armor(0),
    _intelligence(0), _status_effect(Status_effect::None),
    _action_type(&Action::Get_action_data(Action::Action_index::Bash))
{}
ActorStats::ActorStats(int atk, int weapon, int def, int armor,
                       int intelligence, int spd, Status_effect status_effect):
    _atk(atk), _weapon(weapon), _def(def), _armor(armor),
    _intelligence(intelligence), _spd(spd), _status_effect(status_effect),
    _action_type(&Action::Get_action_data(Action::Action_index::Bash))
{}

ActorStats::~ActorStats() {}

int ActorStats::Get_atk()
{
    if (_status_effect & Status_effect::Attack_up) { return _atk * 13 / 10; }
    else if (_status_effect & Status_effect::Attack_down) { return _atk * 7 / 10; }
    else { return _atk; }
}
int ActorStats::Get_weapon() { return _weapon; }
int ActorStats::Get_def()
{
    if (_status_effect & Status_effect::Defence_up) { return _def * 13 / 10; }
    else if (_status_effect & Status_effect::Defence_down) { return _def * 7 / 10; }
    else { return _def; }
}
int ActorStats::Get_armor() { return _armor; }
int ActorStats::Get_int() { return _intelligence; }
int ActorStats::Get_spd()
{
    if (_status_effect & Status_effect::Speed_up) { return _spd * 13 / 10; }
    else if (_status_effect & Status_effect::Speed_down) { return _spd * 7 / 10; }
    else { return _spd; }
}
Status_effect ActorStats::Get_status_effect() { return _status_effect; }
const Action::Action* ActorStats::Get_action_type() { return _action_type; }

void ActorStats::Set_status_effect(Status_effect next_status)
{
    _status_effect = static_cast<Status_effect>(_status_effect | next_status); // << todo: status cancelled/ done
}
void ActorStats::Set_action_type(const Action::Action* action)
{
    _action_type = action;
}

} // namespace Runa::Game
