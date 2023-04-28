#include <kernel.h>
#include <vui/vui.h>

vui_handle_data handles[ VUI_MAX_HANDLES ];

vui_handle  vui_handle_top;
vui_error   vui_last_error;

void vui_initalize( void ) {
    vui_handle_top = 1;
    vui_last_error = 0;
}

vui_handle vui_add_handle( int handle_type, void *resource ) {
    if( vui_handle_top == VUI_MAX_HANDLES ) {
        vui_last_error = VUI_ERROR_MAX_HANDLES;
        return 0;
    }

    handles[vui_handle_top].handle = vui_handle_top;
    handles[vui_handle_top].handle_type = handle_type;
    handles[vui_handle_top].resource = resource;

    vui_handle_top++;

    return vui_handle_top - 1;
}