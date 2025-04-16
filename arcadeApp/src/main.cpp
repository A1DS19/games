#include "main.hpp"

#include "graphics/color.hpp"
#include "graphics/screen.hpp"
#include "main.hpp"
#include "shapes/aaRectangle.hpp"
#include "shapes/circle.hpp"
#include "shapes/line2d.hpp"
#include "shapes/triangle.hpp"

int main() {
  Screen screen;

  screen.Init(SCREEN_W, SCREEN_H, MAGNIFICATION);

  Line2d line = {Vec2D(0, 0), Vec2D(SCREEN_W, SCREEN_H)};
  Triangle triangle = {Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110)};
  AARectangle rectangle = {Vec2D(SCREEN_W / 2 - 25, SCREEN_H / 2 - 25), 50, 50};
  Circle circle = {Vec2D(SCREEN_W / 2 + 50, SCREEN_H / 2 + 50), 50};

  screen.Draw(line, Color::Red());
  screen.Draw(triangle, Color::White(), true, Color::White());
  screen.Draw(rectangle, Color::Blue(), true, Color::Blue());
  screen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
  screen.Draw(SCREEN_W / 2, SCREEN_H / 2, Color::Blue());

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
