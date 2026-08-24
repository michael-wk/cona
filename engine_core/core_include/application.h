#ifndef _APPLICATION_
#define _APPLICATION_

#include <stdint.h>
#include <SDL3/SDL.h>

/* Application window
 * @brief contains the data for the application window.
*/ 
typedef struct
{
    uint16_t size_x;
    uint16_t size_y;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* t;
} application_window;

/* @brief initializes application window */ 
void application_window_init(application_window* a, uint16_t w, uint16_t h);


#endif
