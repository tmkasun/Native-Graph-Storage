#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "NodeBlock.h"

#ifndef NODE_MANAGER
#define NODE_MANAGER

class NodeManager {
   private:
    unsigned int nextNodeIndex = 0;
    std::fstream *nodeDBT;
    int dbSize(std::string path);
    void persistNodeIndex();
    std::unordered_map<std::string, unsigned int> readNodeIndex();
    static const unsigned long INDEX_KEY_SIZE;  // Size of a index key entry in bytes

   public:
    std::string index_db_loc = "streamStore/nodes.index.db";
    std::string nodes_db_loc = "streamStore/nodes.db";

    std::unordered_map<std::string, unsigned int> nodeIndex;

    NodeManager(std::string);
    ~NodeManager() {
        delete this->nodeDBT;
    };

    void addEdge(std::pair<int, int>);
    void close();
    unsigned int addNode(std::string); // will redurn DB block address
    NodeBlock get(unsigned int nodeID);

};

#endif