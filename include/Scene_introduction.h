#ifndef SCENE_INTRODUCTION_H
#define SCENE_INTRODUCTION_H

#include "Scene.h"
#include "Effect_transition.h"
#include "bn_sprite_ptr.h"

namespace Runa::Scene
{

class Introduction final: public Scene_Root
{
public:
    Introduction(bn::sprite_text_generator& text_generator);
    ~Introduction();
    bn::optional<Scene_Type> Update();

private:
    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 50> _intro_text;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 15;
};

} // namespace Runa::Scene

#endif // SCENE_INTRODUCTION_H
