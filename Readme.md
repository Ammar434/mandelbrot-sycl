<h1>Mandelbrot Set Visualizer</h1>

<div align="center">

<a href="https://isocpp.org/"><img src="https://img.shields.io/badge/Made%20with-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B" alt="Made with C++"></a>

<img src="https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat" alt="Contributions welcome">
<a href="https://github.com/yourusername/mandelbrot-visualizer/graphs/commit-activity"><img src="https://img.shields.io/badge/Maintained%3F-yes-green.svg" alt="Maintenance"></a>
<a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT"></a>


</div>

## Demo
https://github.com/user-attachments/assets/7533f51b-8d29-4b83-9d14-1198a73cc95b


<hr>

<h2>🚀 Features</h2>

<ul>
<li> Real-time rendering of the Mandelbrot set</li>
<li> Smooth zooming and panning using mouse</li>
<li> Parallel computation with SYCL for optimal performance</li>
<li> Option to save generated images</li>
</ul>

<h2>🏗️ Project Structure</h2>

<pre>
Mandelbrot Set Visualizer
├── 📄 Makefile
├── 📁 bin/
├── 📁 include/
│   ├── constants.hpp
│   ├── mandelbrot.hpp
│   └── sdl_utils.hpp
├── 📁 src/
│   ├── main.cpp
│   ├── mandelbrot.cpp
│   └── sdl_utils.cpp
├── 📁 images/
└── 📘 README.md
</pre>

<h2>🛠️ Technologies</h2>

<ul>
<li> C++23</li>
<li> SDL2 and SDL2_image</li>
<li> SYCL</li>
</ul>

<h2>📋 Prerequisites</h2>

<ul>
<li> C++23 compatible compiler (e.g., GCC, Clang)</li>
<li> SDL2 and SDL2_image development libraries</li>
<li> SYCL-compatible compiler and runtime (e.g., Intel oneAPI DPC++ Compiler)</li>
<li> Make build automation tool</li>
</ul>

<h2>🚀 Getting Started</h2>

<ol>
<li>Clone the repository:
<pre><code>git clone https://github.com/Ammar434/mandelbrot-sycl.git
cd mandelbrot-sycl
</code></pre>
</li>

<li>Build the project:
<pre><code>make
</code></pre>
</li>

<li>Run the program:
<pre><code>./mandelbrot
</code></pre>
</li>
</ol>

<h2>⚙️ Customizing the Build</h2>

<p>To use a different compiler or adjust flags, modify the <code>Makefile</code>:</p>

<ol>
<li>Change the compiler:
<pre><code>CXX = your_preferred_compiler
</code></pre>
</li>

<li>Adjust compiler flags:
<pre><code>CXXFLAGS = -O2 -std=c++23 -g $(shell sdl2-config --cflags) -I include $(shell pkg-config --cflags SDL2_image) -I/usr/include
CXXFLAGS += -fsycl
</code></pre>
</li>
</ol>

<h2>🤝 Contributing</h2>

<p>Contributions are welcome! Please feel free to submit a Pull Request.</p>

<h2>📄 License</h2>

<p>This project is licensed under the MIT License - see the <a href="LICENSE">LICENSE</a> file for details.</p>


