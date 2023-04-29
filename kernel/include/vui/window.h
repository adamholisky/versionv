#if !defined(VUIWINDOW_INCLUDED)
#define VUIWINDOW_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif


#include <stdint.h>
#include <stdbool.h>
#include <vui/vui.h>

typedef struct {
	vui_object  common;
	
	int			x;
	int			y;
	int			width;
	int			height;

	char		*title;
} vui_window;

vui_window *vui_window_new( int x, int y, int width, int height, char *title );
void vui_window_destroy( vui_window *window );
bool vui_window_draw( vui_window *window );
rect *vui_window_get_inner_rect( vui_window *window, rect *r );

#ifdef __cplusplus
}
#endif

#endif