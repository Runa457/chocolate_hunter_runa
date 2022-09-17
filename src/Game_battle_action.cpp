#include "Game_battle_action.h"

#include "bn_sound_items.h"

#include "bn_sprite_items_effect_sword.h"
#include "bn_sprite_items_effect_bash.h"
#include "bn_sprite_items_effect_guard.h"
#include "bn_sprite_items_effect_heal.h"
#include "bn_sprite_items_effect_regen.h"
#include "bn_sprite_items_effect_focus.h"
#include "bn_sprite_items_effect_blood_cast.h"
#include "bn_sprite_items_effect_charge.h"
#include "bn_sprite_items_effect_fire.h"
#include "bn_sprite_items_effect_ice.h"
#include "bn_sprite_items_effect_lightning.h"
#include "bn_sprite_items_effect_acid.h"
#include "bn_sprite_items_effect_quicksand.h"
#include "bn_sprite_items_effect_red_arrow_up.h"
#include "bn_sprite_items_effect_red_arrow_down.h"
#include "bn_sprite_items_effect_blue_arrow_up.h"
#include "bn_sprite_items_effect_blue_arrow_down.h"

namespace Runa::Game::Action
{

constexpr Action Action_data[] = {
    // None target
    Action("Poisoned", Target_type::None, Action_type::None, Element_type::None,
    0, 0, 0, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_heal, 4, bn::sound_items::sfx_battle_damage_taken),//

    Action("Regenerate", Target_type::None, Action_type::None, Element_type::None,
    0, 0, 0, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_heal, 2, bn::sound_items::sfx_battle_magic),// sound

    // Self target
    Action("Guard", Target_type::Self_target, Action_type::Normal_attack, Element_type::None,
    0, 0, 500, Status_effect_index::Guard, 100, 1,
    bn::sprite_items::effect_guard, 2, bn::sound_items::sfx_battle_sword),// sound

    Action("Charge", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    10, 0, 150, Status_effect_index::Charge, 100, 2,
    bn::sprite_items::effect_charge, 2, bn::sound_items::sfx_battle_magic),

    Action("Super Charge", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    10, 500, 150, Status_effect_index::Charge, 100, 3,
    bn::sprite_items::effect_charge, 2, bn::sound_items::sfx_battle_magic),

    Action("Heal I", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    15, -100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_heal, 2, bn::sound_items::sfx_battle_magic),// sound

    Action("Attack Up", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    7, 0, 100, Status_effect_index::Attack_up, 100, 5,
    bn::sprite_items::effect_red_arrow_up, 2, bn::sound_items::sfx_battle_magic),// sound

    Action("Defense Up", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    7, 0, 100, Status_effect_index::Defence_up, 100, 5,
    bn::sprite_items::effect_blue_arrow_up, 2, bn::sound_items::sfx_battle_magic),// sound

    Action("Barrier", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    10, 0, 100, Status_effect_index::Guard, 100, 5,
    bn::sprite_items::effect_guard, 2, bn::sound_items::sfx_battle_magic),//

    Action("Focus", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    -10, 0, 100, Status_effect_index::Defence_down, 100, 3,
    bn::sprite_items::effect_focus, 2, bn::sound_items::sfx_battle_magic),//

    Action("Blood Cast", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    -30, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_blood_cast, 2, bn::sound_items::sfx_battle_magic),//

    Action("Regenerate", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    15, 0, 100, Status_effect_index::Regenerate, 100, 5,
    bn::sprite_items::effect_regen, 2, bn::sound_items::sfx_battle_magic),//

    Action("Cure", Target_type::Self_target, Action_type::Magic_attack, Element_type::None,
    5, -30, 100, Status_effect_index::Poison, 100, -99,
    bn::sprite_items::effect_heal, 2, bn::sound_items::sfx_battle_magic),//

    // Single target
    Action("Slash", Target_type::Single_target, Action_type::Normal_attack, Element_type::Physical,
    0, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 2, bn::sound_items::sfx_battle_sword),

    Action("Bash", Target_type::Single_target, Action_type::Normal_attack, Element_type::Physical,
    0, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_bash, 2, bn::sound_items::sfx_battle_damage_taken),

    Action("Throw", Target_type::Single_target, Action_type::Normal_attack, Element_type::Physical,
    0, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_bash, 2, bn::sound_items::sfx_battle_damage_taken),

    Action("Quicksand", Target_type::Single_target, Action_type::Normal_attack, Element_type::Physical,
    0, 50, 100, Status_effect_index::Speed_down, 75, 3,
    bn::sprite_items::effect_quicksand, 2, bn::sound_items::sfx_battle_magic),

    Action("Fire I", Target_type::Single_target, Action_type::Magic_attack, Element_type::Fire,
    5, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_fire, 2, bn::sound_items::sfx_battle_magic),

    Action("Ice I", Target_type::Single_target, Action_type::Magic_attack, Element_type::Ice,
    5, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_ice, 2, bn::sound_items::sfx_battle_magic),//

    Action("Ice II", Target_type::Single_target, Action_type::Magic_attack, Element_type::Ice,
    10, 200, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_ice, 2, bn::sound_items::sfx_battle_magic),//

    Action("Ice III", Target_type::Single_target, Action_type::Magic_attack, Element_type::Ice,
    15, 300, 100, Status_effect_index::Defence_down, 80, 5,
    bn::sprite_items::effect_ice, 2, bn::sound_items::sfx_battle_magic),//

    Action("Lightning I", Target_type::Single_target, Action_type::Magic_attack, Element_type::Lightning,
    5, 100, 150, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_lightning, 2, bn::sound_items::sfx_battle_magic),

    Action("Weaken", Target_type::Single_target, Action_type::Magic_attack, Element_type::None,
    8, 0, 100, Status_effect_index::Attack_down, 100, 5,
    bn::sprite_items::effect_red_arrow_down, 2, bn::sound_items::sfx_battle_magic),//

    Action("Soften", Target_type::Single_target, Action_type::Magic_attack, Element_type::None,
    8, 0, 100, Status_effect_index::Defence_down, 100, 5,
    bn::sprite_items::effect_blue_arrow_down, 2, bn::sound_items::sfx_battle_magic),//

    // Multi hit
    Action("Triple Slash", Target_type::Multi_hit, Action_type::Normal_attack, Element_type::Physical,
    0, 80, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_sword, 2, bn::sound_items::sfx_battle_sword),

    Action("Confusion", Target_type::Multi_hit, Action_type::Normal_attack, Element_type::Physical,
    0, 80, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_bash, 2, bn::sound_items::sfx_battle_damage_taken),

    Action("Fire II", Target_type::Multi_hit, Action_type::Magic_attack, Element_type::Fire,
    15, 100, 100, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_fire, 2, bn::sound_items::sfx_battle_magic),

    Action("Fire III", Target_type::Multi_hit, Action_type::Magic_attack, Element_type::Fire,
    20, 150, 100, Status_effect_index::Attack_down, 50, 3,
    bn::sprite_items::effect_fire, 2, bn::sound_items::sfx_battle_magic),

    Action("Sandstorm", Target_type::Multi_hit, Action_type::Magic_attack, Element_type::Physical,
    15, 100, 100, Status_effect_index::Speed_down, 50, 3,
    bn::sprite_items::effect_quicksand, 2, bn::sound_items::sfx_battle_magic),

    // Every enemy target
    Action("Area Heal I", Target_type::Every_enemy_target, Action_type::Magic_attack, Element_type::None,
    30, -100, 80, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_heal, 2, bn::sound_items::sfx_battle_magic),// sound

    Action("Lightning II", Target_type::Every_enemy_target, Action_type::Magic_attack, Element_type::Lightning,
    12, 100, 200, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_lightning, 2, bn::sound_items::sfx_battle_magic),

    Action("Acid Rain", Target_type::Every_enemy_target, Action_type::Magic_attack, Element_type::None,
    15, 50, 100, Status_effect_index::Defence_down, 100, 5,
    bn::sprite_items::effect_acid, 2, bn::sound_items::sfx_battle_magic),//

    // Entire target    
    Action("Sword Dance", Target_type::Entire_target, Action_type::Normal_attack, Element_type::Physical,
    0, 100, 100, Status_effect_index::Bleeding, 60, 3,
    bn::sprite_items::effect_sword, 2, bn::sound_items::sfx_battle_sword),

    Action("Explosion", Target_type::Entire_target, Action_type::Normal_attack, Element_type::Fire,
    0, 500, 50, Status_effect_index::None, 0, 0,
    bn::sprite_items::effect_fire, 4, bn::sound_items::sfx_battle_damage_taken),//

};

constexpr Action Get_action_data_I(Action_index index) { return Action_data[(int)index]; }

constexpr Action Magic_data[] = {
    Get_action_data_I(Action_index::Fire_I),
    Get_action_data_I(Action_index::Ice_I),
    Get_action_data_I(Action_index::Lightning_I),
    Get_action_data_I(Action_index::Defense_Up),
    Get_action_data_I(Action_index::Attack_Up),

    Get_action_data_I(Action_index::Barrier),
    Get_action_data_I(Action_index::Charge),
    Get_action_data_I(Action_index::Fire_II),
    Get_action_data_I(Action_index::Ice_II),
    Get_action_data_I(Action_index::Heal_I),

    Get_action_data_I(Action_index::Sword_Dance),
    Get_action_data_I(Action_index::Weaken),
    Get_action_data_I(Action_index::Soften),
    Get_action_data_I(Action_index::Lightning_II),
    Get_action_data_I(Action_index::Sandstorm),

    Get_action_data_I(Action_index::Acid_Rain),
    Get_action_data_I(Action_index::Fire_III),
    Get_action_data_I(Action_index::Ice_III),
    Get_action_data_I(Action_index::Focus),
    Get_action_data_I(Action_index::Regenerate),

    Get_action_data_I(Action_index::Cure),
    Get_action_data_I(Action_index::Blood_Cast),

};

const Action& Get_action_data(Action_index index) { return Action_data[(int)index]; }
const Action& Get_magic_data(Magic_index index) { return Magic_data[(int)index]; }
const Action& Get_magic_data(int index) { return Magic_data[index]; }

const bn::string_view Print_target_type(Target_type target)
{
    switch (target)
    {
    case Target_type::None:
        return "None";
    case Target_type::Self_target:
        return "Self";
    case Target_type::Single_target:
        return "Single";
    case Target_type::Multi_hit:
        return "Multi";
    case Target_type::Every_enemy_target:
        return "Enemies";
    case Target_type::Entire_target:
        return "Entire";
    default:
        BN_ERROR("Not implemented target type");
        break;
    }
}
const bn::string_view Print_element_type(Element_type element)
{
    switch (element)
    {
    case Element_type::None:
        return "None";
    case Element_type::Physical:
        return "Physical";
    case Element_type::Fire:
        return "Fire";
    case Element_type::Ice:
        return "Ice";
    case Element_type::Lightning:
        return "Lightning";
    default:
        BN_ERROR("Not implemented element type");
        break;
    }
}

} // namespace Runa::Game
