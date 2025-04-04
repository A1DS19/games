#pragma once

#include <stdint.h>

#include <cstdint>

#include "SDL_pixels.h"

struct SDL_PixelFormat;

class Color {
  uint32_t mColor;

public:
  static const SDL_PixelFormat *mFormat;
  static void InitColorFormat(const SDL_PixelFormat *format);

  static Color Black();
  static Color White();
  static Color Blue();
  static Color Red();
  static Color Green();
  static Color Yellow();
  static Color Magenta();
  static Color Cyan();
  static Color Pink();
  static Color Orange();

  Color() : Color(0) {}
  Color(uint32_t color) : mColor(color) {}
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  inline bool operator==(const Color &c) const {
    return this->mColor == c.mColor;
  }
  inline bool operator!=(const Color &c) const { return !(*this == c); }
  inline uint32_t GetPixelColor() const { return mColor; }

  void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  void SetRed(uint8_t r);
  void SetGreen(uint8_t g);
  void SetBlue(uint8_t b);
  void SetAlpha(uint8_t a);

  uint8_t GetRed();
  uint8_t GetGreen();
  uint8_t GetBlue();
  uint8_t GetAlpha();
};
