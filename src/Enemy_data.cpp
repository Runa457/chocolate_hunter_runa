#include "Enemy_data.h"

#include "bn_sprite_items_cursor_0.h"

#include "bn_sprite_items_enemy_abc_a.h"
#include "bn_sprite_items_enemy_abc_b.h"
#include "bn_sprite_items_enemy_abc_c.h"
#include "bn_sprite_items_enemy_abc_h.h"
#include "bn_sprite_items_enemy_abc_n.h"
#include "bn_sprite_items_enemy_abc_s.h"
#include "bn_sprite_items_enemy_abc_t.h"
#include "bn_sprite_items_enemy_abc_w.h"
#include "bn_sprite_items_enemy_abc_boss.h"

#include "bn_sprite_items_enemy_bakery_chipcookie.h"
#include "bn_sprite_items_enemy_bakery_checker.h"
#include "bn_sprite_items_enemy_bakery_cracker.h"
#include "bn_sprite_items_enemy_bakery_chococracker.h"
#include "bn_sprite_items_enemy_bakery_chococake.h"
#include "bn_sprite_items_enemy_bakery_redvelvet.h"
#include "bn_sprite_items_enemy_bakery_chocomuffin.h"
#include "bn_sprite_items_enemy_bakery_donut.h"
#include "bn_sprite_items_enemy_bakery_rollcake.h"
#include "bn_sprite_items_enemy_bakery_cookiehouse.h"

namespace Runa::Game::Enemy
{

/**
 * Enemy base data.
 * Input format : Enemy graphic, name, exp, chocolate, hp, str, def, spd, pattern, phy.weak, fire.weak, ice.weak, light.weak
 * Real Hp, Exp, Chocolate, Atk, Def value will be calculated in runtime.
 */
constexpr Enemy_data Enemy_base_data[] = {
    Enemy_data(bn::sprite_items::cursor_0, "Plc_hldr", 10, 10, 10, 10, 10, 10, Pattern_index::Bash, 100, 100, 100, 100),
    // 1st stratum : alphabetic grassland
    Enemy_data(bn::sprite_items::enemy_abc_a, "Choco Attacker", 6, 9,   10, 13, 3, 6, Pattern_index::Slash,           100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_b, "Choco Blocker",  4, 6,   10, 5, 11, 6, Pattern_index::Guard,           100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_c, "Choco Charger",  7, 10,  10, 13, 7, 6, Pattern_index::Charge_Bash,     100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_h, "Choco Healer",   5, 7,   10, 8, 7, 6, Pattern_index::AreaHeal,         100, 160, 40, 100),
    Enemy_data(bn::sprite_items::enemy_abc_n, "Choco Normal",   5, 7,   10, 9, 7, 6, Pattern_index::Bash,             100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_s, "Choco Speedy",   7, 10,  10, 9, 7, 9, Pattern_index::TripleSlash,      100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_t, "Choco Tanker",   6, 9,   20, 9, 7, 6, Pattern_index::Guard_Slash,      100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_w, "Choco White",    5, 7,   10, 9, 7, 6, Pattern_index::Charge_AreaHeal, 100, 160, 40, 100),
    Enemy_data(bn::sprite_items::enemy_abc_boss, "Choco BOSS", 120, 500, 150, 12, 12, 8, Pattern_index::Boss_1,       100, 120, 150, 100), // Actual 180 / 300, 18, 18, 10
    // 2nd stratum : bakery street
    Enemy_data(bn::sprite_items::enemy_bakery_chipcookie,   "Chip cookie",    15, 16,   20, 11, 10, 8, Pattern_index::Throw,            200, 50, 120, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_checker,      "Checker cookie", 17, 18,   20, 9, 10, 8, Pattern_index::Charge_Confusion,  200, 50, 120, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_cracker,      "Cracker",        30, 0,    17, 14, 11, 8, Pattern_index::Charge_Lightning, 200, 80, 120, 50),
    Enemy_data(bn::sprite_items::enemy_bakery_chococracker, "Choco cracker",  8, 25,    17, 14, 11, 8, Pattern_index::Charge_Fire,      120, 50, 200, 80),
    Enemy_data(bn::sprite_items::enemy_bakery_chococake,    "Choco Cake",     17, 18,   23, 11, 10, 8, Pattern_index::Quicksand,        80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_redvelvet,    "Red Velvet",     17, 18,   23, 13, 13, 8, Pattern_index::FireIce,          80, 100, 100, 200),
    Enemy_data(bn::sprite_items::enemy_bakery_chocomuffin,  "Choco Muffin",   17, 18,   25, 13, 10, 8, Pattern_index::Explosion,        80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_donut,        "Donut",          18, 20,   20, 11, 12, 8, Pattern_index::Healer,           80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_rollcake,     "Roll Cake",      18, 20,   20, 9, 11, 10, Pattern_index::Confusion,        80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_cookiehouse,  "Cookie House", 150, 800,   200, 20, 15, 10, Pattern_index::Boss_2,         150, 50, 120, 100), // Actual 300 / 600, 40, 30, 16
    // 3rd stratum : chess castle
};

const Enemy_data& Get_enemy_base_data(int index)
{
    return Enemy_base_data[index];
}

} // namespace Runa::Game::Enemy
