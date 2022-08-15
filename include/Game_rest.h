#ifndef GAME_REST_H
#define GAME_REST_H

#include "Game.h"

namespace Runa::Game
{

class Rest final : public Game_Root
{
public:
    Rest(bn::sprite_text_generator& text_generator,
         Status& status);
    ~Rest();
    bn::optional<Game_Type> Update();

private:
    enum Menu : char
    {
        Regain_life = 0,
        Magic_potion = 1,
        Upgrade_sword = 2,
        Upgrade_armor = 3
    };

    void Print_text();
    void Press_left_right();
    void Menu_selected();
    void Cursor_update(int move_direction);

    Status& _status;

    bn::sprite_text_generator& _text_generator;
    bn::vector<bn::sprite_ptr, 20> _text_sprite;
    bn::vector<bn::sprite_ptr, 5> _save_text;
    bn::vector<bn::sprite_ptr, 4> _icon_sprite;
    bn::sprite_ptr _cursor;

    Menu _current_menu;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 10;

};

} // namespace Runa::Game

#endif // GAME_REST_H
