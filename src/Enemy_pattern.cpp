#include "Enemy_pattern.h"

namespace Runa::Game::Enemy
{

constexpr Action::Action_index OnlyGuard[] = { Action::Action_index::Guard };
constexpr Action::Action_index OnlyHeal[] = { Action::Action_index::Heal_I };

constexpr Action::Action_index OnlySlash[] = { Action::Action_index::Slash };
constexpr Action::Action_index OnlyBash[] = { Action::Action_index::Bash };
constexpr Action::Action_index OnlyThrow[] = { Action::Action_index::Throw };

constexpr Action::Action_index OnlyTripleSlash[] = { Action::Action_index::Triple_Slash };

constexpr Action::Action_index OnlyAreaHeal[] = { Action::Action_index::Area_Heal_I };

constexpr Action::Action_index GuardSlash[] = {
    Action::Action_index::Guard,
    Action::Action_index::Slash
};
constexpr Action::Action_index GuardConfusion[] = {
    Action::Action_index::Charge,
    Action::Action_index::Confusion
};
constexpr Action::Action_index ChargeBash[] = {
    Action::Action_index::Charge,
    Action::Action_index::Bash
};
constexpr Action::Action_index ChargeAreaHeal[] = {
    Action::Action_index::Charge,
    Action::Action_index::Area_Heal_I
};

constexpr Action::Action_index Quicksand[] = {
    Action::Action_index::Quicksand,
    Action::Action_index::Throw,
    Action::Action_index::Throw
};

constexpr Action::Action_index Explosion[] = {
    Action::Action_index::Guard,
    Action::Action_index::Guard,
    Action::Action_index::Guard,
    Action::Action_index::Guard,
    Action::Action_index::Explosion
};

constexpr Action::Action_index Boss_1[] = {
    Action::Action_index::Guard,
    Action::Action_index::Defence_Up,
    Action::Action_index::Bash,
    Action::Action_index::Charge,
    Action::Action_index::Bash,
};
constexpr Action::Action_index Boss_2[] = {
    Action::Action_index::Guard,
    Action::Action_index::Defence_Up,
    Action::Action_index::Bash,
    Action::Action_index::Charge,
    Action::Action_index::Bash,
};

constexpr Enemy_pattern Enemy_pattern_data[] = {
    Enemy_pattern(1, OnlyGuard), // Guard
    Enemy_pattern(1, OnlyHeal), // Heal
    Enemy_pattern(1, OnlySlash), // Slash
    Enemy_pattern(1, OnlyBash), // Bash
    Enemy_pattern(1, OnlyThrow), // Throw
    Enemy_pattern(1, OnlyTripleSlash), // TripleSlash
    Enemy_pattern(1, OnlyAreaHeal), // AreaHeal

    Enemy_pattern(2, GuardSlash), // Guard_Slash
    Enemy_pattern(2, GuardConfusion), // Confusion
    Enemy_pattern(2, ChargeBash), // Charge_Bash
    Enemy_pattern(2, ChargeAreaHeal), // Charge_AreaHeal

    Enemy_pattern(3, Quicksand), // Quicksand

    Enemy_pattern(5, Explosion), // Explosion

    Enemy_pattern(5, Boss_1), // Boss_1
    Enemy_pattern(5, Boss_2), // Boss_2
};

const Enemy_pattern& Get_enemy_pattern_data(Pattern_index index)
{
    return Enemy_pattern_data[(int)index];
}

} // namespace Runa::Game::Enemy
