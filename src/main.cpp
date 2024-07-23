#include "constants.hpp"
#include "mandelbrot.hpp"
#include "sdl_utils.hpp"
#include <iostream>
#include <sycl/sycl.hpp>

int main() {
  // init_mpreal();

  // Initialize SYCL queue
  sycl::queue q{sycl::default_selector_v};
  std::cout << "Running on device: "
            << q.get_device().get_info<sycl::info::device::name>() << std::endl;

  // Initialize SDL
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  initializeSDL(window, renderer, texture);

  // Allocate pixels
  uint32_t *pixels = sycl::malloc_shared<uint32_t>(WIDTH * HEIGHT, q);

  // Create surface for saving frames
  SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(
      pixels, WIDTH, HEIGHT, 32, WIDTH * sizeof(uint32_t), 0x00FF0000,
      0x0000FF00, 0x000000FF, 0xFF000000);

  // Initialize view parameters
  complex_t center{real_t(START_X), real_t(START_Y)};
  real_t zoom(START_ZOOM);

  bool autozoom = true;
  int frameCount = 0;

  // Main loop
  SDL_Event event;
  bool running = true;
  while (running) {
    handleEvents(event, running, center, zoom, autozoom);

    if (autozoom)
      zoom *= 1.01;

    // Draw and render
    std::cout << "Center: " << center << ", Zoom: " << zoom << std::endl;
    drawMandelbrot(renderer, texture, center, zoom, q, pixels);
    SDL_RenderPresent(renderer);

    saveFrame(renderer, surface, frameCount);
    frameCount++;
  }

  cleanup(q, pixels, surface, texture, renderer, window);
  return 0;
}