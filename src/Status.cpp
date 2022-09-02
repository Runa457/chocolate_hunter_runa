#include "Status.h"

#include "Stats_data.h"
#include "bn_string_view.h"

namespace Runa
{

constexpr int LIFESPAN = 30;
constexpr int MULTIPLIER_DEFAULT = 200;

struct Game_data
{
    constexpr static const char* SAVE_CHECK = "RUNA_0902";

    char CHECK[10] = {};
    short level = 0;
    int hp = 0;
    int mp = 0;
    int exp = 0;
    short left_turns = 0;
    short Weapon_level = 0;
    short Armor_level = 0;
    short stratum = 0;
    int chocolate = 0;
    int multiplier = 0;
    int total_turn = 0;

    bool Read()
    {
        bn::sram::read(*this);
        return bn::string_view(CHECK) == SAVE_CHECK;
    }
    void Write()
    {
        bn::istring_base label_istring(CHECK);
        bn::ostringstream label_stream(label_istring);
        label_stream.append(SAVE_CHECK);
        bn::sram::write(*this);
    }
};

struct Global_data
{
    constexpr static const char* SAVE_CHECK = "RUNA_0902";

    char CHECK[10] = {};
    int Max_level = 0;
    int Max_turn = 0;
    int Enemy_codex[NUM_ENEMY] = {0};

    bool Read()
    {
        bn::sram::read_offset(*this, sizeof(Game_data));
        return bn::string_view(CHECK) == SAVE_CHECK;
    }
    void Write()
    {
        bn::istring_base label_istring(CHECK);
        bn::ostringstream label_stream(label_istring);
        label_stream.append(SAVE_CHECK);
        bn::sram::write_offset(*this, sizeof(Game_data));
    }
};

Status::Status()
{
    Global_data _global_data;
    _global_data.Read();
    Max_level = _global_data.Max_level;
    Max_turn = _global_data.Max_turn;
    for (int i = 0; i < NUM_ENEMY; i++) { Enemy_codex[i] = _global_data.Enemy_codex[i]; }

    if (!Read())
    {
        Game_init();
        Write();
    }
}
Status::~Status() {}

void Status::Game_init()
{
    Level = 0;
    hp = Get_hp_data(0);
    mp = Get_mp_data(0);
    exp = 0;
    left_turns = LIFESPAN;
    Weapon_level = 0;
    Armor_level = 0;
    stratum = 1;
    chocolate = 0;
    choco_multiplier = MULTIPLIER_DEFAULT;
    total_turn = 0;

    _value_changed = false;

    _stats_update();
}
void Status::Reset()
{
    Game_init();

    Max_level = 0;
    for (int i = 0; i < NUM_ENEMY; i++) { Enemy_codex[i] = 0; }

    Write();
}
void Status::Write()
{
    WriteGame();
    WriteGlobal();
}
void Status::WriteGame()
{
    Game_data _game_data;
    _game_data.level = Level;
    _game_data.hp = hp;
    _game_data.mp = mp;
    _game_data.exp = exp;
    _game_data.left_turns = left_turns;
    _game_data.Weapon_level = Weapon_level;
    _game_data.Armor_level = Armor_level;
    _game_data.stratum = stratum;
    _game_data.chocolate = chocolate;
    _game_data.multiplier = choco_multiplier;
    _game_data.total_turn = total_turn;
    _game_data.Write();
}
void Status::WriteGlobal()
{
    Global_data _global_data;
    _global_data.Max_level = Max_level;
    _global_data.Max_turn = Max_turn;
    for (int i = 0; i < NUM_ENEMY; i++) { _global_data.Enemy_codex[i] = Enemy_codex[i]; }
    _global_data.Write();
}
bool Status::Read()
{
    Game_data _read_data;
    if (_read_data.Read())
    {
        Level = _read_data.level;
        hp = _read_data.hp;
        mp = _read_data.mp;
        exp = _read_data.exp;
        left_turns = _read_data.left_turns;
        Weapon_level = _read_data.Weapon_level;
        Armor_level = _read_data.Armor_level;
        stratum = _read_data.stratum;
        chocolate = _read_data.chocolate;
        choco_multiplier = _read_data.multiplier;
        total_turn = _read_data.total_turn;

        _stats_update();
        return true;
    }
    else { return false; }
}

short Status::Get_level() { return Level; }
int Status::Get_hp() { return hp; }
int Status::Get_mp() { return mp; }
int Status::Get_exp() { return exp; }
short Status::Get_turns() { return left_turns; }
short Status::Get_weapon() { return Weapon_level; }
short Status::Get_armor() { return Armor_level; }
short Status::Get_stratum() { return stratum; }
short Status::Get_choco() { return chocolate; }
short Status::Get_multiplier() { return choco_multiplier; }
int Status::Get_Max_level() { return Max_level; }
int Status::Get_Max_turn() { return Max_turn; }
int Status::Get_Enemy_codex(int index)
{
    return Enemy_codex[index];
}

void Status::Defeat_enemy(int index)
{
    ++Enemy_codex[index];
}

bool Status::Hp_change(short increment)
{
    _value_changed = true;
    hp += increment;
    if (hp > Get_hp_data(Level)) { hp = Get_hp_data(Level); }
    else if (hp <= 0) { hp = 0; return true; }
    return false;
}
bool Status::Mp_change(short increment)
{
    _value_changed = true;
    if (mp + increment < 0) { return false; }
    mp += increment;
    if (mp > Get_mp_data(Level)) { mp = Get_mp_data(Level); }
    return true;
}
void Status::Exp_earn(int increment)
{
    _value_changed = true;
    exp += increment;
    while (exp >= Get_exp_data(Level))
    {
        exp -= Get_exp_data(Level);
        ++Level;
        _stats_update();
    }
}
void Status::Choco_earn(int increment)
{
    _value_changed = true;
    chocolate += increment;
}
void Status::Life_regain()
{
    _value_changed = true;
    left_turns = LIFESPAN;
}
void Status::Weapon_upgrade()
{
    ++Weapon_level;
    _stats_update();
}
void Status::Armor_upgrade()
{
    ++Armor_level;
    _stats_update();
}

void Status::Next_stratum()
{
    _value_changed = true;
    ++stratum;
    choco_multiplier = MULTIPLIER_DEFAULT;
}
void Status::Lower_multiplier()
{
    _value_changed = true;
    choco_multiplier -= 5;
    if (choco_multiplier < 0) { choco_multiplier = 0; }
}

bool Status::Value_changed()
{
    if (_value_changed) { _value_changed = false; return true; }
    else { return false; }
}

bool Status::turn_end()
{
    ++total_turn;
    _value_changed = true;
    return --left_turns <= 0;
}

void Status::Game_over()
{
    Max_level = Level;
    Max_turn = total_turn;
    WriteGlobal();
}

void Status::_stats_update()
{
    _stats = Game::ActorStats(Get_str_data(Level), Get_weapon_data(Weapon_level),
                              Get_def_data(Level), Get_armor_data(Armor_level),
                              Get_int_data(Level), Get_spd_data(Level));
}

} // namespace Runa
