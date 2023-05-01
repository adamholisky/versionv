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
#define VUI_FONT_DVSM   3

#define VUI_NO_ERROR 0
#define VUI_ERROR_UNKNOWN 0
#define VUI_ERROR_MAX_HANDLES 1

typedef uint32_t vui_handle;
typedef uint32_t vui_error;

typedef void (*vui_draw_func)(void *obj);

typedef struct {
    vui_handle  handle;
    int         handle_type;
    void        *resource;
    bool        in_use;
} vui_handle_data;

typedef struct {
    vui_handle      handle;
    vui_handle      parent;
    int             type;
    vui_draw_func   custom_paint_func;
} vui_object;

void vui_initalize( void );
void vui_refresh( void );
void *vui_add_handle( int handle_type );
void vui_free_handle( vui_handle handle );
bool vui_handle_draw( vui_handle handle );
bool vui_set_parent( void *child, void *parent );
void vui_draw_rectangle( int x, int y, int width, int height, uint32_t color );
int vui_get_string_width( int font, int size, char *s );
void vui_draw_string( int x, int y, int size, uint32_t fg, int font, char *s );
void vui_draw_string_mono( int x, int y, int size, uint32_t fg, int font, char *s );

#ifdef __cplusplus
}
#endif

#endif