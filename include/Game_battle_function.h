#ifndef GAME_BATTLE_FUNCTION_H
#define GAME_BATTLE_FUNCTION_H

#include "Game_battle_actorstats.h"
#include "Game_battle_action.h"

#include "bn_random.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_text_generator.h"

namespace Runa::Game
{

/**
 * @brief Handles attack damage calculation, pre/post processing.
 * @param Player data.
 * @param Attck type.
 * @param nullopt if attacker is player
 * @param nullopt if defender is player
 * @return Damage for effects
 */
int attack_function(ActorStats* attacker, ActorStats* defender,
                    bn::random& random_generator);

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
                   const Action::Action* action,
                   bn::ivector<bn::sprite_ptr>& _damage_text,
                   bn::sprite_ptr& _attack_effect_sprite,
                   bn::sprite_animate_action<9>& _attack_effect);

} // namespace Runa::Game

#endif // GAME_BATTLE_FUNCTION_H
