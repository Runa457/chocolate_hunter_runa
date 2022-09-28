#include "Scene_game.h"
#include "Game_battle.h"
#include "Game_choice.h"
#include "Game_rest.h"
#include "Stats_data.h"

#include "bn_format.h"
#include "bn_music.h"
#include "bn_music_items.h"

#include "bn_sprite_items_icon_choco.h"
#include "bn_regular_bg_items_bg_interface.h"
#include "bn_regular_bg_items_bg_stratum_1.h"
#include "bn_regular_bg_items_bg_stratum_2.h"
#include "bn_regular_bg_items_bg_stratum_3.h"
#include "bn_sprite_items_portrait_default.h"

namespace Runa::Scene
{

Game::Game(bn::sprite_text_generator& text_generator,
           bn::random& random_generator,
           Status& status) :
    _random(random_generator),
    _status(status),
    _bg_interface(bn::regular_bg_items::bg_interface.create_bg(0, 0)),
    _bg_stratum(bn::regular_bg_items::bg_stratum_1.create_bg(0, 0)),
    _player_sprite(bn::sprite_items::portrait_default.create_sprite(-90, 57)),
    _subscene(),
    _game_mode(Runa::Game::Game_Type::Rest),
    _text_generator(text_generator),
    _scene_begin(Effect::Type::Transparency, Effect::Direction::In, TRANSITION_FRAMES),
    _scene_end(Effect::Type::Transparency, Effect::Direction::Out, TRANSITION_FRAMES * 2)
{
    _choco_icon.push_back(bn::sprite_items::icon_choco.create_sprite(112, -72));
    _choco_icon.push_back(bn::sprite_items::icon_choco.create_sprite(112, 72));

    _choco_icon[0].set_bg_priority(0);
    _choco_icon[1].set_bg_priority(0);

    _player_sprite.set_z_order(1);
    _player_sprite.set_bg_priority(0);
    _player_sprite.set_blending_enabled(true);

    _bg_stratum.set_priority(3);
    _bg_interface.set_priority(2);

    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));
    Handle_Stratum();
    Print_text();

    _bg_stratum.set_blending_enabled(true);
    _bg_interface.set_blending_enabled(true);
    for (bn::sprite_ptr& icon_sprite : _choco_icon)
    {
        icon_sprite.set_blending_enabled(true);
    }
    for (bn::sprite_ptr& text_sprite : _status_text)
    {
        text_sprite.set_blending_enabled(true);
    }
    _scene_begin.Start();
}
Game::~Game() {}

bn::optional<Scene_Type> Game::Update()
{
    switch (_scene_begin.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_begin.Update();
        return bn::nullopt;
    case Effect::State::Done:
        _player_sprite.set_blending_enabled(false);
        _bg_stratum.set_blending_enabled(false);
        _bg_interface.set_blending_enabled(false);
        for (bn::sprite_ptr& icon_sprite : _choco_icon)
        {
            icon_sprite.set_blending_enabled(false);
        }
        for (bn::sprite_ptr& text_sprite : _status_text)
        {
            text_sprite.set_blending_enabled(false);
        }
        _scene_begin.Reset();
        break;
    default:
        break;
    }

    switch (_scene_end.Get_state())
    {
    case Effect::State::Ongoing:
        _scene_end.Update();
        return bn::nullopt;
    case Effect::State::Done:
        return Scene_Type::Title;
    default:
        break;
    }

    if (_status.Value_changed())
    {
        Handle_Stratum();
        Print_text();
    }
    if (_subscene) { _game_mode = _subscene->Update(); }
    if (_game_mode)
    {
        switch (*_game_mode)
        {
        case Runa::Game::Game_Type::Battle:
            _subscene.reset(new Runa::Game::Battle(_text_generator, _random, _status, _player_sprite, _battle_sq, _print_actor_status));
            break;
        case Runa::Game::Game_Type::Result:
            if (bn::keypad::a_pressed())
            {
                _status.Read();

                _player_sprite.set_blending_enabled(true);
                _bg_stratum.set_blending_enabled(true);
                _bg_interface.set_blending_enabled(true);
                for (bn::sprite_ptr& icon_sprite : _choco_icon)
                {
                    icon_sprite.set_blending_enabled(true);
                }
                for (bn::sprite_ptr& text_sprite : _status_text)
                {
                    text_sprite.set_blending_enabled(true);
                }
                _scene_end.Start();
            }
            break;
        case Runa::Game::Game_Type::Rest:
            _subscene.reset(new Runa::Game::Rest(_text_generator, _status));
            break;
        case Runa::Game::Game_Type::Choice:
            _subscene.reset(new Runa::Game::Choice(_text_generator, _random, _status, _battle_sq));
            break;
        case Runa::Game::Game_Type::Exit:
            _subscene.reset();
            _status.Game_over();
            _status.Value_changed();
            bn::music::stop();
            Print_text();
            Effect::Print_text(_text_generator, false, Effect::Alignment::Center, 0, -24, 0, _status_text, 1, "Game over");
            _text_generator.generate(0, 0, bn::format<12>("Score: {}", _status.Get_Total_turn()), _status_text);
            _text_generator.generate(0, 12, bn::format<16>("Highscore: {}", _status.Get_Max_turn()), _status_text);
            _game_mode = Runa::Game::Game_Type::Result;
            break;
        default:
            BN_ERROR("Unknown Scene type: ", (int)*_game_mode);
            break;
        }
    }
    return bn::nullopt;
}
void Game::Handle_Stratum()
{
    if (_current_stratum != _status.Get_stratum())
    {
        _current_stratum = _status.Get_stratum();
        switch (_current_stratum)
        {
        case 1:
            _bg_stratum.set_item(bn::regular_bg_items::bg_stratum_1);
            bn::music_items::k_jose__tropical_feels.play(bn::fixed(_status.Get_Volume()) / 100);
            break;
        case 2:
            _bg_stratum.set_item(bn::regular_bg_items::bg_stratum_2);
            bn::music_items::k_jose__merrily_strolling.play(bn::fixed(_status.Get_Volume()*0.5) / 100);
            break;
        case 3:
            _bg_stratum.set_item(bn::regular_bg_items::bg_stratum_3);
            bn::music_items::pxf_squarevox.play(bn::fixed(_status.Get_Volume()*0.5) / 100);
            break;
        default:
            _bg_stratum.set_item(bn::regular_bg_items::bg_stratum_3);
            bn::music_items::pxf_squarevox.play(bn::fixed(_status.Get_Volume()*0.5) / 100);
            //BN_ERROR("Background needed");
            break;
        }
    }
}
void Game::Print_text()
{
    int level = _status.Get_level();
    _status_text.clear();
    _text_generator.set_left_alignment();
    _text_generator.generate(-116, -73, bn::format<10>("Stratum {}", _status.Get_stratum()), _status_text);
    _text_generator.generate(-60, 42, bn::format<17>("Lv: {} - {}%", level, _status.Get_exp()*100/Get_exp_data(level)), _status_text);
    _text_generator.generate(-60, 52, bn::format<17>("Hp: {}/ {}", _status.Get_hp(), Get_hp_data(level)), _status_text);
    _text_generator.generate(-60, 62, bn::format<17>("Mp: {}/ {}", _status.Get_mp(), Get_mp_data(level)), _status_text);
    _text_generator.generate(-60, 72, bn::format<17>("Left turns: {}", _status.Get_turns()), _status_text);
    _text_generator.set_right_alignment();
    _text_generator.generate(104, 72, bn::format<7>("{}", _status.Get_choco()), _status_text);
    _text_generator.generate(104, -73, bn::format<4>("{}%", _status.Get_multiplier()), _status_text);
}

} // namespace Runa::Scene
