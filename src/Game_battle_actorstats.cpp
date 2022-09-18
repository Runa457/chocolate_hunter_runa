#include "Game_battle_actorstats.h"

namespace Runa::Game
{

ActorStats::ActorStats() :
    _atk(0), _weapon(0), _def(0), _armor(0),
    _intelligence(0), _status_effect(), _current_status(),
    _element_weak(&Enemy::Get_enemy_base_data(0).element_weak),
    _action_type(&Action::Get_action_data(Action::Action_index::Bash))
{}
ActorStats::ActorStats(int atk, int weapon, int def, int armor,
                       int intelligence, int spd):
    _atk(atk), _weapon(weapon), _def(def), _armor(armor),
    _intelligence(intelligence), _spd(spd), _status_effect(), _current_status(),
    _element_weak(&Enemy::Get_enemy_base_data(0).element_weak),
    _action_type(&Action::Get_action_data(Action::Action_index::Bash))
{}
ActorStats::ActorStats(int atk, int def, int intelligence, int spd,
                       const Enemy::Enemy_data &base_data):
    _atk(atk), _weapon(0), _def(def), _armor(0),
    _intelligence(intelligence), _spd(spd), _status_effect(), _current_status(),
    _element_weak(&base_data.element_weak),
    _action_type(&Action::Get_action_data(Action::Action_index::Bash))
{}

ActorStats::~ActorStats() {}

int ActorStats::Get_atk()
{
    if (_current_status & Status_effect_index::Attack_up) { return _atk * 13 / 10; }
    else if (_current_status & Status_effect_index::Attack_down) { return _atk * 7 / 10; }
    else { return _atk; }
}
int ActorStats::Get_base_atk() { return _atk; }
int ActorStats::Get_weapon() { return _weapon; }
int ActorStats::Get_def()
{
    if (_current_status & Status_effect_index::Defence_up) { return _def * 13 / 10; }
    else if (_current_status & Status_effect_index::Defence_down) { return _def * 7 / 10; }
    else { return _def; }
}
int ActorStats::Get_base_def() { return _def; }
int ActorStats::Get_armor() { return _armor; }
int ActorStats::Get_int()
{
    if (_current_status & Status_effect_index::Attack_up) { return _intelligence * 13 / 10; }
    else if (_current_status & Status_effect_index::Attack_down) { return _intelligence * 7 / 10; }
    else { return _intelligence; }
}
int ActorStats::Get_spd()
{
    int spd = _spd * _action_type->_speed;
    if (_current_status & Status_effect_index::Speed_up) { spd = spd * 13 / 10; }
    else if (_current_status & Status_effect_index::Speed_down) { spd = spd * 7 / 10; }
    return spd / 100;
}
int ActorStats::Get_base_spd() { return _spd; }
Status_effect_index ActorStats::Get_status_effect() { return _current_status; }
int ActorStats::Get_weakness(int index) { return _element_weak->Get_weakness(index); }
const Action::Action* ActorStats::Get_action_type() { return _action_type; }

void ActorStats::Set_status_effect(Status_effect_index next_status, int turns)
{
    _status_effect.Set_status_effect(next_status, turns);
    _current_status = _status_effect.Get_status_effect();
}
void ActorStats::Remove_status_effect()
{
    _status_effect.Remove_status_effect();
    _current_status = _status_effect.Get_status_effect();
}
void ActorStats::Turn_passed()
{
    _status_effect.Turn_passed();
    _current_status = _status_effect.Get_status_effect();
}
void ActorStats::Set_action_type(const Action::Action* action)
{
    _action_type = action;
}

} // namespace Runa::Game
