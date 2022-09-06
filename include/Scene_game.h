#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "Scene.h"
#include "Game.h"
#include "Status.h"
#include "Game_type.h"
#include "Battle_sequence.h"
#include "Effect_transition.h"

#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"

namespace Runa::Scene
{

class Game : public Scene_Root
{
public:
    Game(bn::sprite_text_generator& text_generator,
         bn::random& random_generator,
         Status& status);
    ~Game();
    bn::optional<Scene_Type> Update();

private:
    void Print_text();

    bn::random& _random;
    Status& _status;
    bn::regular_bg_ptr _bg_interface;
    bn::regular_bg_ptr _bg_stratum;
    bn::sprite_ptr _player_sprite;

    bn::unique_ptr<Runa::Game::Game_Root> _subscene;
    bn::optional<Runa::Game::Game_Type> _game_mode;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 60> _status_text;
    bn::vector<bn::sprite_ptr, 2> _choco_icon;

    bn::unique_ptr<Runa::Game::Battle_Sequence> _battle_sq;

    Effect::Transition _scene_begin;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 10;

    int _current_stratum = 0;
};

} // namespace Runa::Scene


#endif // SCENE_GAME_H
