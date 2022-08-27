#include "Enemy_data.h"

#include "bn_sprite_items_cursor_0.h"
#include "bn_sprite_items_enemy_abc_a.h"
#include "bn_sprite_items_enemy_abc_b.h"
#include "bn_sprite_items_enemy_abc_c.h"
#include "bn_sprite_items_enemy_abc_s.h"
#include "bn_sprite_items_enemy_abc_t.h"
#include "bn_sprite_items_enemy_abc_boss.h"

namespace Runa::Game::Enemy
{

/**
 * Enemy base data.
 * Real Hp, Exp, Chocolate, Atk, Def value will be calculated in runtime.
 */
constexpr Enemy_data Enemy_base_data[] = {
    Enemy_data(bn::sprite_items::cursor_0, "Plc_hldr", 10, 10, 10, 10, 10, 10, Pattern_index::Bash),
    // 1st stratum : alphabet school
    Enemy_data(bn::sprite_items::enemy_abc_a, "Choco A", 10, 5, 7, 13, 3, 6, Pattern_index::Bash), // Attacker
    Enemy_data(bn::sprite_items::enemy_abc_b, "Choco B", 10, 5, 7, 5, 11, 6, Pattern_index::Guard), // Blocker
    Enemy_data(bn::sprite_items::enemy_abc_c, "Choco C", 10, 7, 10, 11, 7, 6, Pattern_index::Charge_Bash), // Charger
    Enemy_data(bn::sprite_items::enemy_abc_c, "Choco N", 10, 5, 7, 9, 7, 6, Pattern_index::Bash), // Normal ;;graphic
    Enemy_data(bn::sprite_items::enemy_abc_s, "Choco S", 10, 6, 9, 9, 7, 9, Pattern_index::Bash), // Speed
    Enemy_data(bn::sprite_items::enemy_abc_t, "Choco T", 20, 7, 10, 9, 7, 6, Pattern_index::Bash_Guard), // Tanker
    Enemy_data(bn::sprite_items::enemy_abc_t, "Choco W", 10, 6, 9, 12, 7, 6, Pattern_index::Heal), // White  ;;graphic
    Enemy_data(bn::sprite_items::enemy_abc_boss, "Choco BOSS", 100, 60, 500, 12, 12, 7, Pattern_index::Boss_1), // Actual 200, 90, 500, 18, 18, 9
    // 2nd stratum : cookie bakery
    // 3rd stratum : chess kingdom
};

const Enemy_data& Get_enemy_base_data(int index)
{
    return Enemy_base_data[index];
}

} // namespace Runa::Game::Enemy
