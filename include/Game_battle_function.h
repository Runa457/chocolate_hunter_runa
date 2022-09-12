#ifndef GAME_BATTLE_FUNCTION_H
#define GAME_BATTLE_FUNCTION_H

#include "Game_battle_actorstats.h"

#include "bn_random.h"

namespace Runa::Game
{

/**
 * @brief Handles attack damage calculation, pre/post processing.
 * @param Attacker actor data.
 * @param Defender actor data.
 * @param Random function for status chance.
 * @return Damage from action.
 */
int attack_function(ActorStats* attacker, ActorStats* defender,
                    bn::random& random);

/**
 * @brief Handles status effects damage or healing at end of turn.
 * @param Actor data.
 * @return Damage from status effects.
 */
int end_of_turn(ActorStats* actor);

} // namespace Runa::Game

#endif // GAME_BATTLE_FUNCTION_H
