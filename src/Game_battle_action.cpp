#include "Game_battle_action.h"

#include "bn_sound_items.h"

#include "bn_sprite_items_effect_sword.h"

namespace Runa::Game::Action
{

constexpr Action Action_data[] = {
    Action("Slash", Target_type::Single_target, Action_type::Normal_attack,
    0, 100, 0, Status_effect::None,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),

    Action("Bash", Target_type::Single_target, Action_type::Normal_attack,
    0, 100, 0, Status_effect::None,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_damage_taken),//
};

constexpr Action Magic_data[] = {
    Action("Fire", Target_type::Single_target, Action_type::Magic_attack,
    5, 100, 0, Status_effect::None,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//
};

const Action& Get_action_data(int index)
{
    return Action_data[index];
}
const Action& Get_magic_data(int index)
{
    return Magic_data[index];
}

} // namespace Runa::Game
