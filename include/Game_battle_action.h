#ifndef GAME_BATTLE_ACTION_H
#define GAME_BATTLE_ACTION_H

#include "Game_battle_statuseffect.h"

#include "bn_sound_item.h"
#include "bn_sprite_item.h"
#include "bn_string_view.h"

namespace Runa::Game::Action
{

enum class Action_index : short
{
    // Self target
    Guard,
    Charge,
    Super_Charge,
    Heal_I,
    Attack_Up,
    Defense_Up,
    Barrier,
    // Single target
    Slash,
    Bash,
    Throw,
    Quicksand, // Earth I
    Fire_I,
    Ice_I,
    Ice_II,
    Ice_III,
    Lightning_I,
    Weaken, // Gravity I
    Soften, // Acid I
    // Multi hit
    Triple_Slash,
    Confusion,
    Fire_II,
    Fire_III,
    Sandstorm, // Earth II
    // Every enemy target
    Area_Heal_I,
    Lightning_II,
    Acid_Rain, // Acid II
    // Entire target
    Sword_Dance,
    Explosion,
};
enum Magic_index : short
{
    Fire_I,
    Ice_I,
    Lightning_I,
    Defense_Up,
    Attack_Up,

    Barrier,
    Charge,
    Fire_II,
    Ice_II,
    Heal_I,

    Sword_Dance,
    Weaken,
    Soften,
    Lightning_II,
    Sandstorm,

    Acid_Rain,
    Fire_III,
    Ice_III,
    // Regeneration

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
    Normal_attack, // Use STR
    Magic_attack, // Use INT
};

enum class Element_type : char
{
    None,
    Physical,
    Fire,
    Ice,
    Lightning,
};

class Action
{
public:
    constexpr Action(bn::string_view name, Target_type target, Action_type action, Element_type element,
                     int cost, int multiplier, int speed_multi,
                     Status_effect_index status_effect, int status_chance, int status_duration,
                     const bn::sprite_item& action_effect, int frames,
                     const bn::sound_item& action_sound) :
        _name(name),
        _target(target),
        _action(action),
        _element(element),
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
    Element_type _element;

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
     * @brief Index of status effect caused by action
     */
    Status_effect_index _status_effect;
    /**
     * @brief Chance to induce status effect.
     * 0 ~ 100 (%)
     */
    int _status_chance;
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
const Action& Get_magic_data(int index);

const bn::string_view Print_target_type(Target_type target);
const bn::string_view Print_element_type(Element_type element);

} // namespace Runa::Game

#endif // GAME_BATTLE_ACTION_H
