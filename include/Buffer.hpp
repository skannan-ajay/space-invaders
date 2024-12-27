#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
namespace SpaceInvaders {
class Buffer {
public:
  Buffer() = default;

  Buffer(size_t aWidth, size_t aHeight)
      : fWidth(aWidth), fHeight(aHeight),
        fData{new uint32_t[aWidth * aHeight]} {}

  void set(uint8_t aRed, uint8_t aGreen, uint8_t aBlue) {
    auto data = RGB2Uint32(aRed, aGreen, aBlue);
    for (size_t i = 0; i != fWidth * fHeight; ++i) {
      fData[i] = data;
    }
  }

  void clear() {
    for (size_t i = 0; i != fWidth * fHeight; ++i) {
      fData[i] = 0;
    }
  }

  std::pair<std::size_t, size_t> dimensions() { return {fWidth, fHeight}; }

  uint32_t *data() { return fData; }

  ~Buffer() { delete[] fData; }

private:
  uint32_t RGB2Uint32(uint8_t aRed, uint8_t aGreen, uint8_t aBlue) {
    return static_cast<uint32_t>((aRed << 24) | (aGreen << 16) | (aBlue << 8) |
                                 255);
  }
  size_t fWidth{0};
  size_t fHeight{0};
  uint32_t *fData{nullptr};
};

} // namespace SpaceInvaders
