#include "Status.h"

#include "Stats_data.h"
#include "bn_string_view.h"

namespace Runa
{

struct Save_data
{
    constexpr static const char* SAVE_CHECK = "RUNA_0814";

    char CHECK[10] = {};
    short level = 0;
    int hp = 0;
    int mp = 0;
    int exp = 0;
    short left_turns = 0;
    short Weapon_level = 0;
    short Armor_level = 0;
    short stratum = 0;

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
    }
    else { Init(); }
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
    _save_data.Write();
}

short Status::Get_level() { return Level; }
int Status::Get_hp() { return hp; }
int Status::Get_mp() { return mp; }
int Status::Get_exp() { return exp; }
short Status::Get_turns() { return left_turns; }

bool Status::Value_changed() { return _value_changed; }

bool Status::turn_end()
{
    return --left_turns <= 0;
}

} // namespace Runa
