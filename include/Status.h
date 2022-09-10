#ifndef STATUS_H
#define STATUS_H

#include "Game_battle_actorstats.h"

#include "bn_sram.h"

namespace Runa
{

constexpr int NUM_ENEMY = 128;

class Status
{
public:
    Status();
    ~Status();

    void Game_init();
    void Write();
    void WriteGame();
    void WriteGlobal();
    bool Read();
    void Reset();

    short Get_level();
    int Get_hp();
    int Get_mp();
    int Get_exp();
    short Get_turns();
    short Get_weapon();
    short Get_armor();
    short Get_stratum();
    short Get_choco();
    short Get_multiplier();
    int Get_Max_level();
    int Get_Max_turn();
    int Get_Total_turn();
    int Get_Enemy_codex(int index);

    /**
     * @brief Increase enemy defeat counter.
     * @param Enemy index
     */
    void Defeat_enemy(int index);

    /**
     * @brief Change hp and check if hp is below 0
     * @param Amount of change of hp.
     * > 0: heal
     * < 0: damage
     * @return Returns true if hp is 0 or low (dead).
     */
    bool Hp_change(short increment);
    /**
     * @brief Change mp and check if mp is enough.
     * @param Amount of change.
     * @return Returns false if mp is not enough.
     */
    bool Mp_change(short increment);

    void Exp_earn(int increment);
    void Choco_earn(int increment);
    void Life_regain();
    void Weapon_upgrade();
    void Armor_upgrade();

    void Next_stratum();
    /**
     * @brief At the end of battle sequence, lower multiplier by 5%.
     */
    void Lower_multiplier();

    /**
     * @brief Check if value is changed and return flag _value_changed to false.
     * @return True if any of status is changed.
     */
    bool Value_changed();

    /**
     * @brief Called at end of turn. Decrease left_turns by 1.
     * @return Returns true if no turn left.
     */
    bool turn_end();

    void Game_over();

    Game::ActorStats _stats;
private:
    /**
     * @brief Player (Runa) status.
     */
    short Level;
    int hp;
    int mp;
    int exp;
    short left_turns;
    short Weapon_level;
    short Armor_level;
    short stratum;
    int chocolate;
    int choco_multiplier;
    int total_turn;

    int Max_level;
    int Max_turn;
    int Enemy_codex[NUM_ENEMY];

    /**
     * @brief For interface update.
     * Value will be changed to true when other stats changed.
     * After value checked, value will be returned to false.
     */
    bool _value_changed = false;

    void _stats_update();
};

} // namespace Runa

#endif // STATUS_H
