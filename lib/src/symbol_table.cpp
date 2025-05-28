






// Store reaction in symboltable
    // auto A = v.add("A", 100);
    // auto B = v.add("B", 0);
    // auto C = v.add("C", 1);

// what’s the symbol table actually doing?
    // It’s a container that:
    // Stores mappings from names (std::string) to objects (Species, or pointers/references to them).
    // Lets you look up species by name later.
    // Checks for duplicates when adding (e.g., don’t allow v.add("A", 100) twice).
    // Handles failure cases:
    // Looked up symbol doesn’t exist? → throw or handle it.
    // Adding a symbol that already exists? → reject it.