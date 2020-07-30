#include <cstring>
#include <fstream>
#include <set>
#include <string>

#ifndef NODE_BLOCK
#define NODE_BLOCK

class NodeBlock {
   private:
    unsigned int addr;
    std::string id;  // Node ID for this block

   public:
    char usage;
    char label[6] = {0}; // Initialize with null chars
    unsigned int edgeRef;
    unsigned int propRef;

    static const unsigned long BLOCK_SIZE;  // Size of a node block in bytes

    NodeBlock(std::string id, unsigned int index) {
        this->id = id;
        this->addr = index * BLOCK_SIZE;
        this->usage = true;
        if (id.length() <= sizeof(label)) {
            std::strcpy(this->label, id.c_str());
        }
        this->edgeRef = 50505050;
        this->propRef = 20202020;
    };

    NodeBlock(unsigned int index, unsigned int edgeRef, unsigned int propRef, char label[], bool usage) {
        this->id = id;
        this->addr = index * BLOCK_SIZE;
        this->usage = usage;
        this->edgeRef = edgeRef;
        this->propRef = propRef;
        strcpy(this->label, label);
    };

    void save(std::fstream *cursor);
    std::string getLabel();
    bool isInUse();
    std::set<int> getEdges();
    std::set<int> getProps();
    int getFlags();
};

#endif