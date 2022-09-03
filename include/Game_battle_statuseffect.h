#ifndef GAME_BATTLE_STATUSEFFECT_H
#define GAME_BATTLE_STATUSEFFECT_H

namespace Runa::Game
{

constexpr int MAX_STATUS_NUMBER = 3;

enum Status_effect_index : int
{
    None = 0,
    Attack_up = 1,    // 1.3x atk
    Attack_down = 2,  // 0.7x atk
    Defence_up = 4,   // 1.3x def
    Defence_down = 8, // 0.7x def
    Speed_up = 16,    // 1.3x spd
    Speed_down = 32,  // 0.7x spd
    Charge = 64,      // 2.0x damage given
    Guard = 128,      // 0.5x damage taken
    Bleeding = 256,   // 1.5x damage taken
    Poison = 512,
};

class Status_effect
{
public:
    Status_effect();
    ~Status_effect();

    Status_effect_index Get_status_effect();
    /**
     * @brief Add new status effect if possible
     * @param Status effect to be added
     * @param Status effect duration
     */
    void Set_status_effect(Status_effect_index next_status, int turns);
    /**
     * @brief Remove all status effects
     */
    void Remove_status_effect();
    /**
     * @brief Remove status effects as turn passes
     */
    void Turn_passed();

private:
    Status_effect_index _inner_index[MAX_STATUS_NUMBER];
    int _duration[MAX_STATUS_NUMBER];

};

} // namespace Runa::Game

#endif // GAME_BATTLE_STATUSEFFECT_H
