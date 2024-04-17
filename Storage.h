//
// Created by Mark on 4/17/2024.
//

#pragma once

#include "BlockIO.h"
#include <fstream>
#include <string>
#include <vector>
#include <array>

class BinaryIterator;

class Storable {
    virtual void store(BinaryIterator& output) = 0;
    virtual void load (BinaryIterator& input)  = 0;
};

class Storage {
public:
    Storage() = default;
    ~Storage() = default;

    bool open(const std::string& filepath);
    bool create(const std::string& filepath);

private:
    BlockIO blockIO;

};


class BinaryIterator {
public:
    BinaryIterator() = default;

    template<typename T>
    bool write(const T& data) {
        const size_t dataSize = sizeof(T);
        const char* binaryData = reinterpret_cast<const char*>(&data);

        for (size_t i = 0; i < dataSize; ++i)
            buffer.push_back(binaryData[i]);

        return true;
    }

    template<typename T>
    T read() {
        const size_t dataSize = sizeof(T);
        T data;
        char* binaryData = reinterpret_cast<char*>(&data);

        for (size_t i = 0; i < dataSize; ++i)
            binaryData[i] = buffer[readPointer + i];

        readPointer += dataSize;
        return data;
    }

    size_t getSize() { return buffer.size(); }

private:
    std::vector<char> buffer;
    size_t readPointer = 0;

};

