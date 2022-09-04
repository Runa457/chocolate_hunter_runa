#include "Scene_magiclist.h"
#include "Game_battle_statuseffect.h"

#include "bn_format.h"
#include "bn_regular_bg_items_bg_codex2.h"

namespace Runa::Scene
{

namespace
{

constexpr int MAX_PAGE = 15;
constexpr bn::string_view TEXT_LIST[4 * MAX_PAGE] = {
    "Basic flame magic.", // Fire I
    "Concentrate thermal energy",
    "to enemy, inducing",
    "thermal decomposition.",

    "Basic ice magic.", // Ice I
    "Disperse thermal energy",
    "from enemy, lowering",
    "enemy's temperature greatly.",

    "Basic electric magic.", // Lightning I
    "Emit powerful, fast",
    "electromagnetic waves to",
    "disturb the nervous system.",

    "Create force field which", // Defence Up
    "weakens enemy attacks,",
    "raising defensive power.",
    "",

    "Change the flow of mana to", // Attack Up
    "increase the effectiveness",
    "of attacks.",
    "",

    "Create magical shield to defend", // Barrier
    "from enemy attacks for a while.",
    "It has same effect as the",
    "normal guard action, but longer.",

    "Concentrate the mana on self", // Charge
    "for the next action.",
    "The power of the next action",
    "is doubled.",

    "Multiple flame attack.", // Fire II
    "Radiate thermal energy",
    "randomly and multiple times.",
    "",

    "Advanced ice magic.", // Ice II
    "Condense all the liquid",
    "inside of the enemy,",
    "inflicting great damage.",

    "Accelerate the flow of energy", // Heal I
    "in the body and recover health",
    "quickly.",
    "",

    "Increase the weight of the", // Weaken
    "enemy and reduce offensive",
    "power.",
    "",

    "Decompose enemy's tissue", // Soften
    "to soften it, and lower",
    "enemy's defensive power.",
    "",

    "Dancing with a sword and", // Sword Dance
    "attacking everyone in the battle.",
    "Causes bleeding.",
    "Cost no mana.",

    "Will be changed", // Fire III
    "",
    "",
    "",

    "Will be changed", // Fire IV
    "",
    "",
    "",
};

constexpr int TEXT_X = -102;
constexpr int TEXT_Y = -64;
constexpr int TEXT_Y_INT = 12;

constexpr int GRAPHIC_X = 80;
constexpr int GRAPHIC_Y = -40;

} // namespace

Magic_list::Magic_list(bn::sprite_text_generator& text_generator, Status& status) :
    _text_generator(text_generator),
    _status(status),
    _bg_codex(bn::regular_bg_items::bg_codex2.create_bg(0, 0)),
    _magic_graphic(Game::Action::Get_magic_data(0)._action_effect.create_sprite(GRAPHIC_X, GRAPHIC_Y)),
    _magic_effect(bn::create_sprite_animate_action_forever(_magic_graphic, 1, Game::Action::Get_magic_data(0)._action_effect.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8)),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));
    _bg_codex.set_blending_enabled(true);
    _bg_codex.set_priority(2);

    _magic_graphic.set_blending_enabled(true);
    _magic_graphic.set_bg_priority(3);

    Print_magic_codex();
    _scene_start.Start();
}
Magic_list::~Magic_list() {}

bn::optional<Scene_Type> Magic_list::Update()
{
    _magic_effect.update();

    switch (_scene_start.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_start.Update();
        return bn::nullopt;
    case Effect::State::Done:
        break;
    default: break;
    }

    switch (_scene_end.Get_state())
    {
    case Effect::State::Waiting:
        break;
    case Effect::State::Ongoing:
        _scene_end.Update();
        return bn::nullopt;
    case Effect::State::Done:
        return Scene_Type::Options;
    default: break;
    }

    if (bn::keypad::right_pressed())
    {
        if (++_current_page == MAX_PAGE) { --_current_page; }
        else
        {
            bn::sound_items::sfx_menu_move.play();
            Print_magic_codex();
        }
    }
    else if (bn::keypad::left_pressed())
    {
        if (--_current_page < 0) { ++_current_page; }
        else
        {
            bn::sound_items::sfx_menu_move.play();
            Print_magic_codex();
        }
    }
    else if (bn::keypad::b_pressed())
    {
        bn::sound_items::sfx_menu_cancelled.play();
        _scene_end.Start();
    }

    return bn::nullopt;
}

void Magic_list::Print_magic_codex()
{
    _description_text.clear();
    if (_status.Get_Max_level() < _current_page)
    {
        Effect::Print_text(_text_generator, true, Effect::Alignment::Left,
                           TEXT_X, TEXT_Y + TEXT_Y_INT * 7, TEXT_Y_INT, _description_text,
                           1, "Never learned this magic.");
        _magic_graphic.set_visible(false);
    }
    else
    {
        _action = &Game::Action::Get_magic_data(_current_page);

        _magic_graphic.set_visible(true);
        _magic_graphic.set_palette(_action->_action_effect.palette_item());
        _magic_effect = bn::create_sprite_animate_action_forever(_magic_graphic, _action->_frames, _action->_action_effect.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8);

        _text_generator.set_left_alignment();
        _text_generator.generate(TEXT_X + 16, TEXT_Y, _action->_name, _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 2, Game::Action::Print_element_type(_action->_element), _description_text);
        _text_generator.generate(TEXT_X + 70, TEXT_Y + TEXT_Y_INT * 2, Game::Action::Print_target_type(_action->_target), _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 3, bn::format<12>("Cost {}", _action->_cost), _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 4, bn::format<12>("DMG {}%", _action->_multiplier), _description_text);
        _text_generator.generate(TEXT_X + 70, TEXT_Y + TEXT_Y_INT * 4, bn::format<12>("SPD {}%", _action->_speed), _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 5, Game::Print_status_effect(_action->_status_effect), _description_text);
        _text_generator.generate(TEXT_X + 70, TEXT_Y + TEXT_Y_INT * 5, bn::format<12>("Prob. {}%", _action->_status_chance), _description_text);
        _text_generator.generate(TEXT_X + 140, TEXT_Y + TEXT_Y_INT * 5, bn::format<12>("{} TURNS", _action->_status_duration), _description_text);
        for (int i = 0; i < 4; i++)
        {
            _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * (7 + i), TEXT_LIST[i + 4 * _current_page], _description_text);
        }
    }
    _page_text.clear();
    _text_generator.set_right_alignment();
    _text_generator.generate(112, TEXT_Y + TEXT_Y_INT * 11, bn::format<14>("< {} / {} >", _current_page+1, MAX_PAGE), _page_text);

    for (bn::sprite_ptr& text_sprite : _description_text) { text_sprite.set_blending_enabled(true); }
    for (bn::sprite_ptr& text_sprite : _page_text) { text_sprite.set_blending_enabled(true); }
}

} // namespace Runa::Scene
