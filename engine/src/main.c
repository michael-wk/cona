
/*
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "application.h"
#include "cona_math.h"
#include "hashtab.h"

#define APP_NAME "Cona"
#define WINDOW_SIZE_X 500
#define WINDOW_SIZE_Y 500

static application_window app_window;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{

    application_window_init(&app_window, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    // engine testing:
    hash_tab ht;
    hash_tab_init_params params = hash_tab_get_params();
    params.bucket_size = 0xD;
    hash_tab_init(&ht, &params);

    printf("insert : %d\r\n",hash_tab_insert(&ht, "test"));
    printf("insert : %d\r\n",hash_tab_insert(&ht, "grace"));
    printf("insert : %d\r\n",hash_tab_insert(&ht, "mike"));
    printf("insert : %d\r\n",hash_tab_insert(&ht, "crew"));
    printf("insert : %d\r\n",hash_tab_insert(&ht, "bar"));
    printf("insert : %d\r\n",hash_tab_insert(&ht, "foo"));
    printf("insert : %d\r\n",hash_tab_insert(&ht, "poop"));

    hash_tab_print(&ht);



    Uint32 SDL_WindowFlags =  SDL_WINDOW_RESIZABLE;
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer(APP_NAME, app_window.size_x, app_window.size_y, SDL_WindowFlags, &app_window.window, &app_window.renderer))
    {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    app_window.t = SDL_CreateTexture(app_window.renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        app_window.size_x, app_window.size_y);

    SDL_SetTextureBlendMode(app_window.t, SDL_BLENDMODE_NONE);
    SDL_SetTextureScaleMode(app_window.t, SDL_SCALEMODE_NEAREST);
    // SDL_SetTextureScaleMode(this->target, SDL_SCALEMODE_NEAREST);


    SDL_ShowWindow(app_window.window);
    SDL_RaiseWindow(app_window.window);
    
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_QUIT) 
    {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    
    return SDL_APP_CONTINUE;
}



/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}
