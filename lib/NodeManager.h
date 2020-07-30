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

   public:
    std::string index_db_loc = "streamStore/nodes.index.db";
    std::string nodes_db_loc = "streamStore/nodes.db";

    std::unordered_map<std::string, unsigned int> nodeIndex;

    NodeManager(std::string);
    ~NodeManager() {
        this->nodeDBT->flush();
        this->nodeDBT->close();
        delete this->nodeDBT;
    };

    void addEdge(std::pair<int, int>);
    unsigned int addNode(std::string); // will redurn DB block address
    NodeBlock get(unsigned int nodeID);

};

#endif