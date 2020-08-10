#include "NodeBlock.h"
#include "NodeManager.h"

#include <iostream>
#include <sstream>
#include <vector>

bool NodeBlock::isInUse() {
    return this->usage == '\1';
}

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

PropertyLink NodeBlock::insertProperty(std::pair<std::string, unsigned char[]>) {
    if (!propertyHead) {
        std::cout << "Insert new property link" << std::endl;
        std::cout << "Next prop index = " << NodeManager::nextPropertyIndex << std::endl;
        this->propertiesDB->seekp(NodeManager::nextPropertyIndex);

    }
    else {
        std::cout << "Add new property to link" << std::endl;

    }
}
const unsigned long NodeBlock::BLOCK_SIZE = 15;