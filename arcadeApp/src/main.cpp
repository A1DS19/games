#include "main.hpp"

#include "SDL_surface.h"
#include "graphics/color.hpp"
#include "graphics/screenBuffer.hpp"

int main() {
  ScreenBuffer screenBuffer;
  screenBuffer.Init(pixelFormat->format, windowSurface->w, windowSurface->h);
  screenBuffer.SetPixel(Color::Red(), SCREEN_W / 2, SCREEN_H / 2);
  SDL_BlitSurface(screenBuffer.GetSurface(), nullptr, windowSurface, nullptr);

  SDL_UpdateWindowSurface(sdlWindow);

  SDL_Event sdlEvent;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&sdlEvent)) {
      switch (sdlEvent.type) {
      case SDL_QUIT:
        running = false;
        break;

      default:
        break;
      }
    }
  }

  return EXIT_SUCCESS;
}
