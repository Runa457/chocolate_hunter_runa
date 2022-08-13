#ifndef SCENE_CREDITS_H
#define SCENE_CREDITS_H

#include "Scene.h"
#include "Effect_transition.h"
#include "bn_sprite_ptr.h"

namespace Runa::Scene
{

class Credits final: public Scene_Root
{
public:
    Credits(bn::sprite_text_generator& text_generator);
    ~Credits();
    bn::optional<Scene_Type> Update();

private:
    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 50> _credits_text;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 15;
};

} // namespace Runa::Scene

#endif // SCENE_CREDITS_H
