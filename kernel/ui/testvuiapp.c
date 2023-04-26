#include <kernel.h>
#include <vui/vui.h>
#include <vui/testapp.h>

uint32_t rgb_array[12][4] = { 
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 },
	{ 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00000000 }
};

// 'left', 29x24px
const unsigned long left[696] = {
	0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 
	0x00636363, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 
	0x006f6f6f, 0x00e5e5e5, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00e5e5e5, 0x00cfcfcf, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d0d0d0, 0x00dcdcdc, 0x00d4d4d4, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00636363, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cacaca, 0x00cccccc, 0x00c3c3c3, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00393939, 0x002b2b2b, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00c5c5c5, 0x00a3a3a3, 0x00a1a1a1, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00cfcfcf, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d5d5d5, 0x00ececec, 0x00dddddd, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00d3d3d3, 0x00ababab, 0x00aeaeae, 0x00b2b2b2, 0x00b6b6b6, 0x00bbbbbb, 0x00bfbfbf, 0x00c3c3c3, 0x00acacac, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00bfbfbf, 0x00999999, 0x00999999, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00d6d6d6, 0x00afafaf, 0x00b3b3b3, 0x00b7b7b7, 0x00bbbbbb, 0x00bebebe, 0x00c3c3c3, 0x00c7c7c7, 0x00afafaf, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d5d5d5, 0x00e1e1e1, 0x00d5d5d5, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00d8d8d8, 0x00b2b2b2, 0x00b7b7b7, 0x00bbbbbb, 0x00bebebe, 0x00c3c3c3, 0x00c7c7c7, 0x00cbcbcb, 0x00b1b1b1, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00c4c4c4, 0x00b8b8b8, 0x00b3b3b3, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00d9d9d9, 0x00b7b7b7, 0x00bbbbbb, 0x00bfbfbf, 0x00c3c3c3, 0x00c7c7c7, 0x00cbcbcb, 0x00cfcfcf, 0x00b4b4b4, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cacaca, 0x00c2c2c2, 0x00bbbbbb, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00dbdbdb, 0x00bbbbbb, 0x00bfbfbf, 0x00c3c3c3, 0x00c7c7c7, 0x00cbcbcb, 0x00cfcfcf, 0x00d4d4d4, 0x00b6b6b6, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cacaca, 0x00cccccc, 0x00c3c3c3, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00dddddd, 0x00bfbfbf, 0x00c3c3c3, 0x00c8c8c8, 0x00cbcbcb, 0x00cfcfcf, 0x00d4d4d4, 0x00d8d8d8, 0x00b8b8b8, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00c5c5c5, 0x00a3a3a3, 0x00a1a1a1, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00e0e0e0, 0x00c3c3c3, 0x00c7c7c7, 0x00cbcbcb, 0x00cfcfcf, 0x00d4d4d4, 0x00d8d8d8, 0x00dcdcdc, 0x00bcbcbc, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d5d5d5, 0x00ececec, 0x00dddddd, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00c9c9c9, 0x00e2e2e2, 0x00c7c7c7, 0x00cccccc, 0x00cfcfcf, 0x00d3d3d3, 0x00d8d8d8, 0x00dbdbdb, 0x00e0e0e0, 0x00bfbfbf, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00bfbfbf, 0x00999999, 0x00999999, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x00727272, 0x008c8c8c, 0x00898989, 0x008a8a8a, 0x008a8a8a, 0x008a8a8a, 0x008b8b8b, 0x008b8b8b, 0x008c8c8c, 0x00868686, 0x00696969, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d5d5d5, 0x00e1e1e1, 0x00d5d5d5, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00808080, 0x00313131, 0x003d3d3d, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00424242, 0x00262626, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00c4c4c4, 0x00b8b8b8, 0x00b3b3b3, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00bfbfbf, 0x00989898, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00ffffff, 0x00d2d2d2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cacaca, 0x00c2c2c2, 0x00bbbbbb, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00cfcfcf, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d0d0d0, 0x00e0e0e0, 0x00d6d6d6, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 
	0x006f6f6f, 0x00e3e3e3, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 
	0x00666666, 0x00bebebe, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 
	0x005a5a5a, 0x008c8c8c, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 
	0x006b6b6b, 0x00d0d0d0, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3
};

const unsigned long middle[24] = {
	0x00262626, 
	0x00d2d2d2, 
	0x00d7d7d7, 
	0x00d4d4d4, 
	0x00c3c3c3, 
	0x00a1a1a1, 
	0x00dddddd, 
	0x00999999, 
	0x00d5d5d5, 
	0x00b3b3b3, 
	0x00bbbbbb, 
	0x00c3c3c3, 
	0x00a1a1a1, 
	0x00dddddd, 
	0x00999999, 
	0x00d5d5d5, 
	0x00b3b3b3, 
	0x00bbbbbb, 
	0x00d6d6d6, 
	0x00cccccc, 
	0x00cccccc, 
	0x00898989, 
	0x00323232, 
	0x00a3a3a3
};

// 'right', 54x24px
const unsigned long right[1296] = {
	0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00262626, 0x00646477, 
	0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x00d2d2d2, 0x009c9c9c, 0x005a5a5a, 0x00646477, 
	0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00d7d7d7, 0x00a2a2a2, 0x005b5b5b, 0x003b3b41, 
	0x00d4d4d4, 0x00cdcdcd, 0x00cccccc, 0x00c9c9c9, 0x00cacaca, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00bdbdbd, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00bebebe, 0x00e2e2e2, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00c2c2c2, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00a6a6a6, 0x00b6b6b6, 0x00e5e5e5, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00c3c3c3, 0x00b9b9b9, 0x00b9b9b9, 0x00b6b6b6, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x007a7a7a, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x00999999, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x005e5e5e, 0x008a8a8a, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00a1a1a1, 0x00a0a0a0, 0x00a0a0a0, 0x009f9f9f, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00262626, 0x00414141, 0x00414141, 0x00393939, 0x002b2b2b, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00414141, 0x00393939, 0x002b2b2b, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00dddddd, 0x00cecece, 0x00cccccc, 0x00c7c7c7, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00e4e4e4, 0x00262626, 0x00ffffff, 0x00ffffff, 0x00afafaf, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00e4e4e4, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00bfbfbf, 0x005e5e5e, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00999999, 0x00999999, 0x00999999, 0x00999999, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00ffffff, 0x00b2b2b2, 0x00acacac, 0x00afafaf, 0x00b3b3b3, 0x00a5a5a5, 0x00262626, 0x00c0c0c0, 0x00c4c4c4, 0x009b9b9b, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00e4e4e4, 0x00bdbdbd, 0x00ababab, 0x00afafaf, 0x00b3b3b3, 0x00b7b7b7, 0x00bcbcbc, 0x00bfbfbf, 0x00c4c4c4, 0x00a4a4a4, 0x005e5e5e, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00d5d5d5, 0x00c8c8c8, 0x00c5c5c5, 0x00c2c2c2, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00ffffff, 0x00b6b6b6, 0x00b0b0b0, 0x00b4b4b4, 0x00b8b8b8, 0x00a9a9a9, 0x00262626, 0x00c4c4c4, 0x00c9c9c9, 0x009c9c9c, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00e4e4e4, 0x00c1c1c1, 0x00afafaf, 0x00b3b3b3, 0x00b8b8b8, 0x00bcbcbc, 0x00bfbfbf, 0x00c4c4c4, 0x00c8c8c8, 0x00a6a6a6, 0x005e5e5e, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00b3b3b3, 0x00adadad, 0x00ababab, 0x00ababab, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00ffffff, 0x00bababa, 0x00b4b4b4, 0x00b8b8b8, 0x00bcbcbc, 0x00acacac, 0x00262626, 0x00c9c9c9, 0x00cdcdcd, 0x009e9e9e, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x006a6a6a, 0x00636363, 0x005a5a5a, 0x005b5b5b, 0x005d5d5d, 0x005f5f5f, 0x00616161, 0x00626262, 0x00646464, 0x00575757, 0x003c3c3c, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00bbbbbb, 0x00b3b3b3, 0x00b2b2b2, 0x00b0b0b0, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00ffffff, 0x00bdbdbd, 0x00b8b8b8, 0x00bcbcbc, 0x00c0c0c0, 0x00b0b0b0, 0x00262626, 0x00cdcdcd, 0x00d0d0d0, 0x009f9f9f, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00858585, 0x00767676, 0x006f6f6f, 0x00727272, 0x00737373, 0x00767676, 0x00787878, 0x007a7a7a, 0x007c7c7c, 0x00686868, 0x00424242, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00c3c3c3, 0x00b9b9b9, 0x00b9b9b9, 0x00b6b6b6, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00adadad, 0x00858585, 0x00838383, 0x00868686, 0x00888888, 0x00808080, 0x00262626, 0x00d1d1d1, 0x00d5d5d5, 0x00a2a2a2, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x009f9f9f, 0x008d8d8d, 0x00838383, 0x00868686, 0x00888888, 0x008a8a8a, 0x008d8d8d, 0x00909090, 0x00929292, 0x00797979, 0x00474747, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00a1a1a1, 0x00a0a0a0, 0x00a0a0a0, 0x009f9f9f, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00414141, 0x00393939, 0x00393939, 0x003a3a3a, 0x003a3a3a, 0x003b3b3b, 0x003c3c3c, 0x00d5d5d5, 0x00d8d8d8, 0x00a3a3a3, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00414141, 0x00393939, 0x00393939, 0x003a3a3a, 0x003a3a3a, 0x003b3b3b, 0x003c3c3c, 0x003c3c3c, 0x003c3c3c, 0x00373737, 0x002b2b2b, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00dddddd, 0x00cecece, 0x00cccccc, 0x00c7c7c7, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00ffffff, 0x00c8c8c8, 0x00c4c4c4, 0x00c9c9c9, 0x00cccccc, 0x00d0d0d0, 0x00d4d4d4, 0x00d9d9d9, 0x00dddddd, 0x00a5a5a5, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00e4e4e4, 0x00cfcfcf, 0x00c4c4c4, 0x00c8c8c8, 0x00cccccc, 0x00d0d0d0, 0x00d4d4d4, 0x00d8d8d8, 0x00dddddd, 0x00b0b0b0, 0x005e5e5e, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00999999, 0x00999999, 0x00999999, 0x00999999, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00ffffff, 0x00cccccc, 0x00c8c8c8, 0x00cccccc, 0x00d1d1d1, 0x00d5d5d5, 0x00d9d9d9, 0x00dddddd, 0x00e1e1e1, 0x00a5a5a5, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00e4e4e4, 0x00d3d3d3, 0x00c8c8c8, 0x00cccccc, 0x00d0d0d0, 0x00d4d4d4, 0x00d8d8d8, 0x00dddddd, 0x00e1e1e1, 0x00b2b2b2, 0x005e5e5e, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00d5d5d5, 0x00c8c8c8, 0x00c5c5c5, 0x00c2c2c2, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00909090, 0x00888888, 0x00898989, 0x008a8a8a, 0x008a8a8a, 0x008a8a8a, 0x008b8b8b, 0x008b8b8b, 0x008d8d8d, 0x00868686, 0x00535353, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00848484, 0x008c8c8c, 0x00898989, 0x008a8a8a, 0x008a8a8a, 0x008a8a8a, 0x008b8b8b, 0x008b8b8b, 0x008c8c8c, 0x00868686, 0x005e5e5e, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00b3b3b3, 0x00adadad, 0x00ababab, 0x00ababab, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b0b0b0, 0x00757575, 0x00262626, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00373737, 0x00777777, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00b9b9b9, 0x00808080, 0x00262626, 0x00424242, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x00484848, 0x003c3c3c, 0x005c5c5c, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00bbbbbb, 0x00b3b3b3, 0x00b2b2b2, 0x00b0b0b0, 0x00c8c8c8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00c7c7c7, 0x00b9b9b9, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00bcbcbc, 0x00f8f8f8, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00c9c9c9, 0x00bfbfbf, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00929292, 0x00aeaeae, 0x00ffffff, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00d6d6d6, 0x00cdcdcd, 0x00cccccc, 0x00c9c9c9, 0x00c9c9c9, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d9d9d9, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00e9e9e9, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00d3d3d3, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00ececec, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00cccccc, 0x00999999, 0x00575757, 0x00262626, 
	0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x00898989, 0x006b6b6b, 0x00434343, 0x00262626, 
	0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00323232, 0x00303030, 0x002a2a2a, 0x00262626, 
	0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x00a3a3a3, 0x007b7b7b, 0x004b4b4b, 0x00262626
};



void test_app_main( void ) {
	// console default:
	// x = 320
	// y = 150
	// width = 560
	// height = 350

	// left is 29w and 24h
	// middle is 1w and 24h
	// right is 54w and 24h

	int x = 320;
	int y = 150 - 29;
	int i = 0;
	int middle_repeat = 560 - 29 - 54;

	// left, 29x24
	for( int i = 0; i < 24; i++ ) {
		for( int j = 0; j < 29; j++) {
			put_pixel(x + j, y + i, left[(i * 29) + j]);
		}
	}

	x = x + 29;

	// middle, 1x24 (n = middle_repeat)
	for( int n = 0; n < middle_repeat; n++ ) {
		for( int j = 0; j < 24; j++ ) {
			put_pixel( x + n, y + j, middle[j]);
		}
	}

	x = x + middle_repeat;

	// right, 54x24
	for( int i = 0; i < 24; i++ ) {
		for( int j = 0; j < 54; j++) {
			put_pixel(x + j, y + i, right[(i * 54) + j]);
		}
	}
	

	vga_draw_screen();
}