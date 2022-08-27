#ifndef GAME_BATTLE_FUNCTION_H
#define GAME_BATTLE_FUNCTION_H

#include "Game_battle_actorstats.h"

#include "bn_random.h"

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
                    bn::random& random);

} // namespace Runa::Game

#endif // GAME_BATTLE_FUNCTION_H
