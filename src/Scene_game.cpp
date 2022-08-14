#include "Scene_game.h"
#include "Game_battle.h"
#include "Game_choice.h"
#include "Stats_data.h"

#include "bn_format.h"

namespace Runa::Scene
{

Game::Game(bn::sprite_text_generator& text_generator,
           bn::random& random_generator,
           Status& status) :
    _random(random_generator),
    _status(status),
    _text_generator(text_generator),
    _subscene(new Runa::Game::Choice(text_generator, random_generator, status, _battle_sq))
{
    bn::bg_palettes::set_transparent_color(bn::color(8, 8, 8));
    Print_text();
}
Game::~Game() {}

bn::optional<Scene_Type> Game::Update()
{
    if (_status.Value_changed()) { Print_text(); }
    if (_subscene) { _game_mode = _subscene->Update(); }
    if (_game_mode)
    {
        switch (*_game_mode)
        {
        case Runa::Game::Game_Type::Battle:
            _subscene.reset(new Runa::Game::Battle(_text_generator, _status, _battle_sq));
            break;
        case Runa::Game::Game_Type::Result:
            _subscene.reset();
            break;
        case Runa::Game::Game_Type::Rest:
            _subscene.reset();
            break;
        case Runa::Game::Game_Type::Choice:
            _subscene.reset(new Runa::Game::Choice(_text_generator, _random, _status, _battle_sq));
            break;
        case Runa::Game::Game_Type::Exit:
            return Scene_Type::Title;
        default:
            BN_ERROR("Unknown Scene type: ", (int)*_game_mode);
            break;
        }
    }
    return bn::nullopt;
}

void Game::Print_text()
{
    _status_text.clear();
    _text_generator.generate(-60, 42, bn::format<10>("Level: {}", _status.Get_level()), _status_text);
    _text_generator.generate(-60, 52, bn::format<17>("Hp: {}/ {}", _status.Get_hp(), Get_hp_data(_status.Get_level())), _status_text);
    _text_generator.generate(-60, 62, bn::format<17>("Mp: {}/ {}", _status.Get_mp(), Get_mp_data(_status.Get_level())), _status_text);
    _text_generator.generate(-60, 72, bn::format<17>("Left turns: {}", _status.Get_turns()), _status_text);
}

} // namespace Runa::Scene
