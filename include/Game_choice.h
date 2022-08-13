#ifndef GAME_CHOICE_H
#define GAME_CHOICE_H

#include "Game.h"
#include "Battle_sequence.h"

namespace Runa::Game
{

class Choice final : public Game_Root
{
public:
    Choice(Status& status, bn::unique_ptr<Battle_Sequence>& battle_sq,
           bn::sprite_text_generator& text_generator);
    ~Choice();
    bn::optional<Game_Type> Update();

private:
    void PrintText();
    void PressLeftRight();

    bn::array<bn::unique_ptr<Battle_Sequence>, 3> _next_sequence;
    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 20> _text_sprite;

};

} // namespace Runa::Game

#endif // GAME_CHOICE_H
