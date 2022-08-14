#ifndef STATS_DATA_H
#define STATS_DATA_H

#include "bn_fixed.h"

namespace Runa
{

const short& Get_hp_data(int level);
const short& Get_mp_data(int level);
const short& Get_exp_data(int level);
const short& Get_atk_data(int level);
const short& Get_def_data(int level);
const short& Get_spd_data(int level);
const short& Get_weapon_data(int level);
const short& Get_armor_data(int level);

} // namespace Runa

#endif // STATS_DATA_H
