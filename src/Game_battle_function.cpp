#include "Game_battle_function.h"
#include "Damage_formula.h"
#include "Stats_data.h"

#include "bn_format.h"
#include "bn_sound_items.h"
#include "bn_sprite_items_effect_sword.h"

namespace Runa::Game
{

int attack_function(Status& status, Attack_type attack_type,
                    Enemy::Enemy* attacker, Enemy::Enemy* defender)
{
    int atk_pow;
    int weapon = 0;
    int def_pow;
    int armor = 0;
    if (attacker == nullptr)
    {
        if (attack_type == Attack_type::Sword_attack) { atk_pow = Get_str_data(status.Get_level()); }
        else { atk_pow = Get_int_data(status.Get_level()) * 2; }
        weapon = Get_weapon_data(status.Get_weapon());
    }
    else { atk_pow = attacker->Get_atk(); }
    if (defender == nullptr)
    {
        def_pow = Get_def_data(status.Get_level());
        armor = Get_armor_data(status.Get_armor());
    }
    else { def_pow = defender->Get_def(); }

    int damage = Damage_calculator(atk_pow, weapon, def_pow, armor);

    if (defender == nullptr) { status.Hp_change(-damage); }
    else { defender->Hp_change(-damage); }

    return damage;
}

void attack_effect(bn::sprite_text_generator& _text_generator,
                   int x, int y, int damage,
                   Attack_type attack_type,
                   bn::ivector<bn::sprite_ptr>& _damage_text,
                   bn::sprite_ptr& _attack_effect_sprite,
                   bn::sprite_animate_action<9>& _attack_effect)
{
    _attack_effect_sprite.set_position(x, y);
    _attack_effect_sprite.set_visible(true);

    switch (attack_type)
    {
    case Attack_type::Enemy_normal_attack:
        _attack_effect = bn::create_sprite_animate_action_once(_attack_effect_sprite, 1, bn::sprite_items::effect_sword.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8);
        bn::sound_items::sfx_battle_damage_taken.play();
        break;
    case Attack_type::Sword_attack:
        _attack_effect = bn::create_sprite_animate_action_once(_attack_effect_sprite, 1, bn::sprite_items::effect_sword.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8);
        bn::sound_items::sfx_battle_sword.play();
        break;
    case Attack_type::Magic_fire:
        _attack_effect = bn::create_sprite_animate_action_once(_attack_effect_sprite, 1, bn::sprite_items::effect_sword.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8);
        bn::sound_items::sfx_battle_magic.play();
        break;
    case Attack_type::Defence:
        return;
    default:
        _attack_effect = bn::create_sprite_animate_action_once(_attack_effect_sprite, 1, bn::sprite_items::effect_sword.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8);
        bn::sound_items::sfx_battle_sword.play();
        break;
    }
    _text_generator.generate(x, y-25, bn::format<5>("{}", damage), _damage_text);
    for (bn::sprite_ptr& text : _damage_text)
    {
        text.set_visible(false);
        text.set_blending_enabled(true);
    }
}

} // namespace Runa::Game
