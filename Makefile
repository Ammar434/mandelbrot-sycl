CXX = acpp
CXXFLAGS = -O3 -std=c++23 -g $(shell sdl2-config --cflags) -I include $(shell pkg-config --cflags SDL2_image) -I/usr/include
LDFLAGS = $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image) 

SRCDIR = src
INCDIR = include
BINDIR = bin
IMAGEDIR = images

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRCS))
TARGET = mandelbrot

all: $(TARGET)

$(TARGET): $(OBJS) | $(BINDIR)  $(IMAGEDIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(IMAGEDIR):
	mkdir -p $(IMAGEDIR)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BINDIR)
	rm -rf images/*.jpg

# Dependencies
$(BINDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/constants.hpp $(INCDIR)/mandelbrot.hpp $(INCDIR)/sdl_utils.hpp
$(BINDIR)/mandelbrot.o: $(SRCDIR)/mandelbrot.cpp $(INCDIR)/mandelbrot.hpp $(INCDIR)/constants.hpp
$(BINDIR)/sdl_utils.o: $(SRCDIR)/sdl_utils.cpp $(INCDIR)/sdl_utils.hpp $(INCDIR)/constants.hpp

.PHONY: all clean
