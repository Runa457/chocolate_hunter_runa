#ifndef EFFECT_CAMERA_H
#define EFFECT_CAMERA_H

#include "bn_camera_ptr.h"
#include "bn_sprite_ptr.h"

namespace Runa::Effect
{

class Camera
{
public:
    Camera();
    ~Camera();

    void Start_movement(bn::sprite_ptr& sprite);
    void Update();

private:
    bn::camera_ptr _camera;
    int _frame_count = 0;

    bn::sprite_ptr* _sprite = nullptr;

};

} // namespace Runa::Effect

#endif // EFFECT_CAMERA_H
