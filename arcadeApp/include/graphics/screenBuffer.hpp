#pragma once
#include <SDL_surface.h>
#include <stdint.h>

#include <cassert>
#include <cstddef>
#include <cstdlib>

#include "color.hpp"

class SDL_Surface;

class ScreenBuffer {
public:
  ScreenBuffer();
  ScreenBuffer(const ScreenBuffer &screenBuffer);
  ~ScreenBuffer();
  ScreenBuffer &operator=(const ScreenBuffer &screenBuffer);
  void Init(uint32_t format, uint32_t w, uint32_t h);
  inline SDL_Surface *GetSurface() { return mSurface; }
  void Clear(const Color &color = Color::Black());
  void SetPixel(const Color &color, uint32_t x, uint32_t y);

private:
  SDL_Surface *mSurface;
  uint32_t GetIndex(int r, int c);
};
