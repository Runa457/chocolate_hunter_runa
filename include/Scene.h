#ifndef SCENE_H
#define SCENE_H

#include "Scene_type.h"
#include "Effect_text.h"

#include "bn_optional.h"
#include "bn_keypad.h"
#include "bn_blending.h"
#include "bn_fixed_point.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_sound_items.h"

namespace Runa::Scene
{

class Scene_Root
{
public:
    Scene_Root() {}
    virtual ~Scene_Root() = default;
    virtual bn::optional<Scene_Type> Update();

protected:

};

} // namespace Runa::Scene

#endif // SCENE_H
