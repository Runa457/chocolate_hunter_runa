#include "Status.h"

#include "bn_string_view.h"

namespace Runa
{

struct Save_data
{
    constexpr static const char* SAVE_CHECK = "RUNA_0813";

    char CHECK[10] = {};
    int level = 0;
    int hp = 0, maxhp = 0;
    int mp = 0, maxmp = 0;
    int exp = 0;
    int left_turns = 0;

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
        // read data
    }
    else { Init(); }
}
Status::~Status() {}

void Status::Init()
{
    Level = 0;
}
void Status::Write()
{
    Save_data _save_data;
    _save_data.level = Level;
    // save data
    _save_data.Write();
}

int Status::Get_level()
{
    return Level;
}

} // namespace Runa
