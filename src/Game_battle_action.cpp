#include "Game_battle_action.h"

#include "bn_sprite_items_effect_sword.h"

namespace Runa::Game::Action
{

constexpr Action Action_data[] = {
    Action(bn::sprite_items::effect_sword, Target_type::Single_target, Action_type::Normal_attack, 100, 0),
};

} // namespace Runa::Game
