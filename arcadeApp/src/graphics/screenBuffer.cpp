#include "graphics/screenBuffer.hpp"

#include <iostream>

ScreenBuffer::ScreenBuffer() : mSurface(nullptr) {}

ScreenBuffer::ScreenBuffer(const ScreenBuffer &screenBuffer) {
  mSurface = SDL_CreateRGBSurfaceWithFormat(
      0, screenBuffer.mSurface->w, screenBuffer.mSurface->h, 0,
      screenBuffer.mSurface->format->format);

  SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr);
}

ScreenBuffer::~ScreenBuffer() {
  if (mSurface) {
    SDL_FreeSurface(mSurface);
  }
}

ScreenBuffer &ScreenBuffer::operator=(const ScreenBuffer &screenBuffer) {
  if (this == &screenBuffer) {
    return *this;
  }

  if (mSurface != nullptr) {
    SDL_FreeSurface(mSurface);
    mSurface = nullptr;
  }

  if (screenBuffer.mSurface != nullptr) {
    mSurface = SDL_CreateRGBSurfaceWithFormat(
        0, screenBuffer.mSurface->w, screenBuffer.mSurface->h, 0,
        screenBuffer.mSurface->format->format);

    SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr);
  }

  return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t w, uint32_t h) {
  mSurface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 0, format);
  Clear();
}

void ScreenBuffer::Clear(const Color &color) {
  assert(mSurface);
  if (mSurface) {
    SDL_FillRect(mSurface, nullptr, color.GetPixelColor());
  }
}

void ScreenBuffer::SetPixel(const Color &color, uint32_t x, uint32_t y) {
  assert(mSurface);
  if (mSurface && (y < mSurface->h && y >= 0 && x >= 0 && x < mSurface->w)) {
    SDL_LockSurface(mSurface);
    uint32_t *pixels = (uint32_t *)mSurface->pixels;
    size_t index = GetIndex(y, x);
    Color surfaceColor = Color(pixels[index]);
    pixels[index] =
        Color::Evaluate1MinueSourceAlpha(color, surfaceColor).GetPixelColor();
    SDL_UnlockSurface(mSurface);
  }
}

uint32_t ScreenBuffer::GetIndex(int row, int col) {
  assert(mSurface);
  if (mSurface) {
    return row * mSurface->w + col;
  }
  return 0;
}
