#ifndef GAME_TYPE_H
#define GAME_TYPE_H

namespace Runa::Game
{

enum class Game_Type : char
{
    Battle,
    Result,
    Choice,
    Gameover,
    Rest,
    Exit
};

} // namespace Runa::Game

#endif // GAME_TYPE_H
