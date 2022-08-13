#ifndef BN_SPRITE_ITEMS_CURSOR_0_H
#define BN_SPRITE_ITEMS_CURSOR_0_H

#include "bn_sprite_item.h"

//{{BLOCK(cursor_0_bn_gfx)

//======================================================================
//
//	cursor_0_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles not compressed
//	Total size: 32 + 128 = 160
//
//	Time-stamp: 2022-08-09, 21:34:32
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.17
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CURSOR_0_BN_GFX_H
#define GRIT_CURSOR_0_BN_GFX_H

#define cursor_0_bn_gfxTilesLen 128
extern const bn::tile cursor_0_bn_gfxTiles[4];

#define cursor_0_bn_gfxPalLen 32
extern const bn::color cursor_0_bn_gfxPal[16];

#endif // GRIT_CURSOR_0_BN_GFX_H

//}}BLOCK(cursor_0_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item cursor_0(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(cursor_0_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(cursor_0_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

