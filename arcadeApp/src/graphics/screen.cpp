#include "graphics/screen.hpp"

#include <SDL2/SDL.h>

#include <cassert>
#include <cstdlib>

#include "SDL_surface.h"

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
      SDL_CreateWindow("ArcadeApp", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

  if (moptrWindow) {
    mnoptrSurface = SDL_GetWindowSurface(moptrWindow);
    SDL_PixelFormat *pixelFormat = mnoptrSurface->format;
    Color::InitColorFormat(pixelFormat);
    mClearColor = Color::Black();
    mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
    mBackBuffer.Clear();
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
