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

namespace Runa::Game::Enemy
{

/**
 * Enemy base data.
 * Input format : Enemy graphic, name, exp, chocolate, hp, str, def, spd, pattern
 * Real Hp, Exp, Chocolate, Atk, Def value will be calculated in runtime.
 */
constexpr Enemy_data Enemy_base_data[] = {
    Enemy_data(bn::sprite_items::cursor_0, "Plc_hldr", 10, 10, 10, 10, 10, 10, Pattern_index::Bash),
    // 1st stratum : alphabet school
    Enemy_data(bn::sprite_items::enemy_abc_a, "Choco A", 6, 9,      10, 13, 3, 6, Pattern_index::Slash), // Attacker
    Enemy_data(bn::sprite_items::enemy_abc_b, "Choco B", 5, 7,      10, 5, 11, 6, Pattern_index::Guard), // Blocker
    Enemy_data(bn::sprite_items::enemy_abc_c, "Choco C", 6, 9,      10, 13, 7, 6, Pattern_index::Charge_Bash), // Charger
    Enemy_data(bn::sprite_items::enemy_abc_h, "Choco H", 6, 9,      10, 12, 7, 6, Pattern_index::AreaHeal), // Healer
    Enemy_data(bn::sprite_items::enemy_abc_n, "Choco N", 5, 7,      10, 9, 7, 6, Pattern_index::Bash), // Normal
    Enemy_data(bn::sprite_items::enemy_abc_s, "Choco S", 7, 10,     10, 9, 7, 9, Pattern_index::TripleSlash), // Speed
    Enemy_data(bn::sprite_items::enemy_abc_t, "Choco T", 7, 10,     20, 9, 7, 6, Pattern_index::Guard_Slash), // Tanker
    Enemy_data(bn::sprite_items::enemy_abc_w, "Choco W", 6, 9,      10, 14, 7, 6, Pattern_index::Charge_AreaHeal), // White
    Enemy_data(bn::sprite_items::enemy_abc_boss, "Choco BOSS", 60, 500,     100, 12, 12, 7, Pattern_index::Boss_1), // Actual 200, 90, 500, 18, 18, 9
    // 2nd stratum : cookie bakery
    // 3rd stratum : chess kingdom
};

const Enemy_data& Get_enemy_base_data(int index)
{
    return Enemy_base_data[index];
}

} // namespace Runa::Game::Enemy
