#ifndef EFFECT_TEXT_H
#define EFFECT_TEXT_H

#include "bn_sprite_text_generator.h"

#include <cstdarg>

namespace Runa::Effect
{

enum class Alignment
{
    Left, Center, Right
};

void Print_text(bn::sprite_text_generator& _text_generator,
                bool _is_clear,
                Alignment _alignment,
                int x, int y, int spacing,
                bn::ivector<bn::sprite_ptr>& _text_sprite,
                int length, ...);

void Print_text(bn::sprite_text_generator& _text_generator,
                bool _is_clear,
                Alignment _alignment,
                int x, int y, int spacing,
                bn::ivector<bn::sprite_ptr>& _text_sprite,
                bn::span<const bn::string_view> _text);

} // namespace Runa::Effect

#endif // EFFECT_TEXT_H
