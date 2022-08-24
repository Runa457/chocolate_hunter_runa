#ifndef GAME_BATTLE_ACTORSTATS_H
#define GAME_BATTLE_ACTORSTATS_H

namespace Runa::Game
{

enum Status_effect : int
{
    None = 0,
    Attack_up = 1,
    Attack_down = 2,
    Defence_up = 4,
    Defence_down = 8,
    Speed_up = 16,
    Speed_down = 32,
    Charge = 64,
    Guard = 128,
    Poison = 256,
};

class ActorStats
{
public:
    ActorStats();
    ActorStats(int atk, int weapon, int def, int armor,
               int intelligence, Status_effect status_effect);
    ~ActorStats();

    int Get_atk();
    int Get_weapon();
    int Get_def();
    int Get_armor();
    int Get_int();
    Status_effect Get_status_effect();

    void Set_status_effect(Status_effect next_status);

private:
    int _atk;
    int _weapon;
    int _def;
    int _armor;
    int _intelligence;
    Status_effect _status_effect;
};

} // namespace Runa::Game

#endif // GAME_BATTLE_ACTORSTATS_H
