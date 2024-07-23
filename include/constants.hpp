#pragma once

// #include "mpreal.h"
#include <cmath>
#include <complex>
constexpr int WIDTH = 3840;
constexpr int HEIGHT = 2160;
constexpr double START_X = -0.104943;
constexpr double START_Y = 0.927572;
constexpr double START_ZOOM = 500;
constexpr double BAIL_OUT = 2.0;
constexpr double ZOOM_FACTOR = 1.0;
// constexpr int MAX_ITERATIONS = 5000;

using real_t = double;
using complex_t = std::complex<real_t>;

// inline void init_mpreal() { mpfr::mpreal::set_default_prec(56); }
