#include "Stats_data.h"

namespace Runa
{

/**
 * Base Hp = 30
 */
extern constexpr short HP_table[] = {
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79
};

/**
 * Base Mp = 50
 */
extern constexpr short MP_table[] = {
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

/**
 * Base Exp = 100
 */
extern constexpr short EXP_table[] = {
    100, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

/**
 * Base STR = 9
 */
extern constexpr short STR_table[] = {
    9, 10, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

/**
 * Base DEF = 7
 */
extern constexpr short DEF_table[] = {
    7, 10, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

/**
 * Base INT = 12
 */
extern constexpr short INT_table[] = {
    12, 17, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

/**
 * Base SPD = 8
 */
extern constexpr short SPD_table[] = {
    8, 15, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

/**
 * Base Weapon = 3
 */
extern constexpr short Weapon_table[] = {
    3, 4, 5, 3, 4, 5, 6, 7, 8, 9,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

/**
 * Base Armor = 3
 */
extern constexpr short Armor_table[] = {
    3, 4, 5, 7, 4, 5, 6, 7, 8, 9,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
};

const short& Get_hp_data(int level) { return HP_table[level]; }
const short& Get_mp_data(int level) { return MP_table[level]; }
const short& Get_exp_data(int level) { return EXP_table[level]; }
const short& Get_str_data(int level) { return STR_table[level]; }
const short& Get_def_data(int level) { return DEF_table[level]; }
const short& Get_int_data(int level) { return INT_table[level]; }
const short& Get_spd_data(int level) { return SPD_table[level]; }
const short& Get_weapon_data(int level) { return Weapon_table[level]; }
const short& Get_armor_data(int level) { return Armor_table[level]; }

} // namespace Runa
