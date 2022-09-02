#include "Scene_enemylist.h"

#include "bn_format.h"

namespace Runa::Scene
{

namespace
{
constexpr int MAX_PAGE = 9;
constexpr bn::string_view TEXT_LIST[3 * MAX_PAGE] = {
    "Placeholder placeholder placeholder",
    "placeholder placeholder place",
    "holder placeholder placeholder",

};
constexpr int TEXT_X = -110;
constexpr int TEXT_Y = -64;
constexpr int TEXT_Y_INT = 12;

} // namespace

Enemy_list::Enemy_list(bn::sprite_text_generator& text_generator, Status& status) :
    _text_generator(text_generator),
    _status(status),
    _scene_start(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES)
{
    Effect::Print_text(_text_generator, true, Effect::Alignment::Left,
                       TEXT_X, TEXT_Y + TEXT_Y_INT * 10, TEXT_Y_INT, _sub_text,
                       2, "Press left or right key to switch", "page, B to return");
    for (bn::sprite_ptr& text_sprite : _sub_text) { text_sprite.set_blending_enabled(true); }

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
                           TEXT_X, TEXT_Y + TEXT_Y_INT * 6, TEXT_Y_INT, _description_text,
                           1, "This enemy has never encountered.");
    }
    else
    {
        _enemy_data = &Game::Enemy::Get_enemy_base_data(_current_page+1);
        _text_generator.generate(TEXT_X, TEXT_Y, _enemy_data->name, _description_text);
        //1 stratum
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 2, bn::format<15>("Base HP: {}", _enemy_data->base_maxhp), _description_text);
        _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * 3, bn::format<30>("Base Choco: {} Base EXP: {}", _enemy_data->base_choco, _enemy_data->base_exp), _description_text);
        //4 atk def spd
        //5 empty line
        _text_generator.set_left_alignment();
        for (int i = 0; i < 3; i++)
        {
            _text_generator.generate(TEXT_X, TEXT_Y + TEXT_Y_INT * (6 + i), TEXT_LIST[i + 3 * _current_page], _description_text);
        }
    }
    _page_text.clear();
    _text_generator.set_right_alignment();
    _text_generator.generate(112, TEXT_Y + TEXT_Y_INT * 11, bn::format<10>("< {} / {} >", _current_page+1, MAX_PAGE), _page_text);

    for (bn::sprite_ptr& text_sprite : _description_text) { text_sprite.set_blending_enabled(true); }
    for (bn::sprite_ptr& text_sprite : _page_text) { text_sprite.set_blending_enabled(true); }
}

} // namespace Runa::Scene
