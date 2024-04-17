//
// Created by Mark on 4/17/2024.
//

#include "Storage.h"

constexpr std::ios::openmode commonOpenMode =  std::ios::binary | std::ios::in | std::ios::out;

bool Storage::open(const std::string &filepath) {
    return blockIO.open(filepath, BlockIO::OpenMode::open);
}

bool Storage::create(const std::string &filepath) {
    return blockIO.open(filepath, BlockIO::OpenMode::create);
}

