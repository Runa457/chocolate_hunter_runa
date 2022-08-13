
@{{BLOCK(cursor_0_bn_gfx)

@=======================================================================
@
@	cursor_0_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2022-08-09, 21:34:32
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.17
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global cursor_0_bn_gfxTiles		@ 128 unsigned chars
	.hidden cursor_0_bn_gfxTiles
cursor_0_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000211,0x00002110,0x00021100,0x00211000
	.word 0x11110000,0x22220000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x02111111,0x02211222,0x00221100,0x00022110,0x00002211,0x00000222,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global cursor_0_bn_gfxPal		@ 32 unsigned chars
	.hidden cursor_0_bn_gfxPal
cursor_0_bn_gfxPal:
	.hword 0x0000,0x7FFF,0x0000,0x001F,0x03FF,0x03E0,0x7FE0,0x7C00
	.hword 0x7C1F,0x3DEF,0x01FF,0x3646,0x15A9,0x112A,0x1CE6,0x38E7

@}}BLOCK(cursor_0_bn_gfx)
