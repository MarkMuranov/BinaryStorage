//
// Created by Mark on 4/17/2024.
//

#pragma once

#include <fstream>

enum class BlockType : char {
    freeBlock, schemaBlock, dataBlock, tocBlock
};

constexpr size_t noNextBlock = -1;

struct BlockHeader {
    BlockType blockType = BlockType::freeBlock;
    size_t nextBlockIndex = noNextBlock;

};

constexpr size_t blockSize = 1024;
constexpr size_t payloadSize = blockSize - sizeof(BlockHeader);

struct Block {
    BlockHeader blockHeader;
    char payload[payloadSize];
};

class BlockIO {
public:
    enum class OpenMode : bool {
        open, create
    };

    BlockIO() = default;
    ~BlockIO() = default;

    bool open(const std::string& filepath, OpenMode openMode);
    bool isOpen() const { return stream.is_open(); }

    bool readBlock (Block& block, size_t blockIndex);
    bool writeBlock(Block& block, size_t blockIndex);

    size_t getBlockCount();
    size_t getBlockIndex();

private:
    std::fstream stream;
    std::string currentFilepath;

};
