#ifndef GAME_H
#define GAME_H

#include "Game_type.h"
#include "Status.h"
#include "Effect_transition.h"

#include "bn_optional.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "bn_sound_items.h"

namespace Runa::Game
{

class Game_Root
{
public:
    Game_Root() {}
    virtual ~Game_Root() = default;
    virtual bn::optional<Game_Type> Update();

protected:

};

} // namespace Runa::Game

#endif // GAME_H
