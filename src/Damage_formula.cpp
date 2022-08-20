#include "Damage_formula.h"

#include "bn_algorithm.h"

namespace Runa::Game
{

int Damage_calculator(int type, int str, int weapon, int def, int armor)
{
    int base = (type) ? str * 2 : str;
    int dmg = (base + weapon + 1) / (def + 1);
    dmg = dmg + (base * base / 3 + weapon + 1) / (def + armor + 1);
    dmg = dmg + weapon - armor;
    dmg = bn::max(1, dmg);
    return dmg;
}

} // namespace Runa::Game
