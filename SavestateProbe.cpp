#include "SavestateProbe.h"

ChunkProbe* SavestateProbe::GetChunk(ChunkType type) {
    if (chunkMap.find(type) == chunkMap.end())
        chunkMap.insert(std::pair<ChunkType, ChunkProbe>(type, ChunkProbe()));
    else {
        error = true;
        return nullptr;
    }

    return &(chunkMap[type]);
}

bool SavestateProbe::HasError() const { return error; }

const SavestateProbe::chunkMapT& SavestateProbe::GetChunkMap() const { return chunkMap; }

void SavestateProbe::NotifyError() { error = true; }
