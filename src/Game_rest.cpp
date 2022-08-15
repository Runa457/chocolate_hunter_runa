#include "Game_rest.h"
#include "Stats_data.h"

#include "bn_sprite_items_cursor_0.h"

#include "bn_format.h"

namespace Runa::Game
{

namespace
{
static constexpr int CURSOR_X = -60;
static constexpr int CURSOR_Y = -16;
static constexpr int CURSOR_X_INT = 40;
}

Rest::Rest(bn::sprite_text_generator& text_generator,
           Status& status) :
    _status(status),
    _text_generator(text_generator),
    _cursor(bn::sprite_items::cursor_0.create_sprite(CURSOR_X, CURSOR_Y)),
    _current_menu(Menu::Regain_life),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    Print_text();

    _cursor.set_blending_enabled(true);
    for (bn::sprite_ptr& text_sprite : _text_sprite)
    {
        text_sprite.set_blending_enabled(true);
    }
    for (bn::sprite_ptr& text_sprite : _icon_sprite)
    {
        text_sprite.set_blending_enabled(true);
    }
    _scene_start.Start();
}
Rest::~Rest() {}

bn::optional<Game_Type> Rest::Update()
{
    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        Press_left_right();
        break;
    case Effect::State::Done:
        switch (_scene_end.Get_state())
        {
        case Effect::State::Waiting:
            Press_left_right();
            if (bn::keypad::a_pressed()) { Menu_selected(); }
            if (bn::keypad::r_pressed())
            {
                _status.Write();
                _save_text.clear();
                _text_generator.set_center_alignment();
                _text_generator.generate(0, -30, "Game saved.", _save_text);
                _text_generator.set_left_alignment();
            }
            if (bn::keypad::l_pressed()) { _scene_end.Start(); }
            break;
        case Effect::State::Ongoing:
            _scene_end.Update();
            break;
        case Effect::State::Done:
            return Game_Type::Choice;
            break;
        default: break;
        }
        break;
    default: break;
    }
    return bn::nullopt;
}

void Rest::Print_text()
{
    _text_generator.set_center_alignment();
    _text_generator.generate(0, -60, "Camp", _text_sprite);
    _text_generator.generate(0, -46, "Press L to proceed, R to save", _text_sprite);

    _text_generator.generate(CURSOR_X, 16, bn::format<4>("{}", 100), _text_sprite);
    _text_generator.generate(CURSOR_X+CURSOR_X_INT, 16, bn::format<4>("{}", 100), _text_sprite);
    _text_generator.generate(CURSOR_X+CURSOR_X_INT*2, 16, bn::format<4>("{}", 150), _text_sprite);
    _text_generator.generate(CURSOR_X+CURSOR_X_INT*3, 16, bn::format<4>("{}", 150), _text_sprite);
    _text_generator.set_left_alignment();

    _icon_sprite.push_back(bn::sprite_ptr(bn::sprite_items::cursor_0.create_sprite(CURSOR_X, 0)));
    _icon_sprite.push_back(bn::sprite_ptr(bn::sprite_items::cursor_0.create_sprite(CURSOR_X+CURSOR_X_INT, 0)));
    _icon_sprite.push_back(bn::sprite_ptr(bn::sprite_items::cursor_0.create_sprite(CURSOR_X+CURSOR_X_INT*2, 0)));
    _icon_sprite.push_back(bn::sprite_ptr(bn::sprite_items::cursor_0.create_sprite(CURSOR_X+CURSOR_X_INT*3, 0)));
}
void Rest::Press_left_right()
{
    if (bn::keypad::left_pressed()) Cursor_update(-1);
    else if (bn::keypad::right_pressed()) Cursor_update(1);
}
void Rest::Menu_selected()
{
    int choco = _status.Get_choco();
    int level = _status.Get_level();

    switch (_current_menu)
    {
    case Menu::Regain_life:
        if (choco >= 100)
        {
            _status.Life_regain();
            _status.Choco_earn(-100);
        }
        break;
    case Menu::Magic_potion:
        if (choco >= 100)
        {
            _status.Hp_change(Get_hp_data(level));
            _status.Mp_change(Get_mp_data(level));
            _status.turn_end();
            _status.Choco_earn(-100);
        }
        break;
    case Menu::Upgrade_sword:
        if (choco >= 150)
        {
            _status.Weapon_upgrade();
            _status.Choco_earn(-150);
        }
        break;
    case Menu::Upgrade_armor:
        if (choco >= 150)
        {
            _status.Armor_upgrade();
            _status.Choco_earn(-150);
        }
        break;
    }
}
void Rest::Cursor_update(int move_direction)
{
    _current_menu = static_cast<Menu>((_current_menu + 4 + move_direction) % 4);
    _cursor.set_position(CURSOR_X + CURSOR_X_INT * _current_menu, CURSOR_Y);
}

} // namespace Runa::Scene
