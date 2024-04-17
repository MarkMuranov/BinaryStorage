#include <iostream>
#include "Storage.h"

int main() {
    Storage blockStorage;
    const bool isOpen = blockStorage.create("temp/test.db");
    std::cout << "isOpen: " << (isOpen ? "true" : "false") << "\n";

    auto binaryIterator = BinaryIterator();
    binaryIterator.write(42);
    binaryIterator.write('a');
    binaryIterator.write(3.14f);

    std::cout << "Reading: "
        << binaryIterator.read<int>() << ", "
        << binaryIterator.read<char>() << ", "
        << binaryIterator.read<float>() << "\n";



    return 0;
}
