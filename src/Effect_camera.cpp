#include "Effect_camera.h"

namespace Runa::Effect
{

Camera::Camera() :
    _attacker_camera(bn::camera_ptr::create(0, 0)),
    _defender_camera(bn::camera_ptr::create(0, 0))
{}
Camera::~Camera() {}

void Camera::Start_movement()
{
    _frame_count = 16;
}
void Camera::Set_attacker(bn::sprite_ptr& sprite)
{
    _attacker_sprite = &sprite;
    _attacker_sprite->set_camera(_attacker_camera);
}
void Camera::Set_defender(bn::sprite_ptr& sprite)
{
    _defender_sprite = &sprite;
    _defender_sprite->set_camera(_defender_camera);
}

void Camera::Update()
{
    if (_frame_count > 0)
    {
        if (_attacker_sprite != nullptr)
        {
            _attacker_camera.set_y(-_frame_count/3);
        }
        if (_defender_sprite != nullptr)
        {
            _defender_camera.set_x((_frame_count % 6 < 3) ? _frame_count * 2 / 3 : -_frame_count * 2 / 3);
        }
        --_frame_count;
    }
    else
    {
        if (_attacker_sprite != nullptr)
        {
        _attacker_sprite->remove_camera();
        _attacker_sprite = nullptr;
        }
        if (_defender_sprite != nullptr)
        {
        _defender_sprite->remove_camera();
        _defender_sprite = nullptr;
        }
    }
}

} // namespace Runa::Effect
