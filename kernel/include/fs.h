#if !defined(AFS_INCLUDED)
#define AFS_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

void fs_initalize( void );
void primative_ls( char *path );
void primative_pwd( void );
void primative_cat( char *path );

#ifdef __cplusplus
}
#endif

#endif