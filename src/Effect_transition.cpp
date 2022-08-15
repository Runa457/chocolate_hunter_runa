#include "Effect_transition.h"

#include "bn_sprites_mosaic.h"

namespace Runa::Effect
{

Transition::Transition(Type type, Direction direction, int transition_frame) :
    _type(type),
    _direction(direction),
    _transition_frame(transition_frame),
    _frame_left(transition_frame),
    _state(State::Waiting)
{}
Transition::~Transition() {}
void Transition::Update()
{
    if (_state != State::Ongoing) { return; }

    if (_fade_action) { _fade_action->update(); }
    else
    {
        if (_transparency_action) { _transparency_action->update(); }
        if (_intensity_action) { _intensity_action->update(); }
    }
    if (_sprite_mosaic_action) { _sprite_mosaic_action->update(); }
    if (_bg_mosaic_action) { _bg_mosaic_action->update(); }

    if (--_frame_left <= 0)
    {
        _fade_action.reset();
        _transparency_action.reset();
        _intensity_action.reset();
        _sprite_mosaic_action.reset();
        _bg_mosaic_action.reset();

        _state = State::Done;
    }
}
void Transition::Reset()
{
    _frame_left = _transition_frame;
    _state = State::Waiting;
}
void Transition::Start()
{
    _frame_left = _transition_frame;

    /* Fade effect and transparency/intensity effect cannot be applied at the same time. */
    if ((_type & Type::Fade) != 0)
    {
        bn::blending::set_fade_alpha(_direction);
        _fade_action = bn::blending_fade_alpha_to_action(_transition_frame, !_direction);
    }
    else
    {
        if ((_type & Type::Transparency) != 0)
        {
            bn::blending::set_transparency_alpha(!_direction);
            _transparency_action = bn::blending_transparency_alpha_to_action(_transition_frame, _direction);
        }
        if ((_type & Type::Intensity) != 0)
        {
            bn::blending::set_intensity_alpha(_direction);
            _intensity_action = bn::blending_intensity_alpha_to_action(_transition_frame, !_direction);
        }
    }
    if ((_type & Type::Sprite_mosaic) != 0)
    {
        bn::sprites_mosaic::set_stretch(_direction);
        _sprite_mosaic_action = bn::sprites_mosaic_stretch_to_action(_transition_frame, !_direction);
    }
    if ((_type & Type::Bg_mosaic) != 0)
    {
        bn::bgs_mosaic::set_stretch(_direction);
        _bg_mosaic_action = bn::bgs_mosaic_stretch_to_action(_transition_frame, !_direction);
    }
    _state = State::Ongoing;
}
State Transition::Get_state()
{
    return _state;
}

} // namespace Runa::Effect
