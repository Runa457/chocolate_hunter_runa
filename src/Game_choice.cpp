#include "Game_choice.h"

namespace Runa::Game
{

Choice::Choice(Status& status, bn::unique_ptr<Battle_Sequence>& battle_sq,
               bn::sprite_text_generator& text_generator) :
    _text_generator(text_generator)
{
    if (!battle_sq)
    {
        battle_sq.reset(new Battle_Sequence(status.Get_level(), false));
    }
}
Choice::~Choice() {}

bn::optional<Game_Type> Choice::Update()
{
    return bn::nullopt;
}

} // namespace Runa::Scene
