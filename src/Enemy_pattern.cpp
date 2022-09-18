#include "Enemy_pattern.h"

namespace Runa::Game::Enemy
{

//attacks
constexpr Action::Action_index OnlySlash[] = { Action::Action_index::Slash };
constexpr Action::Action_index OnlyBash[] = { Action::Action_index::Bash };
constexpr Action::Action_index OnlyThrow[] = { Action::Action_index::Throw };
constexpr Action::Action_index OnlyTripleSlash[] = { Action::Action_index::Triple_Slash };

constexpr Action::Action_index GuardSlash[] = {
    Action::Action_index::Guard,
    Action::Action_index::Slash
};
constexpr Action::Action_index ChargeConfusion[] = {
    Action::Action_index::Charge,
    Action::Action_index::Confusion
};
constexpr Action::Action_index ChargeBash[] = {
    Action::Action_index::Charge,
    Action::Action_index::Bash
};
constexpr Action::Action_index ChargeFire[] = {
    Action::Action_index::Charge,
    Action::Action_index::Fire_I
};
constexpr Action::Action_index ChargeIce[] = {
    Action::Action_index::Charge,
    Action::Action_index::Ice_I
};
constexpr Action::Action_index ChargeLightning[] = {
    Action::Action_index::Charge,
    Action::Action_index::Lightning_I
};

constexpr Action::Action_index Quicksand[] = {
    Action::Action_index::Quicksand,
    Action::Action_index::Throw,
    Action::Action_index::Throw
};
constexpr Action::Action_index FireIce[] = {
    Action::Action_index::Super_Charge,
    Action::Action_index::Fire_I,
    Action::Action_index::Ice_I
};

constexpr Action::Action_index Explosion[] = {
    Action::Action_index::Guard,
    Action::Action_index::Guard,
    Action::Action_index::Guard,
    Action::Action_index::Guard,
    Action::Action_index::Explosion
};

//weaken
constexpr Action::Action_index Confusion[] = {
    Action::Action_index::Weaken,
    Action::Action_index::Soften,
    Action::Action_index::Confusion
};

//self, support
constexpr Action::Action_index OnlyGuard[] = { Action::Action_index::Guard };
constexpr Action::Action_index OnlyHeal[] = { Action::Action_index::Heal_I };
constexpr Action::Action_index OnlyAreaHeal[] = { Action::Action_index::Area_Heal_I };

constexpr Action::Action_index ChargeAreaHeal[] = {
    Action::Action_index::Charge,
    Action::Action_index::Area_Heal_I
};

constexpr Action::Action_index Healer[] = {
    Action::Action_index::Super_Charge,
    Action::Action_index::Area_Heal_I,
    Action::Action_index::Area_Heal_I
};

//private
constexpr Action::Action_index Pawn_Black[] = {
    Action::Action_index::Guard,
    Action::Action_index::Poison,
    Action::Action_index::En_Passant,
    Action::Action_index::Guard,
    Action::Action_index::Promotion,
    Action::Action_index::Fire_I,
    Action::Action_index::Guard,
    Action::Action_index::Pierce,
    Action::Action_index::Fire_I,
    Action::Action_index::Guard,
    Action::Action_index::Pierce,
    Action::Action_index::Heal_I,
    Action::Action_index::Morale_Boost,
    Action::Action_index::Fire_II,
    Action::Action_index::Fire_II,
    Action::Action_index::Fire_II,
    Action::Action_index::Fire_III,
    Action::Action_index::Fire_III,
    Action::Action_index::Fire_III,
    Action::Action_index::Fire_III,
};
constexpr Action::Action_index Pawn_White[] = {
    Action::Action_index::Guard,
    Action::Action_index::Poison,
    Action::Action_index::En_Passant,
    Action::Action_index::Guard,
    Action::Action_index::Promotion,
    Action::Action_index::Ice_I,
    Action::Action_index::Guard,
    Action::Action_index::Jump,
    Action::Action_index::Ice_I,
    Action::Action_index::Guard,
    Action::Action_index::Jump,
    Action::Action_index::Heal_I,
    Action::Action_index::Protection,
    Action::Action_index::Ice_II,
    Action::Action_index::Ice_II,
    Action::Action_index::Ice_II,
    Action::Action_index::Ice_III,
    Action::Action_index::Ice_III,
    Action::Action_index::Ice_III,
    Action::Action_index::Ice_III,
};
constexpr Action::Action_index Knight_Black[] = {
    Action::Action_index::Pierce,
};
constexpr Action::Action_index Knight_White[] = {
    Action::Action_index::Jump,
};
constexpr Action::Action_index Bishop_Black[] = {
    Action::Action_index::Morale_Boost,
    Action::Action_index::Fire_I,
    Action::Action_index::Fire_I,
    Action::Action_index::Fire_I,
    Action::Action_index::Fire_I,
};
constexpr Action::Action_index Bishop_White[] = {
    Action::Action_index::Protection,
    Action::Action_index::Ice_I,
    Action::Action_index::Ice_I,
    Action::Action_index::Ice_I,
    Action::Action_index::Ice_I,
};
constexpr Action::Action_index Rook_Black[] = {
    Action::Action_index::Charger,
    Action::Action_index::Guard,
    Action::Action_index::Guard,
};
constexpr Action::Action_index Rook_White[] = {
    Action::Action_index::Castling,
    Action::Action_index::Guard,
    Action::Action_index::Guard,
};
constexpr Action::Action_index Queen_Black[] = {
    Action::Action_index::Fire_II,
};
constexpr Action::Action_index Queen_White[] = {
    Action::Action_index::Ice_II,
};
constexpr Action::Action_index King_Black[] = {
    Action::Action_index::Area_Heal_I,
    Action::Action_index::Guard,
    Action::Action_index::Slash
};
constexpr Action::Action_index King_White[] = {
    Action::Action_index::Bless,
    Action::Action_index::Guard,
    Action::Action_index::Slash
};

//boss
constexpr Action::Action_index Boss_1[] = {
    Action::Action_index::Guard,
    Action::Action_index::Defense_Up,
    Action::Action_index::Bash,
    Action::Action_index::Charge,
    Action::Action_index::Bash,
};
constexpr Action::Action_index Boss_2[] = {
    Action::Action_index::Throw,
    Action::Action_index::Attack_Up,
    Action::Action_index::Charge,
    Action::Action_index::Throw,
    Action::Action_index::Guard,
    Action::Action_index::Guard,
    Action::Action_index::Quicksand,
    Action::Action_index::Defense_Up,
};
constexpr Action::Action_index Boss_3[] = {
    Action::Action_index::Throw,
};

constexpr Enemy_pattern Enemy_pattern_data[] = {
    Enemy_pattern(1, OnlySlash), // Slash
    Enemy_pattern(1, OnlyBash), // Bash
    Enemy_pattern(1, OnlyThrow), // Throw
    Enemy_pattern(1, OnlyTripleSlash), // TripleSlash

    Enemy_pattern(2, GuardSlash), // Guard_Slash
    Enemy_pattern(2, ChargeBash), // Charge_Bash
    Enemy_pattern(2, ChargeConfusion), // Charge_Confusion
    Enemy_pattern(2, ChargeFire), // Charge_Fire
    Enemy_pattern(2, ChargeIce), // Charge_Ice
    Enemy_pattern(2, ChargeLightning), // Charge_Lightning

    Enemy_pattern(3, Quicksand), // Quicksand
    Enemy_pattern(3, FireIce), // FireIce

    Enemy_pattern(5, Explosion), // Explosion

    Enemy_pattern(3, Confusion), // Confusion

    Enemy_pattern(1, OnlyGuard), // Guard
    Enemy_pattern(1, OnlyHeal), // Heal
    Enemy_pattern(1, OnlyAreaHeal), // AreaHeal

    Enemy_pattern(2, ChargeAreaHeal), // Charge_AreaHeal

    Enemy_pattern(3, Healer), // Healer

    Enemy_pattern(20, Pawn_Black), // Pawn_Black
    Enemy_pattern(20, Pawn_White), // Pawn_White
    Enemy_pattern(1, Knight_Black), // Knight_Black
    Enemy_pattern(1, Knight_White), // Knight_White
    Enemy_pattern(5, Bishop_Black), // Bishop_Black
    Enemy_pattern(5, Bishop_White), // Bishop_White
    Enemy_pattern(3, Rook_Black), // Rook_Black
    Enemy_pattern(3, Rook_White), // Rook_White
    Enemy_pattern(1, Queen_Black), // Queen_Black
    Enemy_pattern(1, Queen_White), // Queen_White
    Enemy_pattern(3, King_Black), // King_Black
    Enemy_pattern(3, King_White), // King_White

    Enemy_pattern(5, Boss_1), // Boss_1
    Enemy_pattern(8, Boss_2), // Boss_2
    Enemy_pattern(1, Boss_3), // Boss_3
};

const Enemy_pattern& Get_enemy_pattern_data(Pattern_index index)
{
    return Enemy_pattern_data[(int)index];
}

} // namespace Runa::Game::Enemy
