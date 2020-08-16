#include "NodeBlock.h"

#include <iostream>
#include <sstream>
#include <vector>

bool NodeBlock::isInUse() { return this->usage == '\1'; }

std::string NodeBlock::getLabel() { return std::string(this->label); }

void NodeBlock::save() {
    NodeBlock::nodesDB->seekp(this->addr);
    NodeBlock::nodesDB->put(this->usage);
    NodeBlock::nodesDB->write(reinterpret_cast<char*>(&(this->edgeRef)), sizeof(this->edgeRef));
    NodeBlock::nodesDB->write(reinterpret_cast<char*>(&(this->propRef)), sizeof(this->propRef));
    NodeBlock::nodesDB->write(this->label, sizeof(this->label));
    NodeBlock::nodesDB->flush();  // Sync the file with in-memory stream
}

void NodeBlock::addProperty(std::string name, unsigned char value[]){
    this->propRef = properties.insert(name,value);
    NodeBlock::nodesDB->seekp(this->addr + 1 + sizeof(this->edgeRef));
    NodeBlock::nodesDB->write(reinterpret_cast<char*>(&(this->propRef)), sizeof(this->propRef));
    NodeBlock::nodesDB->flush();
}

const unsigned long NodeBlock::BLOCK_SIZE = 15;
std::fstream* NodeBlock::nodesDB = NULL;