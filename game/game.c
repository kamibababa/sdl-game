// Grayson Pike, 2016

#include <stdbool.h>
#include "game.h"
#include "block.h"
#include "clock.h"

struct node *blocks;
float delta;

void game_init() {

    init_clock();

    blocks = linked_list_create();

    linked_list_add_item(blocks, create_block(WIDTH/2, HEIGHT/2, 64, 64));
    linked_list_add_item(blocks, create_block(WIDTH/3, HEIGHT/3, 64, 64));
}

bool game_update() {

    SDL_Event event;

    while(SDL_PollEvent(&event) != 0) {
        if(event.type == SDL_QUIT) {
            return false;
        }
        if(event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return false;
                    break;
                default:
                    break;
            }
        }
    }

    delta = get_delta();

    // Key states
    const Uint8 *key_states = SDL_GetKeyboardState(NULL);
    struct block *b = (struct block*)linked_list_get_item(blocks, 0);
    if(key_states[SDL_SCANCODE_UP]) {
        move_block(b, 'u', delta);
    }
    if(key_states[SDL_SCANCODE_DOWN]) {
        move_block(b, 'd', delta);
    }
    if(key_states[SDL_SCANCODE_LEFT]) {
        move_block(b, 'l', delta);
    }
    if(key_states[SDL_SCANCODE_RIGHT]) {
        move_block(b, 'r', delta);
    }

    return true;
}

void game_quit() {
    linked_list_free_list(blocks);
}