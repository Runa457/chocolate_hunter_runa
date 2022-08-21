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
    Enemy_data(bn::sprite_items::cursor_0, "Plc_hldr", 10, 10, 10, 10, 10, 10),
    // 1st stratum : alphabet land
    Enemy_data(bn::sprite_items::enemy_abc_a, "Choco A", 10, 5, 7, 13, 3, 6),
    Enemy_data(bn::sprite_items::enemy_abc_b, "Choco B", 10, 5, 7, 5, 11, 6),
    Enemy_data(bn::sprite_items::enemy_abc_c, "Choco C", 10, 5, 7, 9, 7, 6),
    Enemy_data(bn::sprite_items::enemy_abc_s, "Choco S", 10, 6, 9, 9, 7, 9),
    Enemy_data(bn::sprite_items::enemy_abc_t, "Choco T", 20, 7, 10, 9, 7, 6),
    Enemy_data(bn::sprite_items::enemy_abc_boss, "Choco BOSS", 100, 60, 500, 12, 12, 7),
    // 2nd stratum : cookie land
    // 3rd stratum : chess land
};

const Enemy_data& Get_enemy_base_data(int index)
{
    return Enemy_base_data[index];
}

} // namespace Runa::Game::Enemy
