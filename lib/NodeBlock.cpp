#include "NodeBlock.h"

#include <iostream>
#include <sstream>
#include <vector>

bool NodeBlock::isInUse() { return false; }

void NodeBlock::save(std::fstream* cursor) {
    cursor->seekp(this->addr);
    cursor->write(&(this->usage), sizeof(this->usage));
    cursor->write(reinterpret_cast<char*>(&(this->edgeRef)), sizeof(this->edgeRef));
    cursor->write(reinterpret_cast<char*>(&(this->propRef)), sizeof(this->propRef));
}

const int NodeBlock::BLOCK_SIZE = 15;