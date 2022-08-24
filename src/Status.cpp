#include "Status.h"

#include "Stats_data.h"
#include "bn_string_view.h"

namespace Runa
{

struct Save_data
{
    constexpr static const char* SAVE_CHECK = "RUNA_0821";

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

Status::Status()
{
    if (!Read())
    {
        Init();
        Write();
    }
    _stats_update();
}
Status::~Status() {}

void Status::Init()
{
    Level = 0;
    hp = Get_hp_data(0);
    mp = Get_mp_data(0);
    exp = 0;
    left_turns = 100;
    Weapon_level = 0;
    Armor_level = 0;
    stratum = 1;
    chocolate = 0;
    choco_multiplier = 200;

    _value_changed = false;
}
void Status::Write()
{
    Save_data _save_data;
    _save_data.level = Level;
    _save_data.hp = hp;
    _save_data.mp = mp;
    _save_data.exp = exp;
    _save_data.left_turns = left_turns;
    _save_data.Weapon_level = Weapon_level;
    _save_data.Armor_level = Armor_level;
    _save_data.stratum = stratum;
    _save_data.chocolate = chocolate;
    _save_data.multiplier = choco_multiplier;
    _save_data.Write();
}
bool Status::Read()
{
    Save_data _read_data;
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
    left_turns = 100;
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
    choco_multiplier = 200;
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
    _value_changed = true;
    return --left_turns <= 0;
}

void Status::_stats_update()
{
    _stats = Game::ActorStats(Get_str_data(Level), Get_weapon_data(Weapon_level),
                              Get_def_data(Level), Get_armor_data(Armor_level),
                              Get_int_data(Level), Game::Status_effect::None);
}

} // namespace Runa
