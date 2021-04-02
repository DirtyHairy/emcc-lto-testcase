#include "Savestate.h"

Chunk* Savestate::GetChunk(ChunkType type) {
    if (!buffer) {
        return nullptr;
    }

    if (chunkMap.find(type) == chunkMap.end()) {
        return nullptr;
    }

    Chunk& chunk = chunkMap.at(type);

    error = error || chunk.HasError();
    chunk.Reset();

    return &chunk;
}

void Savestate::NotifyError() { error = true; }

void Savestate::Reset() {
    buffer.reset();
    size = 0;
    error = false;
    chunkMap.clear();
}
