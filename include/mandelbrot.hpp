#pragma once

#include "constants.hpp"
#include <SDL2/SDL.h>
#include <mpfr.h>
#include <sycl/sycl.hpp>
SYCL_EXTERNAL int mandelbrot(real_t cr, real_t ci, real_t zoom);
SYCL_EXTERNAL real_t smooth_iter(real_t zr, real_t zi, int n);
void drawMandelbrot(SDL_Renderer *renderer, SDL_Texture *texture,
                    complex_t center, real_t zoom, sycl::queue &q,
                    uint32_t *pixels);