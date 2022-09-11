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
    bn::vector<bn::sprite_ptr, 60> _intro_text;
    bn::vector<bn::sprite_ptr, 20> _sub_text;
    bn::vector<bn::sprite_ptr, 5> _page_text;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 15;

    int _current_page = 0;
    void Print_text();
};

} // namespace Runa::Scene

#endif // SCENE_INTRODUCTION_H
