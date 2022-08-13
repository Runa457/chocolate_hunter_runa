#ifndef BN_REGULAR_BG_ITEMS_LSH_GAMES_LOGO_H
#define BN_REGULAR_BG_ITEMS_LSH_GAMES_LOGO_H

#include "bn_regular_bg_item.h"

//{{BLOCK(lsh_games_logo_bn_gfx)

//======================================================================
//
//	lsh_games_logo_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 49 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 1568 + 2048 = 3648
//
//	Time-stamp: 2022-08-09, 21:34:32
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.17
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LSH_GAMES_LOGO_BN_GFX_H
#define GRIT_LSH_GAMES_LOGO_BN_GFX_H

#define lsh_games_logo_bn_gfxTilesLen 1568
extern const bn::tile lsh_games_logo_bn_gfxTiles[49];

#define lsh_games_logo_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell lsh_games_logo_bn_gfxMap[1024];

#define lsh_games_logo_bn_gfxPalLen 32
extern const bn::color lsh_games_logo_bn_gfxPal[16];

#endif // GRIT_LSH_GAMES_LOGO_BN_GFX_H

//}}BLOCK(lsh_games_logo_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item lsh_games_logo(
            regular_bg_tiles_item(span<const tile>(lsh_games_logo_bn_gfxTiles, 49), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(lsh_games_logo_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(lsh_games_logo_bn_gfxMap[0], size(32, 32), compression_type::NONE));
}

#endif

