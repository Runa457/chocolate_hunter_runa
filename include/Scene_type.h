#ifndef SCENE_TYPE_H
#define SCENE_TYPE_H

namespace Runa::Scene
{

enum class Scene_Type : char
{
    Logo,
    Title,
    Introduction,
    Options,
    Main_game,
    Credits,
    Enemy_list,
    Magic_list
};

} // namespace Runa::Scene

#endif // SCENE_TYPE_H
