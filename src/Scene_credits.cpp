#include "Scene_credits.h"

namespace Runa::Scene
{

namespace
{
constexpr int NUM_CREDITS = 12;
constexpr bn::string_view CREDITS_LIST[NUM_CREDITS] = {
    "-Chocolate Hunter Runa-",
    "",
    "Made with Butano 10.5.0",
    "",
    "Programming: Lsh Games",
    "Music:",
    "Graphics: Lsh Games",
    "",
    "Special Thanks: copyrat90",
    "",
    "",
    "Press B to return"
};
constexpr int CREDITS_X = -100;
constexpr int CREDITS_Y = -64;
constexpr int CREDITS_Y_INT = 12;

} // namespace

Credits::Credits(bn::sprite_text_generator& text_generator) :
    _text_generator(text_generator),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    Effect::Print_text(_text_generator, true, Effect::Alignment::Left,
                       CREDITS_X, CREDITS_Y, CREDITS_Y_INT, _credits_text, CREDITS_LIST);
    for (bn::sprite_ptr& text_sprite : _credits_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    _scene_start.Start();
}
Credits::~Credits() {}

bn::optional<Scene_Type> Credits::Update()
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
            if (bn::keypad::b_pressed())
            {
                bn::sound_items::sfx_menu_cancelled.play();
                _scene_end.Start();
            }
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
