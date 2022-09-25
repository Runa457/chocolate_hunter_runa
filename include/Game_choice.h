#ifndef GAME_CHOICE_H
#define GAME_CHOICE_H

#include "Game.h"
#include "Battle_sequence.h"

namespace Runa::Game
{

class Choice final : public Game_Root
{
public:
    Choice(bn::sprite_text_generator& text_generator,
           bn::random& random_generator,
           Status& status,
           bn::unique_ptr<Battle_Sequence>& battle_sq);
    ~Choice();
    bn::optional<Game_Type> Update();

private:
    enum Menu : char
    {
        Left = 0,
        Center = 1,
        Right = 2
    };

    void Print_text();
    void Press_left_right();
    void Cursor_update(int move_direction);

    bn::random& _random;
    Status& _status;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 20> _text_sprite;
    bn::sprite_ptr _cursor;

    Menu _current_menu;
    bn::array<bn::unique_ptr<Battle_Sequence>, 3> _sequence_option;
    bn::unique_ptr<Battle_Sequence>& _next_sequence;
    bn::optional<Game_Type> _next_scene;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 10;

};

} // namespace Runa::Game

#endif // GAME_CHOICE_H
