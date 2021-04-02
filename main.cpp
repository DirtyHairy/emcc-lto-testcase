#include <iostream>

#include "Chunk.h"
#include "EmCommon.h"
#include "Savestate.h"

struct MockCpu68k {
    template <typename T>
    void Save(T& savestate) {
        typename T::chunkT* chunk = savestate.GetChunk(ChunkType::cpu68k);
        if (!chunk) return;
    }
};

struct MockRoot {
    MockCpu68k cpu68k;

    template <typename T>
    void Save(T& savestate) {
        cpu68k.Save(savestate);
    }
};

int main() {
    MockCpu68k cpu68k;
    MockRoot root{cpu68k};

    Savestate savestate;
    savestate.Save(root);
}
