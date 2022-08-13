#ifndef GAME_BATTLE_H
#define GAME_BATTLE_H

#include "Game.h"
#include "Battle_sequence.h"

namespace Runa::Game
{

class Battle final : public Game_Root
{
public:
    Battle(bn::unique_ptr<Battle_Sequence>& battle_sq,
           bn::sprite_text_generator& text_generator);
    ~Battle();
    bn::optional<Game_Type> Update();

private:
    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 20> _battle_text;
    bn::vector<bn::sprite_ptr, 5> _damage_text;

};

} // namespace Runa::Game

#endif // GAME_BATTLE_H
