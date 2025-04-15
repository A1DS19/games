#include "graphics/screen.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <vector>

#include "SDL_surface.h"
#include "Utils.h"
#include "shapes/aaRectangle.hpp"
#include "shapes/circle.hpp"
#include "shapes/line2d.hpp"
#include "shapes/triangle.hpp"

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

void Screen::Draw(const Triangle &triangle, const Color &color, bool fill,
                  const Color &fillColor) {
  if (fill) {
    FillPoly(triangle.GetPoints(), fillColor);
  }
  Line2d p0p1 = Line2d(triangle.GetP0(), triangle.GetP1());
  Line2d p1p2 = Line2d(triangle.GetP1(), triangle.GetP2());
  Line2d p2p0 = Line2d(triangle.GetP2(), triangle.GetP0());

  Draw(p0p1, color);
  Draw(p1p2, color);
  Draw(p2p0, color);
}

void Screen::Draw(const AARectangle &rectangle, const Color &color, bool fill,
                  const Color &fillColor) {
  if (fill) {
    FillPoly(rectangle.GetPoints(), fillColor);
  }

  std::vector<Vec2D> points = rectangle.GetPoints();
  Line2d p0p1 = Line2d(points[0], points[1]);
  Line2d p1p2 = Line2d(points[1], points[2]);
  Line2d p2p3 = Line2d(points[2], points[3]);
  Line2d p3p0 = Line2d(points[3], points[0]);

  Draw(p0p1, color);
  Draw(p1p2, color);
  Draw(p2p3, color);
  Draw(p3p0, color);
}

void Screen::Draw(const Circle &circle, const Color &color, bool fill,
                  const Color &fillColor) {
  std::vector<Vec2D> circlePoints;
  std::vector<Line2d> lines;

  static unsigned int NUM_CIRCLE_SEGMENTS = 30;
  float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

  Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(),
                   circle.GetCenterPoint().GetY());
  Vec2D p1 = p0;
  Line2d nextLineToDraw;

  for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; i++) {
    p1.Rotate(angle, circle.GetCenterPoint());
    nextLineToDraw.SetP1(p1);
    nextLineToDraw.SetP0(p0);

    lines.push_back(nextLineToDraw);
    // Draw(nextLineToDraw, color);
    p0 = p1;
    circlePoints.push_back(p0);
  }

  if (fill) {
    FillPoly(circlePoints, fillColor);
  }

  for (const Line2d &line : lines) {
    Draw(line, color);
  }
}

void Screen::FillPoly(const std::vector<Vec2D> &points, const Color &color) {
  if (points.size() > 0) {
    float top = points[0].GetY();
    float bottom = points[0].GetY();
    float right = points[0].GetX();
    float left = points[0].GetX();

    for (size_t i = 1; i < points.size(); ++i) {
      if (points[i].GetY() < top) {
        top = points[i].GetY();
      }

      if (points[i].GetY() > bottom) {
        bottom = points[i].GetY();
      }

      if (points[i].GetX() < left) {
        left = points[i].GetX();
      }

      if (points[i].GetX() > right) {
        right = points[i].GetX();
      }
    }

    for (int pixelY = top; pixelY < bottom; ++pixelY) {
      std::vector<float> nodeXVec;

      size_t j = points.size() - 1;

      for (size_t i = 0; i < points.size(); ++i) {
        float pointiY = points[i].GetY();
        float pointjY = points[j].GetY();

        if ((pointiY <= (float)pixelY && pointjY > (float)pixelY) ||
            (pointjY <= (float)pixelY && pointiY > (float)pixelY)) {
          float denom = pointjY - pointiY;
          if (IsEqual(denom, 0)) {
            continue;
          }

          float x =
              points[i].GetX() + (pixelY - pointiY) / (denom) *
                                     (points[j].GetX() - points[i].GetX());
          nodeXVec.push_back(x);
        }

        j = i;
      }

      std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

      for (size_t k = 0; k < nodeXVec.size(); k += 2) {
        if (nodeXVec[k] > right) {
          break;
        }

        if (nodeXVec[k + 1] > left) {
          if (nodeXVec[k] < left) {
            nodeXVec[k] = left;
          }
          if (nodeXVec[k + 1] > right) {
            nodeXVec[k + 1] = right;
          }

          // Line2D line = {Vec2D(nodeXVec[k], pixelY), Vec2D(nodeXVec[k+1],
          // pixelY)}; Draw(line, color);
          for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k + 1]; ++pixelX) {
            Draw(pixelX, pixelY, color);
          }
        }
      }
    }
  }
}
