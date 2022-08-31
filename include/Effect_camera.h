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

    void Start_movement();
    void Set_attacker(bn::sprite_ptr& sprite);
    void Set_defender(bn::sprite_ptr& sprite);
    void Update();

private:
    bn::camera_ptr _attacker_camera;
    bn::camera_ptr _defender_camera;

    bn::sprite_ptr* _attacker_sprite = nullptr;
    bn::sprite_ptr* _defender_sprite = nullptr;

    int _frame_count = 0;
};

} // namespace Runa::Effect

#endif // EFFECT_CAMERA_H
