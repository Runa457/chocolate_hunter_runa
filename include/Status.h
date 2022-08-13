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

    int Get_level();
private:
    /**
     * @brief Player (Runa) status.
     */
    int Level;
    int hp, maxhp;
    int mp, maxmp;
    int exp;
    int left_turns;
    int strength, constitution;
    int ATK, DEF;
    int stratum;
    int num_chocolate;
};

} // namespace Runa

#endif // STATUS_H
