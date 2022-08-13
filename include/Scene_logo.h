#ifndef SCENE_LOGO_H
#define SCENE_LOGO_H

#include "Scene.h"
#include "Effect_transition.h"

#include "bn_regular_bg_ptr.h"

namespace Runa::Scene
{

class Logo final : public Scene_Root
{
public:
    Logo(bn::sprite_text_generator& text_generator);
    ~Logo();
    bn::optional<Scene_Type> Update();

private:
    bn::sprite_text_generator& _text_generator;
    bn::regular_bg_ptr _logo_bg;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 30;
    int _waiting_frame;
};

} // namespace Runa::Scene

#endif // SCENE_LOGO_H
