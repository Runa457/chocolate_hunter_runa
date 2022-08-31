#include "Scene_title.h"

#include "bn_sprite_items_cursor_0.h"
#include "bn_regular_bg_items_bg_title.h"

namespace Runa::Scene
{

namespace
{
static constexpr int MENU_X = -80;
static constexpr int MENU_Y = 20;
static constexpr int MENU_Y_INT = 12;
}

Title::Title(bn::sprite_text_generator& text_generator) :
    _text_generator(text_generator),
    _cursor(bn::sprite_items::cursor_0.create_sprite(MENU_X-10, MENU_Y)),
    _bg_title(bn::regular_bg_items::bg_title.create_bg(0, 0)),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
    //bg(bn::regular_bg_items::bg_title.create_bg(0, 0))
{
    Print_text();
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));
    _bg_title.set_blending_enabled(true);

    _cursor.set_blending_enabled(true);
    for (bn::sprite_ptr& text_sprite : _menu_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    _scene_start.Start();
}
Title::~Title() {}

bn::optional<Scene_Type> Title::Update()
{
    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        Press_up_down();
        break;
    case Effect::State::Done:
        switch (_scene_end.Get_state())
        {
        case Effect::State::Waiting:
            Press_up_down();
            if (bn::keypad::a_pressed())
            {
                bn::sound_items::sfx_menu_selected.play();
                _scene_end.Start();
            }
            break;
        case Effect::State::Ongoing:
            _scene_end.Update();
            break;
        case Effect::State::Done:
            return Get_next_scene();
            break;
        default: break;
        }
        break;
    default: break;
    }
    return bn::nullopt;
}

void Title::Press_up_down()
{
    if (bn::keypad::up_pressed()) Cursor_update(-1);
    else if (bn::keypad::down_pressed()) Cursor_update(1);
}
void Title::Cursor_update(int move_direction)
{
    bn::sound_items::sfx_menu_move.play();
    _current_menu = static_cast<Menu>((_current_menu + NUM_MENU_OPTIONS + move_direction) % NUM_MENU_OPTIONS);
    _cursor.set_position(MENU_X-10, MENU_Y + _current_menu * MENU_Y_INT);
}
bn::optional<Scene_Type> Title::Get_next_scene()
{
    switch (_current_menu)
    {
    case Menu::Main_game_start:
        return Scene_Type::Main_game;
    case Menu::Introduction:
        return Scene_Type::Introduction;
    case Menu::Options:
        return Scene_Type::Options;
    case Menu::Credits:
        return Scene_Type::Credits;
    case Menu::Back_to_logo:
        return Scene_Type::Logo;
    default:
        BN_ERROR("Unknown Menu type: ", (int)_current_menu);
    }
    return bn::nullopt;
}
void Title::Print_text()
{
    Effect::Print_text(_text_generator, true, Effect::Alignment::Left,
                       MENU_X, MENU_Y, MENU_Y_INT, _menu_text,
                       5, "Start", "Introdunction", "Options", "Credits", "Back to title");
    /*
    for (int i = 0; i < NUM_MENU_OPTIONS; i++)
    {
        _text_generator.generate(MENU_X, MENU_Y + MENU_Y_INT * i, MENU_LISTS[i], _menu_text);
    }
    */
}

} // namespace Runa::Scene
