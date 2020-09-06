#include "NodeBlock.h"

#include <iostream>
#include <sstream>
#include <vector>

bool NodeBlock::isInUse() { return this->usage == '\1'; }

std::string NodeBlock::getLabel() { return std::string(this->label); }

void NodeBlock::save() {
    char _label[PropertyLink::MAX_VALUE_SIZE] = {0};
    std::strcpy(_label, id.c_str());

    bool isSmallLabel = id.length() <= sizeof(label);
    if (isSmallLabel) {
        std::strcpy(this->label, this->id.c_str());
    }
    NodeBlock::nodesDB->seekp(this->addr);
    NodeBlock::nodesDB->put(this->usage);
    NodeBlock::nodesDB->write(reinterpret_cast<char*>(&(this->edgeRef)), sizeof(this->edgeRef));
    NodeBlock::nodesDB->write(reinterpret_cast<char*>(&(this->propRef)), sizeof(this->propRef));
    NodeBlock::nodesDB->write(this->label, sizeof(this->label));
    NodeBlock::nodesDB->flush();  // Sync the file with in-memory stream
    if (!isSmallLabel) {
        this->addProperty("label", _label);
    }
}

void NodeBlock::addProperty(std::string name, char* value) {
    this->propRef = properties.insert(name, value);
    NodeBlock::nodesDB->seekp(this->addr + 1 + sizeof(this->edgeRef));
    NodeBlock::nodesDB->write(reinterpret_cast<char*>(&(this->propRef)), sizeof(this->propRef));
    NodeBlock::nodesDB->flush();
}

const unsigned long NodeBlock::BLOCK_SIZE = 15;
std::fstream* NodeBlock::nodesDB = NULL;