#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"

// SDL Container object
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} sdl_t;

// Emulator config object
typedef struct {
    uint32_t window_height; // SDL Window Height
    uint32_t window_width; // SDL Window Width
    uint32_t fg_color; // Foreground Color
    uint32_t bg_color; // Background Color
    uint32_t scale_factor; // Amount to scale a CHIP8 pixel by

} config_t;

// Emulator states
typedef enum {
    QUIT,
    RUNNING,
    PAUSED,
} emu_state_t;

// CHIP8 Machine Setup
typedef struct {
    emu_state_t state;
    uint8_t ram[4096];

    
} chip8_t;

//initialize sdl
bool init_sdl(sdl_t *sdl, const config_t config){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        SDL_Log("Could not initialize SDL: %s.\n", SDL_GetError());
        return false;
    }

    // Create window
    sdl->window = SDL_CreateWindow("New Window", 
                                    SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     config.window_width * config.scale_factor,
                                    config.window_height * config.scale_factor,
                                     SDL_WINDOW_OPENGL);
    if (sdl->window == NULL) {
        fprintf(stderr, "Couldn't create window. %s\n", SDL_GetError());
        return false;
    }

    sdl->renderer = SDL_CreateRenderer(sdl->window, - 1, SDL_RENDERER_ACCELERATED);
    if (sdl->renderer == NULL) {
        fprintf(stderr, "Couldn't create renderer. %s\n", SDL_GetError());
        return false;
    }

    return true;

}

// set up initial emulator config from arguments
bool set_config_args(config_t *config, const int argc, const char **argv){

    // Defaults
    config->window_width = 64;  // original X resolution of CHIP-8
    config->window_height = 32; // original Y resolution of CHIP-8

    // If command is passed for dimensions set dimensions 
    if (argc > 1) {
        config->window_width = (uint32_t)atoi(argv[1]);
    }

    if (argc > 2) {
        config->window_height = (uint32_t)atoi(argv[2]);
    }



    config->fg_color = 0xFFFFFFFF; // White
    config->bg_color = 0xFFFF00FF; // Yellow
    config->scale_factor = 20; // Default Resolution is 1280x640

    return true;
}

// quit sdl
void cleanup_sdl(const sdl_t sdl){
    printf("\nQuitting SDL.\n");

    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();
}

void clear_window(const sdl_t sdl, const config_t config) {

    // Set rgba values -> Use bitshift and mask to extract rgba
    const uint8_t r = (config.bg_color >> 24) & 0xFF; 
    const uint8_t g = (config.bg_color >> 16) & 0xFF;
    const uint8_t b = (config.bg_color >>  8) & 0xFF;
    const uint8_t a = config.bg_color & 0xFF;

    // Inititial Screen Clear to Background Color
    SDL_SetRenderDrawColor(sdl.renderer, r, g, b, a);

    // Fill back buffer with specified color from set
    SDL_RenderClear(sdl.renderer);
}

// Update changes to window
void update_window(const sdl_t sdl){
    // Present rendered frame to front buffer
    SDL_RenderPresent(sdl.renderer);
}

void handle_input(chip8_t *chip8){
    SDL_Event event;

    while (SDL_PollEvent(&event)) // poll until all events are handled (works as a queue)
        switch(event.type) {
            case SDL_QUIT:
                // Exit window and end program
                chip8->state = QUIT; // Exit main emulator loop
                return;
            
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        // Escape Key; Exist window and End Program
                        chip8->state = QUIT;
                        return;

                    case SDLK_DOWN:
                        return;
                    
                    case SDLK_UP:
                        return;

                    case SDLK_LEFT:
                        return;

                    case SDLK_RIGHT:
                        return;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                break;
            
            default:
                break;
        }
}

bool init_chip8(chip8_t *chip8){
    // Initialize CHIP8 state
    chip8->state = RUNNING;

    return true;
}




int main(const int argc, const char **argv) {
    (void) argc;
    (void) argv;


    // Initialize SDL and Config
    sdl_t sdl = {0};
    config_t config = {0};
    if (!set_config_args(&config, argc, argv)){
            printf("Hello, World!1111111\n");
        exit(1);
    }

    // Initialize SDL
    if(!init_sdl(&sdl, config)){
            printf("Hello, World!222222222\n");

        exit(1);
    }    

    // Initialize CHIP8 Machine
    chip8_t chip8 = {0};
    if (!init_chip8(&chip8)){
        exit(1);
    }
    


    // Initial Background Clear
    clear_window(sdl, config);

    // Main emulator loop

    while (chip8.state != QUIT) {

        // Handle user input
        handle_input(&chip8);
        // If chip8.state == PAUSED continue;

        // Get_time();
        // Emulate CHIP8 Instructions
        // Ge_time() elapsed since last get_time()

        // Delay for approx. 60hz/fps (16.67ms)
        // SDL_Delay(16 - actual time elapsed);
        SDL_Delay(16);
        // Update Window with changes
        update_window(sdl);
    }

    // Cleanup at exit
    cleanup_sdl(sdl);
    
    // Create window
    printf("Exiting Application.\n\n");
    exit(0);
}
