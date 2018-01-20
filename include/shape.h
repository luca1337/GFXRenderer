#include <gfx_context.h>

typedef struct gfx_shape{
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
    gfx_color_t color;
}gfx_shape_t;

gfx_shape_t gfx_shape_new(int32_t x, int32_t y, int32_t w, int32_t h, gfx_color_t color);
void gfx_shape_draw(gfx_context_t* context, gfx_shape_t shape);