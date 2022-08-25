#ifndef GAME_BATTLE_STATUSEFFECT_H
#define GAME_BATTLE_STATUSEFFECT_H

namespace Runa::Game
{

enum Status_effect : int
{
    None = 0,
    Attack_up = 1,    // 1.3x atk
    Attack_down = 2,  // 0.7x atk
    Defence_up = 4,   // 1.3x def
    Defence_down = 8, // 0.7x def
    Speed_up = 16,    // 1.3x spd
    Speed_down = 32,  // 0.7x spd
    Charge = 64,      // 1.5x damage
    Guard = 128,      // 0.5x damage
    Poison = 256,
};

} // namespace Runa::Game

#endif // GAME_BATTLE_STATUSEFFECT_H
