#include "Enemy_pattern.h"

namespace Runa::Game::Enemy
{

constexpr Action::Action_index pattern1[] = { Action::Action_index::Bash };
constexpr Action::Action_index pattern2[] = { Action::Action_index::Guard };
constexpr Action::Action_index pattern3[] = {
    Action::Action_index::Bash,
    Action::Action_index::Guard
};
constexpr Action::Action_index boss_1[] = {
    Action::Action_index::Bash,
    Action::Action_index::Guard
};

constexpr Enemy_pattern Enemy_pattern_data[] = {
    Enemy_pattern(1, pattern1), // Bash
    Enemy_pattern(1, pattern2), // Guard
    Enemy_pattern(2, pattern3), // Bash_Guard
    Enemy_pattern(2, boss_1), // Boss_1
};

const Enemy_pattern& Get_enemy_pattern_data(Pattern_index index)
{
    return Enemy_pattern_data[index];
}

} // namespace Runa::Game::Enemy
