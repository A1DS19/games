#include "main.hpp"

#include "graphics/screen.hpp"
#include "main.hpp"
#include "shapes/line2d.hpp"

int main() {
  Screen screen;

  screen.Init(SCREEN_W, SCREEN_H, MAGNIFICATION);
  Line2d line = {Vec2D(0, 0), Vec2D(SCREEN_W, SCREEN_H)};
  screen.Draw(line, Color::White());
  // screen.Draw(SCREEN_W / 2, SCREEN_H / 2, Color::Blue());
  screen.SwapScreen();

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
