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

#include "bn_sprite_items_enemy_chess_pawnb.h"
#include "bn_sprite_items_enemy_chess_pawnw.h"
#include "bn_sprite_items_enemy_chess_knightb.h"
#include "bn_sprite_items_enemy_chess_knightw.h"
#include "bn_sprite_items_enemy_chess_bishopb.h"
#include "bn_sprite_items_enemy_chess_bishopw.h"
#include "bn_sprite_items_enemy_chess_rookb.h"
#include "bn_sprite_items_enemy_chess_rookw.h"
#include "bn_sprite_items_enemy_chess_queenb.h"
#include "bn_sprite_items_enemy_chess_queenw.h"
#include "bn_sprite_items_enemy_chess_kingb.h"
#include "bn_sprite_items_enemy_chess_kingw.h"
#include "bn_sprite_items_enemy_chess_unicorn.h"

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
    Enemy_data(bn::sprite_items::enemy_abc_a, "Choco Attacker", 8, 9,   10, 13, 3, 6, Pattern_index::Slash,           100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_b, "Choco Blocker",  6, 6,   10, 5, 11, 6, Pattern_index::Guard,           100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_c, "Choco Charger",  9, 10,  10, 13, 7, 6, Pattern_index::Charge_Bash,     100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_h, "Choco Healer",   7, 7,   10, 8, 7, 6, Pattern_index::AreaHeal,         100, 160, 40, 100),
    Enemy_data(bn::sprite_items::enemy_abc_n, "Choco Normal",   7, 7,   10, 9, 7, 6, Pattern_index::Bash,             100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_s, "Choco Speedy",   9, 10,  10, 9, 7, 9, Pattern_index::TripleSlash,      100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_t, "Choco Tanker",   8, 9,   20, 9, 7, 6, Pattern_index::Guard_Slash,      100, 120, 150, 100),
    Enemy_data(bn::sprite_items::enemy_abc_w, "Choco White",    7, 7,   10, 9, 7, 6, Pattern_index::Charge_AreaHeal,  100, 160, 40, 100),
    Enemy_data(bn::sprite_items::enemy_abc_boss, "Choco BOSS", 120, 500, 150, 12, 12, 8, Pattern_index::Boss_1,       100, 120, 150, 100), // Actual 180 / 300, 18, 18, 10
    // 2nd stratum : bakery street
    Enemy_data(bn::sprite_items::enemy_bakery_chipcookie,   "Chip cookie",    15, 16,   20, 11, 10, 8, Pattern_index::Throw,            200, 50, 120, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_checker,      "Checker cookie", 16, 17,   20, 9, 10, 8, Pattern_index::Charge_Confusion,  200, 50, 120, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_cracker,      "Cracker",        30, 0,    17, 14, 11, 8, Pattern_index::Charge_Lightning, 200, 80, 120, 50),
    Enemy_data(bn::sprite_items::enemy_bakery_chococracker, "Choco cracker",  8, 25,    17, 14, 11, 8, Pattern_index::Charge_Fire,      120, 50, 200, 80),
    Enemy_data(bn::sprite_items::enemy_bakery_chococake,    "Choco Cake",     17, 18,   23, 11, 10, 8, Pattern_index::Quicksand,        80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_redvelvet,    "Red Velvet",     16, 17,   23, 13, 13, 8, Pattern_index::FireIce,          80, 100, 100, 200),
    Enemy_data(bn::sprite_items::enemy_bakery_chocomuffin,  "Choco Muffin",   17, 18,   25, 13, 10, 8, Pattern_index::Explosion,        80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_donut,        "Donut",          18, 20,   20, 11, 12, 8, Pattern_index::Healer,           80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_rollcake,     "Roll Cake",      18, 20,   20, 9, 11, 10, Pattern_index::Confusion,        80, 150, 150, 100),
    Enemy_data(bn::sprite_items::enemy_bakery_cookiehouse,  "Cookie House", 250, 800,   240, 20, 17, 10, Pattern_index::Boss_2,         150, 50, 120, 100), // Actual 500 / 720, 40, 34, 16
    // 3rd stratum : chess castle
    Enemy_data(bn::sprite_items::enemy_chess_pawnb,   "Black Pawn",   24, 36,   30, 14, 12, 10, Pattern_index::Pawn_Black,   100, 10, 150, 100),
    Enemy_data(bn::sprite_items::enemy_chess_pawnw,   "White Pawn",   24, 36,   30, 14, 12, 11, Pattern_index::Pawn_White,   100, 150, 10, 100),
    Enemy_data(bn::sprite_items::enemy_chess_knightb, "Black Knight", 21, 30,   30, 14, 12, 11, Pattern_index::Knight_Black, 100, 10, 150, 80),
    Enemy_data(bn::sprite_items::enemy_chess_knightw, "White Knight", 21, 30,   30, 14, 12, 12, Pattern_index::Knight_White, 100, 150, 10, 80),
    Enemy_data(bn::sprite_items::enemy_chess_bishopb, "Black Bishop", 24, 36,   33, 17, 12, 10, Pattern_index::Bishop_Black, 100, 10, 150, 100),
    Enemy_data(bn::sprite_items::enemy_chess_bishopw, "White Bishop", 22, 32,   33, 17, 12, 11, Pattern_index::Bishop_White, 100, 150, 10, 100),
    Enemy_data(bn::sprite_items::enemy_chess_rookb,   "Black Rook",   23, 34,   30, 14, 15, 10, Pattern_index::Rook_Black,   10, 10, 150, 10),
    Enemy_data(bn::sprite_items::enemy_chess_rookw,   "White Rook",   22, 32,   30, 14, 15, 11, Pattern_index::Rook_White,   10, 150, 10, 10),
    Enemy_data(bn::sprite_items::enemy_chess_queenb,  "Black Queen",  23, 34,   32, 15, 12, 10, Pattern_index::Queen_Black,  100, 10, 120, 50),
    Enemy_data(bn::sprite_items::enemy_chess_queenw,  "White Queen",  23, 34,   32, 15, 12, 11, Pattern_index::Queen_White,  100, 120, 10, 50),
    Enemy_data(bn::sprite_items::enemy_chess_kingb,   "Black King",   22, 32,   31, 14, 12, 10, Pattern_index::King_Black,   100, 10, 150, 100),
    Enemy_data(bn::sprite_items::enemy_chess_kingw,   "White King",   22, 32,   31, 14, 12, 11, Pattern_index::King_White,   100, 150, 10, 100),
    Enemy_data(bn::sprite_items::enemy_chess_unicorn, "Unicorn",    500, 900,   340, 20, 20, 12, Pattern_index::Boss_3,       100, 100, 100, 100), // Actual 1250 / 1360, 50, 50, 22
    // 4th stratum
};

const Enemy_data& Get_enemy_base_data(int index)
{
    return Enemy_base_data[index];
}

} // namespace Runa::Game::Enemy
