#include <cstring>
#include <fstream>
#include <set>
#include <string>

#include <iostream> // for cout
#include "PropertyLink.h"

#ifndef NODE_BLOCK
#define NODE_BLOCK

class NodeBlock {
   private:
    unsigned int addr;
    std::string id;  // Node ID for this block
    std::fstream *propertiesDB;

   public:
    char usage;
    char label[6] = {0}; // Initialize with null chars
    unsigned int edgeRef;
    unsigned int propRef;
    PropertyLink *propertyHead = NULL;

    static const unsigned long BLOCK_SIZE;  // Size of a node block in bytes

    NodeBlock(std::string id, unsigned int index) {
        this->id = id;
        this->addr = index * BLOCK_SIZE;
        this->usage = true;
        if (id.length() <= sizeof(label)) {
            std::strcpy(this->label, id.c_str());
        }
        this->edgeRef = 50505050;
        this->propRef = 0;
    };

    NodeBlock(unsigned int index, unsigned int edgeRef, unsigned int propRef, char label[], bool usage, std::fstream *propertiesDB) {
        this->id = id;
        this->addr = index * BLOCK_SIZE;
        this->usage = usage;
        this->edgeRef = edgeRef;
        this->propRef = propRef;
        this->propertiesDB = propertiesDB;
        strcpy(this->label, label);
    };

    void save(std::fstream *cursor);
    std::string getLabel();
    bool isInUse();
    std::set<int> getEdges();
    std::set<int> getProps();
    int getFlags();
    PropertyLink insertProperty(std::pair<std::string, unsigned char[]>);
};

#endif