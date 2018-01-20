#include <shape.h>
#include <stdlib.h>
#include <gfx_context.h>

gfx_shape_t* gfx_shape_new(int32_t x, int32_t y, int32_t w, int32_t h, gfx_color_t color)
{
    gfx_shape_t* shape = malloc(sizeof(gfx_shape_t));
    if(!shape)
        return ((void*)0);
    
    shape->x = x;
    shape->y = y;
    shape->w = w;
    shape->h = h;
    shape->color = color;

    return shape;
}

void gfx_shape_dispose(gfx_shape_t* shape)
{
    if(shape) free(shape);
}

void gfx_shape_draw(gfx_context_t* context, gfx_shape_t* shape)
{
    for(unsigned int x = 0; x < shape->w; x++)
    {
        for(unsigned int y = 0; y < shape->h; y++)
        {
            gfx_put_pixel(context, (x + (shape->x - shape->w)), (y + (shape->y - shape->h)), shape->color);
        }
    }
}