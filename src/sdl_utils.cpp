#include "sdl_utils.hpp"
#include <iomanip>
#include <sstream>

void initializeSDL(SDL_Window *&window, SDL_Renderer *&renderer,
                   SDL_Texture *&texture) {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Mandelbrot Explorer", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                            SDL_WINDOW_VULKAN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
                              SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

void cleanup(sycl::queue &q, uint32_t *pixels, SDL_Surface *surface,
             SDL_Texture *texture, SDL_Renderer *renderer, SDL_Window *window) {
  sycl::free(pixels, q);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void handleEvents(SDL_Event &event, bool &running, complex_t &center,
                  real_t &zoom, bool &autozoom) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_SPACE:
        center = complex_t{real_t(START_X), real_t(START_Y)};
        zoom = START_ZOOM;
        break;
      case SDLK_ESCAPE:
        running = false;
        break;
      case SDLK_a:
        autozoom = !autozoom;
        break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      // When updating center
      real_t dx = (event.button.x - (WIDTH / 2)) / zoom;
      real_t dy = (event.button.y - (HEIGHT / 2)) / zoom;
      center += complex_t(dx, dy);
      if (event.button.button == SDL_BUTTON_LEFT) {
        zoom *= ZOOM_FACTOR + sycl::log10(zoom);
      } else if (event.button.button == SDL_BUTTON_RIGHT) {
        zoom /= ZOOM_FACTOR;
      }
      break;
    }
  }
}

void saveFrame(SDL_Renderer *renderer, SDL_Surface *surface, int frameCount) {
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
                       surface->pixels, surface->pitch);

  std::ostringstream oss;
  oss << "images/mandelbrot_frame_" << std::setw(6) << std::setfill('0')
      << frameCount << ".jpg";

  IMG_SaveJPG(surface, oss.str().c_str(), 70);
}