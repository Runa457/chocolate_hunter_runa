#ifndef ENEMY_H
#define ENEMY_H

#include "Enemy_data.h"

#include "bn_vector.h"

namespace Runa::Game::Enemy
{

enum class Status_effect : char
{
    None,
    Attack_up,
    Attack_down,
    Defence_up,
    Defence_down,
    Speed_up,
    Speed_down,
};

class Enemy
{
public:
    Enemy(int index, short level);
    ~Enemy();

    void Init();

    const bn::string_view& Get_name();
    const short& Get_level();
    int Get_hp();
    const short& Get_atk();
    const short& Get_def();
    const short& Get_spd();
    int Get_exp();
    short Get_choco();
    Status_effect Get_status();

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
    void Sprite_create(short x, short y, bn::vector<bn::sprite_ptr, 3>& sprite);

private:
    Enemy_data _base_data;
    short level;
    int hp, maxhp;
    short atk, def, spd;
    Status_effect _status_effect;

};

} // namespace Runa::Game::Enemy

#endif // ENEMY_H
