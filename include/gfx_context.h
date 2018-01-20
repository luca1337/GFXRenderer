#pragma once

#define SDL_MAIN_HANDLED 1

#include <string.h>
#include <stdio.h>
#ifdef _WIN32
#include <SDL/SDL.h>
#else
#include <SDL/SDL2.h>
#endif

typedef struct gfx_color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
}gfx_color_t;

gfx_color_t gfx_set_colors(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

typedef struct gfx_context{
    SDL_Window* window;
    SDL_Renderer* renderer;
    uint32_t width;
    uint32_t height;
    uint32_t half_width;
    uint32_t half_height;
    int32_t is_running;
    float delta_time;
    float screen_ratio;
    long long unsigned last;
    const Uint8* key_state;
}gfx_context_t;

gfx_context_t* gfx_init(const char* title, uint32_t width, uint32_t height);
void gfx_put_pixel(gfx_context_t *context, int x, int y, gfx_color_t color);
void gfx_context_dispose(gfx_context_t* context);
Uint8 gfx_get_key_state(gfx_context_t* context, SDL_Scancode code);
void gfx_context_quit(gfx_context_t *context);
void gfx_update(gfx_context_t* context);