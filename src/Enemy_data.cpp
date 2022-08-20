#include "Enemy_data.h"

#include "bn_sprite_items_cursor_0.h"
#include "bn_sprite_items_enemy_abc_a.h"
#include "bn_sprite_items_enemy_abc_b.h"
#include "bn_sprite_items_enemy_abc_c.h"
#include "bn_sprite_items_enemy_abc_boss.h"

namespace Runa::Game::Enemy
{

/**
 * Enemy base data.
 * Real Hp, Exp, Chocolate, Atk, Def value will be calculated in runtime.
 */
constexpr Enemy_data Enemy_base_data[] = {
    Enemy_data(bn::sprite_items::cursor_0, "Plc_hldr", 10, 10, 10, 10, 10, 10),
    Enemy_data(bn::sprite_items::enemy_abc_a, "Choco A", 10, 10, 10, 15, 5, 7),
    Enemy_data(bn::sprite_items::enemy_abc_b, "Choco B", 10, 10, 10, 5, 15, 7),
    Enemy_data(bn::sprite_items::enemy_abc_c, "Choco C", 10, 10, 10, 10, 10, 7),
    Enemy_data(bn::sprite_items::enemy_abc_boss, "The Boss", 200, 60, 150, 25, 25, 15)
};

const Enemy_data& Get_enemy_base_data(int index)
{
    return Enemy_base_data[index];
}

} // namespace Runa::Game::Enemy
