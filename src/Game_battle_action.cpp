#include "Game_battle_action.h"

#include "bn_sound_items.h"

#include "bn_sprite_items_effect_sword.h"
#include "bn_sprite_items_effect_guard.h"
#include "bn_sprite_items_effect_heal.h"
#include "bn_sprite_items_effect_red_arrow_up.h"
#include "bn_sprite_items_effect_blue_arrow_up.h"

namespace Runa::Game::Action
{

constexpr Action Action_data[] = {
    // Self target
    Action("Guard", Target_type::Self_target, Action_type::Normal_attack, Element_type::None,
    0, 0, 500, Status_effect_index::Guard, 100, 1,
    bn::sprite_items::effect_guard, 9, bn::sound_items::sfx_battle_sword),//

    Action("Charge", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    10, 0, 150, Status_effect_index::Charge, 100, 2,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),//

    Action("Heal I", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    15, -100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_heal, 9, bn::sound_items::sfx_battle_magic),//

    Action("Attack Up", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    7, 0, 100, Status_effect_index::Attack_up, 100, 5,
    bn::sprite_items::effect_red_arrow_up, 9, bn::sound_items::sfx_battle_magic),//

    Action("Defence Up", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    7, 0, 100, Status_effect_index::Defence_up, 100, 5,
    bn::sprite_items::effect_blue_arrow_up, 9, bn::sound_items::sfx_battle_magic),//

    // Single target
    Action("Slash", Target_type::Single_target, Action_type::Normal_attack, Element_type::Physical,
    0, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),

    Action("Bash", Target_type::Single_target, Action_type::Normal_attack, Element_type::Physical,
    0, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_damage_taken),//

    // Multi hit
    Action("Triple Slash", Target_type::Multi_hit, Action_type::Normal_attack, Element_type::Physical,
    0, 80, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),

    // Every enemy target
    Action("Area Heal I", Target_type::Every_enemy_target, Action_type::Magic_attack, Element_type::None,
    30, -100, 80, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_heal, 9, bn::sound_items::sfx_battle_magic),//

    // Entire target
};

constexpr Action Magic_data[] = {
    Action("Fire I", Target_type::Single_target, Action_type::Magic_attack, Element_type::Fire,
    5, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Ice I", Target_type::Single_target, Action_type::Magic_attack, Element_type::Ice,
    5, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Lightning I", Target_type::Single_target, Action_type::Magic_attack, Element_type::Lightning,
    5, 100, 150, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Defense Up", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    7, 0, 100, Status_effect_index::Defence_up, 100, 5,
    bn::sprite_items::effect_blue_arrow_up, 9, bn::sound_items::sfx_battle_magic),//

    Action("Attack Up", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    7, 0, 100, Status_effect_index::Attack_up, 100, 5,
    bn::sprite_items::effect_red_arrow_up, 9, bn::sound_items::sfx_battle_magic),//


    Action("Barrier", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    10, 0, 100, Status_effect_index::Guard, 100, 5,
    bn::sprite_items::effect_guard, 9, bn::sound_items::sfx_battle_magic),//

    Action("Charge", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    10, 0, 150, Status_effect_index::Charge, 100, 2,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),//

    Action("Fire II", Target_type::Multi_hit, Action_type::Magic_attack, Element_type::Fire,
    15, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Sword Dance", Target_type::Entire_target, Action_type::Normal_attack, Element_type::Physical,
    0, 150, 100, Status_effect_index::Bleeding, 60, 3,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_sword),

    Action("Fire III", Target_type::Every_enemy_target, Action_type::Magic_attack, Element_type::Fire,
    20, 150, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Fire IV", Target_type::Entire_target, Action_type::Magic_attack, Element_type::Fire,
    15, 200, 100, Status_effect_index::Attack_down, 10, 3,
    bn::sprite_items::effect_sword, 9, bn::sound_items::sfx_battle_magic),//

    Action("Heal I", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    15, -100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_heal, 9, bn::sound_items::sfx_battle_magic),//

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
