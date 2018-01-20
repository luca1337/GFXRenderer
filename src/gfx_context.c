#include <gfx_context.h>
#include <colors.h>
#include <stdlib.h>
#include <shape.h>
#include <time.h>

gfx_context_t* gfx_init(const char* title, unsigned int width, unsigned int height)
{
    gfx_context_t* context = malloc(sizeof(gfx_context_t));
    if(!context)
        return ((void*)0);

    SDL_Init(SDL_INIT_VIDEO);

    context->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if(!context->window)
    {
        SDL_Quit();
        free(context);
        return ((void*)0);
    }

    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!context->renderer)
    {
        SDL_DestroyWindow(context->window);
        SDL_Quit();
        free(context);
        return ((void*)0);
    }

    context->last = SDL_GetPerformanceCounter();
    context->key_state  = SDL_GetKeyboardState(NULL);
    context->width = width;
    context->height = height;
    context->half_width = width / 2;
    context->half_height = height / 2;
    context->screen_ratio = (float)width / (float)height;
    context->delta_time = 0;
    context->is_running = 1;

    return context;
} 

 Uint8 gfx_context_get_key_state(gfx_context_t* context, SDL_Scancode code)
{
    return context->key_state[code];
}

static void gfx_context_blit(gfx_context_t *context)
{
    SDL_RenderPresent(context->renderer);
    long long unsigned now = SDL_GetPerformanceCounter();
    context->delta_time = (float)(now - context->last) / SDL_GetPerformanceFrequency();
    context->last = now;
}

static void gfx_context_clear(gfx_context_t *context, gfx_color_t color)
{
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(context->renderer);
}

void gfx_put_pixel(gfx_context_t *context, int x, int y, gfx_color_t color)
{
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(context->renderer, x, y);
}

void gfx_context_dispose(gfx_context_t* context)
{
    SDL_DestroyWindow(context->window);
    SDL_DestroyRenderer(context->renderer);
    SDL_Quit();
    free(context);
}

void gfx_context_quit(gfx_context_t *context)
{
    context->is_running = !context->is_running;
}

gfx_color_t gfx_set_colors(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    gfx_color_t original_color;
    original_color.r = r;
    original_color.g = g;
    original_color.b = b;
    original_color.a = a;
    return original_color;
}

void gfx_update(gfx_context_t* context)
{
    //randomize color for the square each tick
    srand(time(NULL));
    gfx_color_t new_color = gfx_set_colors(rand()%255, rand()%255, rand()%255, rand()%255);

    gfx_shape_t* quad = gfx_shape_new(context->half_width, context->half_height, 100, 100, new_color);

    while(context->is_running)
    {
        //update event queue and internal input device state
        SDL_PumpEvents();
        
        //clear color window
        gfx_context_clear(context, black); 

        //draw simple shape
        gfx_shape_draw(context, quad);

        //quit key code
        if(gfx_context_get_key_state(context, SDL_SCANCODE_ESCAPE))
            gfx_context_quit(context);

        //blit
        gfx_context_blit(context);
    }

    //free shape
    gfx_shape_dispose(quad);

    //free memory when exiting
    gfx_context_dispose(context);
}
