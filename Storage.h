//
// Created by Mark on 4/17/2024.
//

#pragma once

#include "BlockIO.h"
#include <fstream>
#include <string>
#include <vector>
#include <array>

class BinaryBuffer;

class Storable {
public:
    virtual void store(BinaryBuffer& output) = 0;
    virtual void load (BinaryBuffer& input)  = 0;
};

class Storage {
public:
    Storage() = default;
    ~Storage() = default;

    bool open(const std::string& filepath);
    bool create(const std::string& filepath);

    void store(Storable& storable);
    void load(Storable& storable);

private:
    BlockIO blockIO;

};


class BinaryBuffer {
public:
    BinaryBuffer() = default;

    template<typename T>
    bool write(const T& data) {
        const size_t dataSize = sizeof(T);
        const char* binaryData = reinterpret_cast<const char*>(&data);

        for (size_t i = 0; i < dataSize; ++i)
            buffer.push_back(binaryData[i]);

        return true;
    }

    bool writeString(const std::string& data) {
        for (auto character : data)
            buffer.push_back(character);

        buffer.push_back('\0');
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

    std::string readString() {
        std::string data(buffer.data() + readPointer);

        readPointer += data.size() + 1;
        return data;
    }

    size_t getSize() { return buffer.size(); }
    std::vector<char>& getBuffer() { return buffer; };

private:
    std::vector<char> buffer;
    size_t readPointer = 0;

};

