#include <stdio.h>
#include <sdl_context.h>

static gfx_context_t* context;

int main(int args, char** argv)
{ 
    context = gfx_init("Square", 800, 600);
    gfx_update(context);

    return 0;
}