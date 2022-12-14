#ifndef GAME_BATTLE_ACTORSTATS_H
#define GAME_BATTLE_ACTORSTATS_H

#include "Enemy_data.h"
#include "Game_battle_action.h"
#include "Game_battle_statuseffect.h"

namespace Runa::Game
{

class ActorStats
{
public:
    ActorStats();
    ActorStats(int atk, int weapon, int def, int armor,
               int intelligence, int spd);
    ActorStats(int atk, int def, int intelligence, int spd,
               const Enemy::Enemy_data& base_data);
    ~ActorStats();

    int Get_atk();
    int Get_base_atk();
    int Get_weapon();
    int Get_def();
    int Get_base_def();
    int Get_armor();
    int Get_int();
    int Get_base_int();
    int Get_final_spd();
    int Get_spd();
    int Get_base_spd();
    Status_effect_index Get_status_effect();
    Status_effect_index Get_status_effect(int index);
    int Get_weakness(int index);
    const Action::Action* Get_action_type();

    void Set_status_effect(Status_effect_index next_status, int turns);
    void Remove_status_effect();
    void Turn_passed();
    void Set_action_type(const Action::Action* action);

private:
    int _atk;
    int _weapon;
    int _def;
    int _armor;
    int _intelligence;
    int _spd;
    Status_effect _status_effect;
    Status_effect_index _current_status;
    const Enemy::Element_weakness* _element_weak = nullptr;
    const Action::Action* _action_type;
};

} // namespace Runa::Game

#endif // GAME_BATTLE_ACTORSTATS_H
