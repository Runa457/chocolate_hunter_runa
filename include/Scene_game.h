#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "Scene.h"
#include "Game.h"
#include "Status.h"
#include "Game_type.h"
#include "Battle_sequence.h"
#include "Effect_transition.h"

#include "bn_sprite_ptr.h"

namespace Runa::Scene
{

class Game : public Scene_Root
{
public:
    Game(Status& status, bn::sprite_text_generator& text_generator);
    ~Game();
    bn::optional<Scene_Type> Update();

private:
    bn::unique_ptr<Runa::Game::Game_Root> _subscene;
    bn::optional<Runa::Game::Game_Type> _game_mode;
    Status& _status;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 5> _status_text;

    bn::unique_ptr<Runa::Game::Battle_Sequence> _battle_sq;
};

} // namespace Runa::Scene


#endif // SCENE_GAME_H