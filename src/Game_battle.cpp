#include "Game_battle.h"

namespace Runa::Game
{

Battle::Battle(bn::unique_ptr<Battle_Sequence>& battle_sq,
               bn::sprite_text_generator& text_generator) :
    _text_generator(text_generator)
{
}
Battle::~Battle() {}

bn::optional<Game_Type> Battle::Update()
{
    return bn::nullopt;
}

} // namespace Runa::Scene
