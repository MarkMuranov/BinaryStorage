//
// Created by Mark Muranov on 4/17/24.
//

#pragma once

#include "Storage.h"

class Schema : public Storable {
public:
    void store(BinaryBuffer& output) override {
        output.write(42);
        output.write('a');
        output.write(3.14f);
        output.write(false);
        output.writeString("hello world!");
        output.write(1337);
    }
    void load(BinaryBuffer& input) override {
        std::cout << "Schema load: "
            << input.read<int>() << ", "
            << input.read<char>() << ", "
            << input.read<float>() << ", "
            << input.read<bool>() << ", "
            << input.readString() << ", "
            << input.read<int>() << "\n";
    }

};