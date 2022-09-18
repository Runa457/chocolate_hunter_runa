#include "Game_battle_function.h"
#include "Damage_formula.h"

//#include "bn_log.h"

namespace Runa::Game
{

int attack_function(ActorStats* attacker, ActorStats* defender,
                    bn::random& random)
{
    const Action::Action* action = attacker->Get_action_type();
    int atk_pow;
    int weapon = attacker->Get_weapon();
    int def_pow = defender->Get_def();
    int armor = defender->Get_armor();

    if (action->_action == Action::Action_type::Normal_attack)
        { atk_pow = attacker->Get_atk(); }
    else { atk_pow = attacker->Get_int(); }

    if (action->_multiplier < 0) { def_pow = atk_pow; armor = 0; }

    double damage = Damage_calculator(atk_pow, weapon, def_pow, armor);
    //BN_LOG((int)damage, " ", atk_pow, " ", weapon, " ", def_pow, " ", armor);

    damage *= action->_multiplier;
    damage *= defender->Get_weakness((int)action->_element);

    Status_effect_index attacker_status = attacker->Get_status_effect();
    Status_effect_index defender_status = defender->Get_status_effect();

    if ((attacker_status & Status_effect_index::Charge) != 0)
    {
        damage = damage * 2;
    }
    if (damage > 0 && (defender_status & Status_effect_index::Bleeding) != 0)
    {
        damage = damage * 3 / 2;
    }

    damage += (damage > 0) ? 5000 : -5000;

    if (damage > 0 && (defender_status & Status_effect_index::Guard) != 0)
    {
        damage = damage / 2;
    }

    damage /= 10000; // multiplier 100%, weakness 100%

    int chance = random.get_int(100);
    if (chance < action->_status_chance)
    {
        defender->Set_status_effect(action->_status_effect, action->_status_duration);
    }
    //BN_LOG(chance, " ", action->_status_chance, " ", defender->Get_status_effect());

    return damage;
}

int end_of_turn(ActorStats* actor)
{
    int atk_pow = actor->Get_atk();
    int def_pow = actor->Get_def();
    double damage = 0;

    Status_effect_index status = actor->Get_status_effect();
    if ((status & Status_effect_index::Poison) != 0)
    {
        damage += Damage_calculator(atk_pow, 0, atk_pow, 0);
    }
    if ((status & Status_effect_index::Regenerate) != 0)
    {
        damage -= Damage_calculator(def_pow, 0, def_pow, 0);
    }
    return damage;
}

} // namespace Runa::Game
