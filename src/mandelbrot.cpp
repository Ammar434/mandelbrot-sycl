#include "mandelbrot.hpp"
void drawMandelbrot(SDL_Renderer *renderer, SDL_Texture *texture,
                    complex_t center, real_t zoom, sycl::queue &q,
                    uint32_t *pixels) {

  q.submit([&](sycl::handler &h) {
    h.parallel_for(sycl::range<2>(HEIGHT, WIDTH), [=](sycl::id<2> id) {
      int py = id[0];
      int px = id[1];
      real_t x = (px - WIDTH / 2.0) / zoom + center.real();
      real_t y = (py - HEIGHT / 2.0) / zoom + center.imag();

      int n = 0;
      real_t zr = 0, zi = 0;
      real_t zr2 = 0, zi2 = 0;
      real_t cr = x, ci = y;

      int MAX_ITERATIONS =
          sycl::clamp(static_cast<int>(100 + 50 * sycl::log(zoom)), 100, 10000);

      // Check if point is in main cardioid or period-2 bulb
      real_t q = (x - 0.25) * (x - 0.25) + y * y;
      if (q * (q + (x - 0.25)) < 0.25 * y * y ||
          (x + 1) * (x + 1) + y * y < 0.0625) {
        n = MAX_ITERATIONS;
      } else {
        while (n < MAX_ITERATIONS && zr2 + zi2 < BAIL_OUT * BAIL_OUT) {
          zi = 2 * zr * zi + ci;
          zr = zr2 - zi2 + cr;
          zr2 = zr * zr;
          zi2 = zi * zi;
          ++n;
        }
      }

      real_t smooth_n = n - sycl::log2(sycl::log(zr2 + zi2) / sycl::log(2.0));

      real_t r = (1 + sycl::sin(smooth_n * 0.07 + 5)) * 127.0;
      real_t g = (1 + sycl::cos(smooth_n * 0.05)) * 127.0;
      real_t b = (1 + sycl::sin(smooth_n * 0.05)) * 127.0;

      pixels[py * WIDTH + px] = (n >= MAX_ITERATIONS)
                                    ? 0
                                    : (static_cast<uint32_t>(r) << 16) |
                                          (static_cast<uint32_t>(g) << 8) |
                                          static_cast<uint32_t>(b);
    });
  });

  q.wait();

  SDL_UpdateTexture(texture, nullptr, pixels, WIDTH * sizeof(uint32_t));
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}