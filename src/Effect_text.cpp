#include "Effect_text.h"

#include "bn_sprite_ptr.h"

namespace Runa::Effect
{

void Print_text(bn::sprite_text_generator& _text_generator,
                bool _is_clear,
                Alignment _alignment,
                int x, int y, int spacing,
                bn::ivector<bn::sprite_ptr>& _text_sprite,
                int length, ...)
{
    if (_is_clear) { _text_sprite.clear(); }

    switch (_alignment)
    {
    case Alignment::Left:
        _text_generator.set_left_alignment();
        break;
    case Alignment::Center:
        _text_generator.set_center_alignment();
        break;
    case Alignment::Right:
        _text_generator.set_right_alignment();
        break;
    default: BN_ERROR(); break;
    }
    va_list _text;
    va_start(_text, length);

    for (int i = 0; i < length; i++)
    {
        bn::string_view line = va_arg(_text, const char*);
        _text_generator.generate(x, y + i*spacing, line, _text_sprite);
    }
    va_end(_text);
}

void Print_text(bn::sprite_text_generator& _text_generator,
                bool _is_clear,
                Alignment _alignment,
                int x, int y, int spacing,
                bn::ivector<bn::sprite_ptr>& _text_sprite,
                bn::span<const bn::string_view> _text)
{
    if (_is_clear) { _text_sprite.clear(); }

    switch (_alignment)
    {
    case Alignment::Left:
        _text_generator.set_left_alignment();
        break;
    case Alignment::Center:
        _text_generator.set_center_alignment();
        break;
    case Alignment::Right:
        _text_generator.set_right_alignment();
        break;
    default: BN_ERROR(); break;
    }
    for (int i = 0; i < _text.size(); i++)
    {
        _text_generator.generate(x, y + i*spacing, _text[i], _text_sprite);
    }
}

} // namespace Runa::Effect
