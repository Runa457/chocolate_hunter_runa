#include "Stats_data.h"

namespace Runa
{

/**
 * Base Hp = 30
 * Multiplier = 1.04
 */
extern constexpr short HP_table[] = {
    30, 31, 32, 33, 35, 36, 37, 39, 41, 42,
    44, 46, 48, 49, 51, 54, 56, 58, 60, 63,
    65, 68, 71, 73, 76, 79, 83, 86, 89, 93,
    97, 101, 105, 109, 113, 118, 123, 128, 133, 138,
    144, 149, 155, 162, 168, 175, 182, 189, 197, 205,
    213
};

/**
 * Base Mp = 50
 * Multiplier = 1.04
 */
extern constexpr short MP_table[] = {
    50, 52, 54, 56, 58, 60, 63, 65, 68, 71,
    74, 76, 80, 83, 86, 90, 93, 97, 101, 105,
    109, 113, 118, 123, 128, 133, 138, 144, 149, 155,
    162, 168, 175, 182, 189, 197, 205, 213, 221, 230,
    240, 249, 259, 270, 280, 292, 303, 315, 328, 341,
    355
};

/**
 * Base Exp = 100
 * Multiplier = 1.10
 */
extern constexpr short EXP_table[] = {
    100, 110, 121, 133, 146, 161, 177, 194, 214, 235,
    259, 285, 313, 345, 379, 417, 459, 505, 555, 611,
    672, 740, 814, 895, 984, 1083, 1191, 1310, 1442, 1586,
    1744, 1919, 2111, 2322, 2554, 2810, 3091, 3400, 3740, 4114,
    4525, 4978, 5476, 6024, 6626, 7289, 8017, 8819, 9701, 10671,
    32767 //11739
};

/**
 * Base STR = 9
 * Multiplier = 1.05
 */
extern constexpr short STR_table[] = {
    9, 9, 9, 10, 10, 11, 12, 12, 13, 13,
    14, 15, 16, 16, 17, 18, 19, 20, 21, 22,
    23, 25, 26, 27, 29, 30, 32, 33, 35, 37,
    38, 40, 42, 45, 47, 49, 52, 54, 57, 60,
    63, 66, 69, 73, 77, 80, 84, 89, 93, 98,
    103 //50level
};

/**
 * Base DEF = 7
 * Multiplier = 1.05
 */
extern constexpr short DEF_table[] = {
    7, 7, 7, 8, 8, 8, 9, 9, 10, 10,
    11, 11, 12, 13, 13, 14, 15, 16, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 26, 27, 28,
    30, 31, 33, 35, 36, 38, 40, 42, 44, 46,
    49, 51, 54, 57, 59, 62, 66, 69, 72, 76,
    80
};

/**
 * Base INT = 12
 * Multiplier = 1.06
 */
extern constexpr short INT_table[] = {
    12, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 24, 25, 27, 28, 30, 32, 34, 36,
    38, 40, 43, 45, 48, 51, 54, 57, 61, 65,
    68, 73, 77, 82, 87, 92, 97, 103, 109, 116,
    123, 130, 138, 147, 155, 165, 175, 185, 196, 208,
    221
};

/**
 * Base SPD = 8
 * Multiplier = 1.04
 */
extern constexpr short SPD_table[] = {
    8, 8, 8, 8, 9, 9, 10, 10, 10, 11,
    11, 12, 12, 13, 13, 14, 14, 15, 16, 16,
    17, 18, 18, 19, 20, 21, 22, 23, 23, 24,
    25, 26, 28, 29, 30, 31, 32, 34, 35, 36,
    38, 39, 41, 43, 44, 46, 48, 50, 52, 54,
    56
};

/**
 * Base Weapon = 3
 */
extern constexpr short Weapon_table[] = {
    3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 15, 17, 19, 21, 23, 25, 27, 29, 31,
    33, 36, 39, 42, 45, 48, 51, 54, 57, 60,
    63, 67, 71, 75, 79, 83, 87, 91, 95, 99,
    103, 108, 113, 118, 123, 128, 133, 138, 143, 148,
    153
};

/**
 * Base Armor = 3
 */
extern constexpr short Armor_table[] = {
    3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 15, 17, 19, 21, 23, 25, 27, 29, 31,
    33, 36, 39, 42, 45, 48, 51, 54, 57, 60,
    63, 67, 71, 75, 79, 83, 87, 91, 95, 99,
    103, 108, 113, 118, 123, 128, 133, 138, 143, 148,
    153
};

extern constexpr short Enemy_index_table[] = {
    0, 8, 9
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
const short& Get_enemy_index(int level) { return Enemy_index_table[level]; }

} // namespace Runa
