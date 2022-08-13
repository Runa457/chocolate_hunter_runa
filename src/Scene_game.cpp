#include "Scene_game.h"
#include "Game_battle.h"
#include "Game_choice.h"

#include "bn_format.h"

namespace Runa::Scene
{

Game::Game(Status& status, bn::sprite_text_generator& text_generator) :
    _status(status),
    _text_generator(text_generator),
    _subscene(new Runa::Game::Choice(_battle_sq, text_generator))
{
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));
    //_text_generator.generate(0, 0, bn::format<5>("{}", _status.Level), _status_text);
}
Game::~Game() {}

bn::optional<Scene_Type> Game::Update()
{
    if (_subscene) { _game_mode = _subscene->Update(); }
    if (_game_mode)
    {
        switch (*_game_mode)
        {
        case Runa::Game::Game_Type::Battle:
            _subscene.reset(new Runa::Game::Battle(_battle_sq, _text_generator));
            break;
        case Runa::Game::Game_Type::Result:
            _subscene.reset();
            break;
        case Runa::Game::Game_Type::Rest:
            _subscene.reset();
            break;
        case Runa::Game::Game_Type::Choice:
            _subscene.reset(new Runa::Game::Choice(_battle_sq, _text_generator));
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

} // namespace Runa::Scene
