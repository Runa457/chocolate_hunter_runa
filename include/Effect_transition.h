#ifndef EFFECT_TRANSITION_H
#define EFFECT_TRANSITION_H

#include "bn_optional.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_bgs_mosaic_actions.h"
#include "bn_sprites_mosaic_actions.h"

namespace Runa::Effect
{

enum class State : char
{
    Waiting,
    Ongoing,
    Done
};

enum Type : char
{
    None = 0,
    Fade = 1,
    Transparency = 2,
    Intensity = 4,
    Sprite_mosaic = 8,
    Bg_mosaic = 16
};

enum Direction : char
{
    Out = 0,
    In = 1
};

class Transition
{
public:
    Transition(Type type, Direction direction, int transition_frame);
    ~Transition();
    void Update();
    void Init();
    State Get_state();

private:
    Type _type;

    /**
     * @brief Out for fadeout / In for fadein
     */
    Direction _direction;

    /**
     * @brief Total number of frames
     */
    int _transition_frame;

    /**
     * @brief Current state of transition object.
     * Waiting : Effect is not started yet.
     * Ongoing : Effect is being applied.
     * Done : Effect is done.
     */
    State _state;

    bn::optional<bn::blending_fade_alpha_to_action> _fade_action;
    bn::optional<bn::blending_transparency_alpha_to_action> _transparency_action;
    bn::optional<bn::blending_intensity_alpha_to_action> _intensity_action;
    bn::optional<bn::sprites_mosaic_stretch_to_action> _sprite_mosaic_action;
    bn::optional<bn::bgs_mosaic_stretch_to_action> _bg_mosaic_action;
};

} // namespace Runa::Effect

#endif // EFFECT_TRANSITION_H
