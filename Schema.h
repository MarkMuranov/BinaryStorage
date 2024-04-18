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
        auto test1 = input.read<int>();
        auto test2 = input.read<char>();
        auto test3 = input.read<float>();
        auto test4 = input.read<bool>();
        auto test5 = input.readString();
        auto test6 = input.read<int>();
        std::cout << "test\n";
    }

};