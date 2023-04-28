#if !defined(VUIWINDOW_INCLUDED)
#define VUIWINDOW_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif


#include <stdint.h>
#include <stdbool.h>
#include <vui/vui.h>

typedef struct vui_window {
	vui_handle  handle;
	vui_handle  parent;
	
	int			x;
	int			y;
	int			width;
	int			height;
};

#ifdef __cplusplus
}
#endif

#endif