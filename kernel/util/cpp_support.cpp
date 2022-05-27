#include <stddef.h>
#include <kmalloc.h>

extern "C" void __cxa_pure_virtual() {
   // Intentionally blanks
}

void *operator new(size_t size)
{
    return kmalloc(size);
}
 
void *operator new[](size_t size)
{
    return kmalloc(size);
}
 
void operator delete(void *p)
{
    free(p);
}
 
void operator delete[](void *p)
{
    free(p);
}