#ifndef SCENE_ENEMYLIST_H
#define SCENE_ENEMYLIST_H

#include "Enemy_data.h"
#include "Scene.h"
#include "Status.h"
#include "Effect_transition.h"

#include "bn_sprite_ptr.h"

namespace Runa::Scene
{

class Enemy_list final: public Scene_Root
{
public:
    Enemy_list(bn::sprite_text_generator& text_generator, Status& status);
    ~Enemy_list();
    bn::optional<Scene_Type> Update();

private:
    bn::sprite_text_generator& _text_generator;
    Status& _status;

    bn::vector<bn::sprite_ptr, 70> _description_text;
    bn::vector<bn::sprite_ptr, 5> _page_text;
    bn::sprite_ptr _enemy_graphic;

    Effect::Transition _scene_start;
    Effect::Transition _scene_end;
    static constexpr int TRANSITION_FRAMES = 15;

    int _current_page = 0;
    const Runa::Game::Enemy::Enemy_data* _enemy_data = nullptr;
    /**
     * @brief Check if enemy[current index] is defeated ever and print codex
     */
    void Print_enemy_codex();
};
} // namespace Runa::Scene

#endif // SCENE_ENEMYLIST_H
