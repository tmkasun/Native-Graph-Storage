#include <cstring>
#include <fstream>
#include <set>
#include <string>

#ifndef NODE_BLOCK
#define NODE_BLOCK

class NodeBlock {
   private:
    unsigned int addr;
    std::string id;               // Node ID for this block
    static const int BLOCK_SIZE;  // Size of a node block in bytes

   public:
    char usage;
    char label[6];
    unsigned int edgeRef;
    unsigned int propRef;

    NodeBlock(std::string id, unsigned int index) {
        this->id = id;
        this->addr = index * BLOCK_SIZE;
        this->usage = true;
        if (sizeof(id) <= sizeof(label)) {
            std::strcpy(this->label, id.c_str());
        }
        this->edgeRef = 0;
        this->propRef = 0;
    };

    void save(std::fstream* cursor);
    bool isInUse();
    std::set<int> getEdges();
    std::set<int> getProps();
    int getFlags();

    static NodeBlock get(int nodeID);

};

#endif