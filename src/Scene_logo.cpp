#include "Scene_logo.h"

#include "bn_regular_bg_items_lsh_games_logo.h"

namespace Runa::Scene
{

Logo::Logo(bn::sprite_text_generator& text_generator) :
    _text_generator(text_generator),
    _logo_bg(bn::regular_bg_items::lsh_games_logo.create_bg(0, 0)),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES),
    _waiting_frame(90)
{
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));

    _logo_bg.set_blending_enabled(true);
    _logo_bg.set_mosaic_enabled(true);

    _scene_start.Init();
}
Logo::~Logo() {}

bn::optional<Scene_Type> Logo::Update()
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
            if (bn::keypad::a_held() || --_waiting_frame <= 0)
                { _scene_end.Init(); }
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
