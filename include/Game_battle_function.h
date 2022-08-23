#ifndef GAME_BATTLE_FUNCTION_H
#define GAME_BATTLE_FUNCTION_H

#include "Effect_transition.h"
#include "Enemy.h"
#include "Status.h"

#include "bn_sprite_animate_actions.h"
#include "bn_sprite_text_generator.h"

namespace Runa::Game
{

enum class Action_type // <---WIP
{
    None,
    Normal_type,
    Magic_type,
    Self_type,
};

enum class Attack_type
{
    None,
    Enemy_normal_attack,
    Sword_attack,
    Magic_fire,
    Defence,
};

/**
 * @brief Handles attack damage calculation, pre/post processing.
 * @param Player data.
 * @param Attck type.
 * @param nullopt if attacker is player
 * @param nullopt if defender is player
 * @return Damage for effects
 */
int attack_function(Status& status, Attack_type attack_type,
                    Enemy::Enemy* attacker, Enemy::Enemy* defender);

/**
 * @brief Handles attack effects.
 * @param _text_generator
 * @param x coordinate of defender.
 * @param y coordinate of defender.
 * @param damage
 * @param text sprites for damage text.
 * @param _attack_effect_sprite
 * @param _attack_effect
 */
void attack_effect(bn::sprite_text_generator& _text_generator,
                   int x, int y, int damage,
                   Attack_type attack_type,
                   bn::ivector<bn::sprite_ptr>& _damage_text,
                   bn::sprite_ptr& _attack_effect_sprite,
                   bn::sprite_animate_action<9>& _attack_effect);

} // namespace Runa::Game

#endif // GAME_BATTLE_FUNCTION_H
