#include <iostream>

#include "Chunk.h"
#include "ChunkHelper.h"
#include "EmCommon.h"
#include "Savestate.h"

struct MockCpu68k {
    uint32 x{0};
    int16 y{0};
    double z{0};
    string str{"hello world"};

    template <typename T>
    void Save(T& savestate) {
        typename T::chunkT* chunk = savestate.GetChunk(ChunkType::cpu68k);
        if (!chunk) return;

        SaveChunkHelper helper(*chunk);
        DoSaveLoad(helper);
    }

    template <typename T>
    void DoSaveLoad(T& helper) {
        helper.Do32(x).Do16(y).DoString(str, 15).DoDouble(z);
    }

    bool operator==(const MockCpu68k other) const {
        return (x == other.x) && (y == other.y) && (z == other.z) && (str == other.str);
    }
};

struct MockRegsEZ {
    uint8 x{0};
    uint8 y{0};
    uint8 z{0};
    bool b1{false}, b2{true};

    template <typename T>
    void Save(T& savestate) {
        typename T::chunkT* chunk = savestate.GetChunk(ChunkType::regsEZ);
        if (!chunk) return;

        SaveChunkHelper helper(*chunk);
        DoSaveLoad(helper);
    }

    template <typename T>
    void DoSaveLoad(T& helper) {
        helper.Do(typename T::Pack8() << x << y << z).Do(typename T::BoolPack() << b1 << b2);
    }

    bool operator==(const MockRegsEZ other) const {
        return (x == other.x) && (y == other.y) && (z == other.z) && (b1 == other.b1) &&
               (b2 == other.b2);
    }
};

struct MockRoot {
    MockCpu68k cpu68k;
    MockRegsEZ regsEZ;

    template <typename T>
    void Save(T& savestate) {
        cpu68k.Save(savestate);
        regsEZ.Save(savestate);
    }
};

int main() {
    MockRegsEZ regsEZ{1, 55, 66, true};
    MockCpu68k cpu68k{0x12345678, -17, 3.5};
    MockRoot root{cpu68k, regsEZ};

    Savestate savestate;
    savestate.Save(root);
}
