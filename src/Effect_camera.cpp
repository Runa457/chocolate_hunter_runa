#include "Effect_camera.h"

namespace Runa::Effect
{

Camera::Camera() :
    _camera(bn::camera_ptr::create(0, 0))
{}
Camera::~Camera() {}

void Camera::Start_movement(bn::sprite_ptr& sprite)
{
    _sprite = &sprite;
    _frame_count = 16;

    _sprite->set_camera(_camera);
}

void Camera::Update()
{
    if (_frame_count > 0)
    {
        _camera.set_x((_frame_count % 6 < 3) ? _frame_count * 2 / 3 : -_frame_count * 2 / 3);
        --_frame_count;
    }
    else if (_sprite != nullptr)
    {
    _sprite->remove_camera();
    _sprite = nullptr;
    }
}

} // namespace Runa::Effect
