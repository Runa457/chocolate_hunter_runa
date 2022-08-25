#ifndef ENEMY_H
#define ENEMY_H

#include "Enemy_data.h"
#include "Game_battle_actorstats.h"

#include "bn_vector.h"

namespace Runa::Game::Enemy
{

class Enemy
{
public:
    Enemy(int index, short level);
    ~Enemy();

    void Init();

    const bn::string_view& Get_name();
    const short& Get_level();
    int Get_hp();
    int Get_exp();
    short Get_choco();

    /**
     * @brief Change hp and check if hp is below 0
     * @param Amount of change of hp.
     * > 0: heal
     * < 0: damage
     * @return Returns true if hp is 0 or low (dead).
     */
    bool Hp_change(short increment);

    /**
     * @brief Same as Hp_change(0)
     * @return True if hp is 0 or low.
     */
    bool Is_dead();

    /**
     * @brief Create sprite of enemy object.
     * @param X coordinate of sprite.
     * @param Y coordinate of sprite.
     * @param Pointer of sprite object.
     */
    void Sprite_create(short x, short y, bn::ivector<bn::sprite_ptr>& sprite);

    ActorStats _stats;
private:
    Enemy_data _base_data;
    short level;
    int hp, maxhp;

};

} // namespace Runa::Game::Enemy

#endif // ENEMY_H
