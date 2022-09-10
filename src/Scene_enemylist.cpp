#include "Scene_enemylist.h"

#include "bn_format.h"
#include "bn_regular_bg_items_bg_codex1.h"

namespace Runa::Scene
{

namespace
{
constexpr int MAX_PAGE = 17;
constexpr bn::string_view TEXT_LIST[4 * MAX_PAGE] = {
    "Appears in Alphabetic Grassland.", // choco attacker
    "Has strong offensive power,",
    "but very weak defensive power.",
    "Always does slash attack.",

    "Appears in Alphabetic Grassland.", // choco blocker
    "Has strong defensive power.",
    "Always guards.",
    "",

    "Appears in Alphabetic Grassland.", // choco charger
    "Charges before execute",
    "powerful attack.",
    "",

    "Appears in Alphabetic Grassland.", // choco healer
    "It never attacks,",
    "but heals other enemies.",
    "",

    "Appears in Alphabetic Grassland.", // choco normal
    "It doesn't have any weapons,",
    "so it can only do bash attack.",
    "",

    "Appears in Alphabetic Grassland.", // choco speedy
    "It can attack multiple times",
    "at high speed,",
    "but each attack is weak.",

    "Appears in Alphabetic Grassland.", // choco tanker
    "Has higher health than others",
    "and sometimes guards itself.",
    "",

    "Appears in Alphabetic Grassland.", // choco white
    "It never attacks,",
    "but does charged heal.",
    "",

    "Powerful gatekeeper", // choco boss * 1st stratum boss
    "who protects the gateway",
    "between Alphabetic Grassland",
    "and Bakery Street.",


    "Baked from the Bakery Street.", // chip cookie
    "Attacks by throwing its own",
    "chocolate chips.",
    "Vulnerable to physical attacks.",

    "Baked from the Bakery Street.", // checker cookie
    "Distracts the vision and",
    "gives the impression of being",
    "attacked from all sides.",

    "Baked from the Bakery Street.", // cracker
    "Doesn't contain chocolate,",
    "but gives more experience.",
    "Uses lightning magic.",

    "Baked from the Bakery Street.", // choco cracker
    "Contains more chocolates,",
    "but gives less experience.",
    "Uses fire magic.",

    "Baked from the Bakery Street.", // choco cake
    "Attacks after slowing the",
    "opponent with sticky chocolate.",
    "",

    "Baked from the Bakery Street.", // choco muffin
    "Blocks and withstands attacks,",
    "then self-destructs,",
    "inflicting great damage.",

    "Baked from the Bakery Street.", // donut
    "Recovers others at the expense",
    "of its own stamina.",
    "",

    "The greatest masterpiece of", // cookie house * 2nd stratum boss
    "the Bakery Street.",
    "Resides in front of the gate",
    "to the Chess Castle.",
};
constexpr int TEXT_X = -102;
constexpr int TEXT_Y = -64;
constexpr int TEXT_Y_INT = 12;

constexpr int GRAPHIC_X = 80;
constexpr int GRAPHIC_Y = -40;

} // namespace

Enemy_list::Enemy_list(bn::sprite_text_generator& text_generator, Status& status) :
    _text_generator(text_generator),
    _status(status),
    _bg_codex(bn::regular_bg_items::bg_codex1.create_bg(0, 0)),
    _enemy_graphic(Game::Enemy::Get_enemy_base_data(0).sprite_item.create_sprite(GRAPHIC_X, GRAPHIC_Y)),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));
    _bg_codex.set_blending_enabled(true);
    _bg_codex.set_priority(2);

    _enemy_graphic.set_bg_priority(3);

    Print_enemy_codex();
    _scene_start.Start();
}
Enemy_list::~Enemy_list() {}

bn::optional<Scene_Type> Enemy_list::Update()
{
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
            Print_enemy_codex();
        }
    }
    else if (bn::keypad::left_pressed())
    {
        if (--_current_page < 0) { ++_current_page; }
        else
        {
            bn::sound_items::sfx_menu_move.play();
            Print_enemy_codex();
        }
    }
    else if (bn::keypad::b_pressed())
    {
        bn::sound_items::sfx_menu_cancelled.play();
        _scene_end.Start();
    }

    return bn::nullopt;
}

void Enemy_list::Print_enemy_codex()
{
    _description_text.clear();
    if (_status.Get_Enemy_codex(_current_page+1) <= 0)
    {
        Effect::Print_text(_text_generator, true, Effect::Alignment::Left,
                           TEXT_X, TEXT_Y + TEXT_Y_INT * 7, TEXT_Y_INT, _description_text,
                           1, "Never encountered this enemy.");
        _enemy_graphic.set_visible(false);
    }
    else
    {
        _enemy_data = &Game::Enemy::Get_enemy_base_data(_current_page+1);

        _enemy_graphic = _enemy_data->sprite_item.create_sprite(GRAPHIC_X, GRAPHIC_Y);
        _enemy_graphic.set_visible(true);
        _enemy_graphic.set_blending_enabled(true);

        _text_generator.set_left_alignment();
        _text_generator.generate(TEXT_X + 16, TEXT_Y, _enemy_data->name, _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 2, bn::format<15>("{} eaten", _status.Get_Enemy_codex(_current_page+1)), _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 3, bn::format<12>("HP {}", _enemy_data->base_maxhp), _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 4, bn::format<12>("Choco {}", _enemy_data->base_choco), _description_text);
        _text_generator.generate(TEXT_X + 70, TEXT_Y + TEXT_Y_INT * 4, bn::format<10>("EXP {}", _enemy_data->base_exp), _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 5, bn::format<10>("ATK {}", _enemy_data->base_atk), _description_text);
        _text_generator.generate(TEXT_X + 70, TEXT_Y + TEXT_Y_INT * 5, bn::format<10>("DEF {}", _enemy_data->base_def), _description_text);
        _text_generator.generate(TEXT_X + 140, TEXT_Y + TEXT_Y_INT * 5, bn::format<10>("SPD {}", _enemy_data->base_spd), _description_text);
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
