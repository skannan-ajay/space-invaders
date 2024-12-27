#pragma once

#include "Buffer.hpp"
#include <cstddef>
#include <cstdint>

namespace SpaceInvaders {
class Sprite {
public:
  enum class COLOR { RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE };
  Sprite(size_t aWidth = 10, size_t aHeight = 10,
         COLOR aColor = Sprite::COLOR::RED)
      : fWidth(aWidth), fHeight(aHeight), fColor(aColor) {}

  void setColor(COLOR aColor) { fColor = aColor; }
  void draw(Buffer *aBuffer, size_t aXPos, size_t aYPos) {
    uint32_t color = 0;
    switch (fColor) {
    case Sprite::COLOR::RED:
      color = RGB2Uint32(255, 0, 0);
    case Sprite::COLOR::GREEN:
      color = RGB2Uint32(0, 255, 0);
    case Sprite::COLOR::BLUE:
      color = RGB2Uint32(0, 0, 255);
    case Sprite::COLOR::YELLOW:
      color = RGB2Uint32(255, 255, 0);
    case Sprite::COLOR::ORANGE:
      color = RGB2Uint32(128, 128, 0);
    case Sprite::COLOR::PURPLE:
      color = RGB2Uint32(128, 0, 128);
    default:
      color = RGB2Uint32(0, 0, 0);
    }

    auto dims = aBuffer->dimensions();
    auto bufferWidth = dims.first;
    auto bufferHeight = dims.second;
    auto bufferData = aBuffer->data();

    for (size_t xi = 0; xi != fWidth; ++xi) {
      for (size_t yi = 0; yi != fHeight; ++yi) {
        auto sy = aYPos + fHeight - 1 - yi;
        auto sx = aXPos + xi;
        if (fData[yi * fWidth + xi] && sy < bufferHeight && sx < bufferWidth) {
          bufferData[sy * bufferWidth + sx] = color;
        }
      }
    }
  }

private:
  uint32_t RGB2Uint32(uint8_t aRed, uint8_t aGreen, uint8_t aBlue) {
    return static_cast<uint32_t>((aRed << 24) | (aGreen << 16) | (aBlue << 8) |
                                 255);
  }

protected:
  size_t fWidth{0};
  size_t fHeight{0};
  bool *fData{nullptr};
  COLOR fColor{Sprite::COLOR::RED};
};
} // namespace SpaceInvaders
