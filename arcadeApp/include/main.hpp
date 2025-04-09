#pragma once

#include <SDL2/SDL.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

const static int SCREEN_H = 288;
const static int SCREEN_W = 224;
const static int MAGNIFICATION = 2;

void setPixel(SDL_Surface *surface, uint32_t color, int x, int y);
size_t getIndex(SDL_Surface *surface, int row, int col);
