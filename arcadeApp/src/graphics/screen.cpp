#include "graphics/screen.hpp"

#include <SDL2/SDL.h>

#include <cassert>
#include <cmath>
#include <cstdlib>

#include "SDL_surface.h"
#include "shapes/line2d.hpp"

Screen::Screen()
    : mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrSurface(nullptr) {}

Screen::~Screen() {
  if (moptrWindow) {
    SDL_DestroyWindow(moptrWindow);
    moptrWindow = nullptr;
  }
  SDL_Quit();
}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "SDL init failed" << std::endl;
    return nullptr;
  }

  mWidth = w;
  mHeight = h;

  moptrWindow =
      SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       mWidth * mag, mHeight * mag, 0);

  if (moptrWindow) {
    mnoptrSurface = SDL_GetWindowSurface(moptrWindow);
    SDL_PixelFormat *pixelFormat = mnoptrSurface->format;
    Color::InitColorFormat(pixelFormat);
    mClearColor = Color::Black();
    mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
    mBackBuffer.Clear(mClearColor);
  }

  return moptrWindow;
}

void Screen::SwapScreen() {
  assert(moptrWindow);
  if (moptrWindow) {
    ClearScreen();
    SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrSurface, nullptr);
    SDL_UpdateWindowSurface(moptrWindow);
    mBackBuffer.Clear(mClearColor);
  }
}

void Screen::Draw(int x, int y, const Color &color) {
  assert(moptrWindow);
  if (moptrWindow) {
    std::cout << "x:" << x << " y:" << y << std::endl;
    mBackBuffer.SetPixel(color, x, y);
  }
}

void Screen::Draw(const Vec2D &point, const Color &color) {
  assert(moptrWindow);
  if (moptrWindow) {
    mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
  }
}

void Screen::ClearScreen() {
  assert(moptrWindow);
  if (moptrWindow) {
    SDL_FillRect(mnoptrSurface, nullptr, mClearColor.GetPixelColor());
  }
}

void Screen::Draw(const Line2d &line, const Color &color) {
  assert(moptrWindow);
  if (!moptrWindow)
    return;

  int x0 = roundf(line.GetP0().GetX());
  int y0 = roundf(line.GetP0().GetY());
  int x1 = roundf(line.GetP1().GetX());
  int y1 = roundf(line.GetP1().GetY());

  int dx = abs(x1 - x0);
  int sx = (x0 < x1) ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx + dy, e2;

  while (true) {
    Draw(x0, y0, color);
    if (x0 == x1 && y0 == y1)
      break;
    e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}
