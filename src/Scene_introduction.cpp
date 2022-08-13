#include "Scene_introduction.h"

namespace Runa::Scene
{

namespace
{
constexpr int NUM_INTRO = 12;
constexpr bn::string_view INTRO_LIST[NUM_INTRO] = {
    " Hunt for chocolates!",
    "",
    "Chocolate hunter Runa is",
    "addicted to chocolate.",
    "She must eat chocolate",
    "within certain time limit.",
    "",
    "placeholder",
    "",
    "",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "Press B to return"
};
constexpr int INTRO_X = -110;
constexpr int INTRO_Y = -64;
constexpr int INTRO_Y_INT = 12;

} // namespace

Introduction::Introduction(bn::sprite_text_generator& text_generator) :
    _text_generator(text_generator),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    for (int i = 0; i < NUM_INTRO; i++)
    {
        _text_generator.generate(INTRO_X, INTRO_Y + INTRO_Y_INT * i, INTRO_LIST[i], _intro_text);
    }
    for (bn::sprite_ptr& text_sprite : _intro_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    _scene_start.Init();
}
Introduction::~Introduction() {}

bn::optional<Scene_Type> Introduction::Update()
{
    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        break;
    case Effect::State::Done:
        switch (_scene_end.Get_state())
        {
        case Effect::State::Waiting:
            if (bn::keypad::b_pressed()) { _scene_end.Init(); }
            break;
        case Effect::State::Ongoing:
            _scene_end.Update();
            break;
        case Effect::State::Done:
            return Scene_Type::Title;
            break;
        default: break;
        }
        break;
    default: break;
    }
    return bn::nullopt;
}

} // namespace Runa::Scene
