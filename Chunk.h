#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "EmCommon.h"

class Chunk {
   public:
    Chunk(size_t size, uint32* buffer) {}
    Chunk(Chunk&&) = default;

   private:
    Chunk() = delete;
    Chunk(const Chunk&) = delete;
    Chunk& operator=(const Chunk&) = delete;
    Chunk& operator=(Chunk&&) = delete;
};

#endif  // _CHUNK_H_
