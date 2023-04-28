#if !defined(VUI_INCLUDED)
#define VUI_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define VUI_MAX_HANDLES 256

#define VUI_TYPE_UNKNOWN 0
#define VUI_TYPE_WINDOW 1
#define VUI_TYPE_DESKTOP 2
#define VUI_TYPE_LABEL 3

#define VUI_FONT_FIRA   0
#define VUI_FONT_VERA   1
#define VUI_FONT_VERAB  2

#define VUI_NO_ERROR 0
#define VUI_ERROR_UNKNOWN 0
#define VUI_ERROR_MAX_HANDLES 1

typedef uint32_t vui_handle;
typedef uint32_t vui_error;

typedef struct {
    vui_handle  handle;
    int         handle_type;
    void        *resource;
} vui_handle_data;

void vui_initalize( void );

vui_handle vui_add_handle( int handle_type, void *resource );


#ifdef __cplusplus
}
#endif

#endif