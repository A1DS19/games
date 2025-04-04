#include "main.hpp"

#include "SDL_surface.h"
#include "graphics/color.hpp"
#include "graphics/screenBuffer.hpp"

int main() {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "SDL init failed" << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Window *sdlWindow =
      SDL_CreateWindow("ArcadaApp", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, 0);

  if (sdlWindow == nullptr) {
    std::cout << "SDL could not create window: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Surface *windowSurface = SDL_GetWindowSurface(sdlWindow);

  SDL_PixelFormat *pixelFormat = windowSurface->format;
  Color::InitColorFormat(pixelFormat);

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

  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();

  return EXIT_SUCCESS;
}
