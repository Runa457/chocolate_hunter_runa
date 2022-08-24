#include "Game_battle_function.h"
#include "Damage_formula.h"

#include "bn_format.h"
//#include "bn_log.h"

namespace Runa::Game
{
/*
namespace
{

const bn::span<const uint16_t> graphics_indexes(int num_frames)
{
    bn::span<const uint16_t> out;
    for (int i = 0; i < num_frames; i++)
    {}
    return out;
}

} // namespace
*/
int attack_function(const Action::Action* action,
                    ActorStats* attacker, ActorStats* defender)
{
    int atk_pow;
    int weapon = attacker->Get_weapon();
    int def_pow = defender->Get_def();
    int armor = defender->Get_armor();

    if (action->_action == Action::Action_type::Normal_attack)
        { atk_pow = attacker->Get_atk(); }
    else { atk_pow = attacker->Get_int(); }

    int damage = Damage_calculator(atk_pow, weapon, def_pow, armor);
    //BN_LOG(damage, " ", atk_pow, " ", weapon, " ", def_pow, " ", armor);

    damage = damage * action->_multiplier / 100;

    if ((attacker->Get_status_effect() & Status_effect::Charge) != 0)
    {
        damage = damage * 150 / 100;
    }
    if ((defender->Get_status_effect() & Status_effect::Guard) != 0)
    {
        damage = damage / 2;
    }
    return damage;
}

void attack_effect(bn::sprite_text_generator& _text_generator,
                   int x, int y, int damage,
                   const Action::Action* action,
                   bn::ivector<bn::sprite_ptr>& _damage_text,
                   bn::sprite_ptr& _attack_effect_sprite,
                   bn::sprite_animate_action<9>& _attack_effect)
{
    _attack_effect_sprite.set_position(x, y);
    _attack_effect_sprite.set_visible(true);
    _attack_effect = bn::create_sprite_animate_action_once(_attack_effect_sprite, 1, action->_action_effect.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8);

    action->_action_sound.play();

    _text_generator.generate(x, y-25, bn::format<5>("{}", damage), _damage_text);
    for (bn::sprite_ptr& text : _damage_text)
    {
        text.set_visible(false);
        text.set_blending_enabled(true);
    }
}

} // namespace Runa::Game
