#ifndef GAME_BATTLE_ACTION_H
#define GAME_BATTLE_ACTION_H

#include "Game_battle_statuseffect.h"

#include "bn_sound_item.h"
#include "bn_sprite_item.h"
#include "bn_string_view.h"

namespace Runa::Game::Action
{

enum Action_index : short
{
    // Self target
    Guard,
    // Single target
    Slash,
    Bash,
    // Multi hit
    // Every enemy target
    // Entire target
};
enum Magic_index : short
{
    Fire_I,
    Fire_II,
    Fire_III,
    Fire_IV,
    Heal,
    END_OF_INDEX
};

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
    constexpr Action(bn::string_view name, Target_type target, Action_type action,
                     int cost, int multiplier, int speed_multi,
                     Status_effect_index status_effect, int status_chance, int status_duration,
                     const bn::sprite_item& action_effect, int frames,
                     const bn::sound_item& action_sound) :
        _name(name),
        _target(target),
        _action(action),
        _cost(cost),
        _multiplier(multiplier),
        _speed(speed_multi),
        _status_effect(status_effect),
        _status_chance(status_chance),
        _status_duration(status_duration),
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
     * @brief Speed multiplier %
     */
    int _speed;
    /**
     * @brief Chance to induce status effect.
     * 0 ~ 100 (%)
     */
    int _status_chance;
    /**
     * @brief Index of status effect caused by action
     */
    Status_effect_index _status_effect;
    /**
     * @brief Turns needed to end status effect.
     */
    int _status_duration;

    // for effect
    const bn::sprite_item& _action_effect;
    int _frames;
    const bn::sound_item& _action_sound;
};

const Action& Get_action_data(Action_index index);
const Action& Get_magic_data(Magic_index index);

} // namespace Runa::Game

#endif // GAME_BATTLE_ACTION_H
