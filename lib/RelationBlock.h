#include <cstring>
#include <fstream>
#include <iostream>  // for cout
#include <set>
#include <string>

#include "PropertyLink.h"

#ifndef RELATION_BLOCK
#define RELATION_BLOCK

/**
 * Relation states
 *              Available       Not Available
 * Source           x               x
 * Destination      x               x
 *
 * **/

class RelationBlock {
   private:
    unsigned int addr;  // Block size * block ID ID for this block
    std::string id;

   public:
    RelationBlock(unsigned int, unsigned int);
    char usage;
    unsigned int startingNode;
    unsigned int endingNode;

    unsigned int startingNodeNextRelID;
    short int startingRelNextPartID;
    unsigned int startingNodePrevRelID;
    short int startingRelPrevPartID;

    unsigned int endingNodeNextRelID;
    short int endingRelNextPartID;
    unsigned int endingNodePrevRelID;
    short int endingRelPrevPartID;

    unsigned int relationPropRef;
    PropertyLink *propertyHead = NULL;

    static const unsigned long BLOCK_SIZE;  // Size of a relation record block in bytes
    static std::string DB_PATH;
    static std::fstream *relationsDB;

    void save(std::fstream *cursor);

    bool isInUse();
    int getFlags();
    PropertyLink insertProperty(std::pair<std::string, unsigned char[]>);
};

#endif