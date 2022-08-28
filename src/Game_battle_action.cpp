#include "Game_battle_action.h"

#include "bn_sound_items.h"

#include "bn_sprite_items_effect_sword.h"

namespace Runa::Game::Action
{

constexpr Action Action_data[] = {
    // Self target
    Action("Guard", Target_type::Self_target, Action_type::Normal_attack,
    0, 0, 500, Status_effect_index::Guard, 100, 1,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),//

    Action("Charge", Target_type::Self_target, Action_type::Normal_attack,
    0, 0, 150, Status_effect_index::Charge, 100, 2,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),//

    Action("Heal I", Target_type::Self_target, Action_type::Magic_attack,
    15, -100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    // Single target
    Action("Slash", Target_type::Single_target, Action_type::Normal_attack,
    0, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),

    Action("Bash", Target_type::Single_target, Action_type::Normal_attack,
    0, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_damage_taken),//

    // Multi hit
    Action("Triple Slash", Target_type::Multi_hit, Action_type::Normal_attack,
    0, 80, 150, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),

    // Every enemy target
    Action("Area Heal I", Target_type::Every_enemy_target, Action_type::Magic_attack,
    30, -100, 80, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    // Entire target
};

constexpr Action Magic_data[] = {
    Action("Fire I", Target_type::Single_target, Action_type::Magic_attack,
    5, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Fire II", Target_type::Multi_hit, Action_type::Magic_attack,
    15, 150, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Fire III", Target_type::Every_enemy_target, Action_type::Magic_attack,
    20, 200, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Fire IV", Target_type::Entire_target, Action_type::Magic_attack,
    15, 200, 100, Status_effect_index::Attack_down, 10, 3,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Heal I", Target_type::Self_target, Action_type::Magic_attack,
    15, -100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//
};

const Action& Get_action_data(Action_index index)
{
    return Action_data[(int)index];
}
const Action& Get_magic_data(Magic_index index)
{
    return Magic_data[(int)index];
}

} // namespace Runa::Game
