#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#ifndef NODE_MANAGER
#define NODE_MANAGER

class NodeManager {
   private:
    unsigned int nextNodeIndex = 0;
    std::fstream* nodeDBT = new std::fstream("streamStore/nodes.db", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

   public:
    std::string index_db_loc = "streamStore/nodes.index.db";
    std::string nodes_db_loc = "streamStore/nodes.db";
    // typedef struct ref_id {
    //     char x[4];
    // } ref_id;

    std::unordered_map<std::string, unsigned int> nodeIndex;

    NodeManager() {
        std::ifstream index_db(index_db_loc);
        if (index_db.is_open()) {
            std::string data;
            while (getline(index_db, data)) {
                std::cout << data << '\n';
                // Read and populate nodeIndex map
            }
            index_db.close();
        }
    };

    unsigned int addEdge(std::pair<int, int> edge);
};

#endif