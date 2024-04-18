//
// Created by Mark on 4/17/2024.
//

#include "Storage.h"
#include <cstring>

constexpr std::ios::openmode commonOpenMode =  std::ios::binary | std::ios::in | std::ios::out;

bool Storage::open(const std::string &filepath) {
    return blockIO.open(filepath, BlockIO::OpenMode::open);
}

bool Storage::create(const std::string &filepath) {
    return blockIO.open(filepath, BlockIO::OpenMode::create);
}

void Storage::store(Storable &storable) {
    BinaryBuffer binaryBuffer;
    storable.store(binaryBuffer);

    Block block;
    std::memcpy(block.payload, binaryBuffer.getBuffer().data(), binaryBuffer.getSize());
    blockIO.writeBlock(block, 0);
}

void Storage::load(Storable &storable) {
    BinaryBuffer binaryBuffer;

    Block block;
    blockIO.readBlock(block, 0);
    binaryBuffer.getBuffer().resize(blockSize);
    std::memcpy(binaryBuffer.getBuffer().data(), block.payload, binaryBuffer.getSize());

    storable.load(binaryBuffer);
}
