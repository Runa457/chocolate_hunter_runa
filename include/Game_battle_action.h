#ifndef GAME_BATTLE_ACTION_H
#define GAME_BATTLE_ACTION_H

#include "Game_battle_actorstats.h"

#include "bn_sound_item.h"
#include "bn_sprite_item.h"
#include "bn_string_view.h"

namespace Runa::Game::Action
{

enum class Target_type : char
{
    None,
    Self_target,
    Single_target,
    Multi_hit,
    Every_enemy_target,
    Entire_target
};

enum class Action_type : char
{
    None,
    Normal_attack,
    Magic_attack,
};

class Action
{
public:
    constexpr Action(bn::string_view name,
                     Target_type target, Action_type action,
                     int cost, int multiplier,
                     int status_chance, Status_effect status_effect,
                     const bn::sprite_item& action_effect, int frames,
                     const bn::sound_item& action_sound) :
        _name(name),
        _target(target),
        _action(action),
        _cost(cost),
        _multiplier(multiplier),
        _status_chance(status_chance),
        _status_effect(status_effect),
        _action_effect(action_effect),
        _frames(frames),
        _action_sound(action_sound)
    {}

    bn::string_view _name;
    Target_type _target;
    Action_type _action;

    /**
     * @brief Mana cost for magic attack
     */
    int _cost;
    /**
     * @brief Damage multiplier %
     */
    int _multiplier;
    /**
     * @brief Chance to induce status effect.
     */
    int _status_chance;
    /**
     * @brief _status_effect
     */
    Status_effect _status_effect;

    // for effect
    const bn::sprite_item& _action_effect;
    int _frames;
    const bn::sound_item& _action_sound;
};

const Action& Get_action_data(int index);
const Action& Get_magic_data(int index);

} // namespace Runa::Game

#endif // GAME_BATTLE_ACTION_H
