#ifndef ENEMY_H
#define ENEMY_H

#include "Enemy_data.h"

#include "bn_vector.h"

namespace Runa::Game::Enemy
{

class Enemy
{
public:
    Enemy(int index, short level);
    ~Enemy();

    void Init();

    int Get_exp();
    int Get_choco();

    /**
     * @brief Change hp and check if hp is below 0
     * @param Amount of change of hp.
     * > 0: heal
     * < 0: damage
     * @return Returns true if hp is below 0 (dead)
     */
    bool Hp_change(short increment);

    /**
     * @brief Create sprite of enemy object.
     * @param X coordinate of sprite.
     * @param Y coordinate of sprite.
     * @param Pointer of sprite object.
     */
    void Sprite_create(short x, short y, bn::vector<bn::sprite_ptr, 3>& sprite);

private:
    Enemy_data _base_data;
    short level;
    short hp, maxhp;
    short atk, def, spd;

};

} // namespace Runa::Game::Enemy

#endif // ENEMY_H
