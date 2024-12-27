#pragma once

#include "Buffer.hpp"
#include <GL/glew.h>

namespace SpaceInvaders {

class BufferTexture {
public:
  explicit BufferTexture(Buffer *aBuffer) {
    glGenTextures(1, &fID);
    glBindTexture(GL_TEXTURE_2D, fID);
    auto dims = aBuffer->dimensions();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, dims.first, dims.second, 0, GL_RGBA,
                 GL_UNSIGNED_INT_8_8_8_8, aBuffer->data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

private:
  GLuint fID;
};

} // namespace SpaceInvaders
