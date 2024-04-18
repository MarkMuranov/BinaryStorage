#include <iostream>
#include "Storage.h"
#include "Schema.h"

int main() {
    Storage storage;
    const bool isOpen = storage.create("temp/test.db");
    std::cout << "isOpen: " << (isOpen ? "true" : "false") << "\n";

    Schema schema;
    storage.store(schema);
    storage.load(schema);

    return 0;
}
