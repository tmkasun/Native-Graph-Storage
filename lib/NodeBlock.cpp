#include "NodeBlock.h"

#include <iostream>
#include <sstream>
#include <vector>

bool NodeBlock::isInUse() { return this->usage == '\1'; }

std::string NodeBlock::getLabel() {
    return std::string(this->label);
}

void NodeBlock::save(std::fstream* cursor) {
    cursor->seekp(this->addr);
    cursor->put(this->usage);
    cursor->write(reinterpret_cast<char*>(&(this->edgeRef)), sizeof(this->edgeRef));
    cursor->write(reinterpret_cast<char*>(&(this->propRef)), sizeof(this->propRef));
    cursor->write(this->label, sizeof(this->label));
    cursor->flush();  // Sync the file with in-memory stream
}

const unsigned long NodeBlock::BLOCK_SIZE = 15;