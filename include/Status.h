#ifndef STATUS_H
#define STATUS_H

#include "bn_sram.h"

namespace Runa
{

class Status
{
public:
    Status();
    ~Status();

    void Init();
    void Write();

    short Get_level();
    int Get_hp();
    int Get_mp();
    int Get_exp();
    short Get_turns();
    short Get_weapon();
    short Get_armor();

    /**
     * @brief Change hp and check if hp is below 0
     * @param Amount of change of hp.
     * > 0: heal
     * < 0: damage
     * @return Returns true if hp is 0 or low (dead).
     */
    bool Hp_change(short increment);

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
    int num_chocolate;

    /**
     * @brief For interface update.
     * Value will be changed to true when other stats changed.
     * After value checked, value will be returned to false.
     */
    bool _value_changed = false;
};

} // namespace Runa

#endif // STATUS_H
