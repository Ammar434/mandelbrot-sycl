#pragma once

#include "constants.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <sycl/sycl.hpp>

void initializeSDL(SDL_Window *&window, SDL_Renderer *&renderer,
                   SDL_Texture *&texture);
void cleanup(sycl::queue &q, uint32_t *pixels, SDL_Surface *surface,
             SDL_Texture *texture, SDL_Renderer *renderer, SDL_Window *window);
void handleEvents(SDL_Event &event, bool &running, complex_t &center,
                  real_t &zoom, bool &autozoom);
void saveFrame(SDL_Renderer *renderer, SDL_Surface *surface, int frameCount);