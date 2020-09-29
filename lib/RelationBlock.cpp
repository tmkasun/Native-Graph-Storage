#include "RelationBlock.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "NodeManager.h"

RelationBlock::RelationBlock(unsigned int source, unsigned int destination) {
    
}

bool RelationBlock::isInUse() { return this->usage == '\1'; }

const unsigned long RelationBlock::BLOCK_SIZE = 37;
std::string RelationBlock::DB_PATH = "streamStore/relations.db";
std::fstream* RelationBlock::relationsDB = NULL;