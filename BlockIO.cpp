//
// Created by Mark on 4/17/2024.
//

#include "BlockIO.h"

bool BlockIO::open(const std::string &filepath, BlockIO::OpenMode anOpenMode) {
    currentFilepath = filepath;

    auto openMode = std::ios::binary | std::ios::in | std::ios::out;
    if (anOpenMode == OpenMode::create)
        openMode |= std::ios::trunc;

    stream.open(filepath, openMode);
    stream.close();
    stream.open(filepath, openMode); // fstreams suck
    return isOpen();
}

bool BlockIO::readBlock(Block &block, size_t blockIndex) {
    if (blockIndex >= getBlockCount())
        return false;

    stream.clear();
    stream.seekp(static_cast<std::streamoff>(blockIndex * blockSize));
    stream.read(reinterpret_cast<char*>(&block), blockSize);
    return true;
}

bool BlockIO::writeBlock(Block &block, size_t blockIndex) {
    if (blockIndex >= getBlockCount())
        return false;

    stream.clear();
    stream.seekg(static_cast<std::streamoff>(blockIndex * blockSize));
    stream.write(reinterpret_cast<const char*>(&block), blockSize);
    return true;
}

size_t BlockIO::getBlockCount() {
    if (!stream.is_open())
        return 0;

    const auto previousPosition = stream.tellg();
    stream.seekg(0, std::ios::end);
    const auto endPosition = stream.tellg();
    stream.seekg(previousPosition);

    return (size_t)endPosition / blockSize;
}

size_t BlockIO::getBlockIndex() {
    if (!stream.is_open())
        return 0;

    return (size_t)stream.tellg() / blockSize;
}
