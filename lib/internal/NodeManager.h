/**
Copyright 2020 JasmineGraph Team
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#include <fstream>
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
    static std::string NODE_DB_PATH;  // Size of a index key entry in bytes

   public:
    static unsigned int nextPropertyIndex; // Next available property block index // unless open in wipe data mode(trunc) need to set this value to property db seekp()/BLOCK_SIZE
    std::string index_db_loc = "streamStore/nodes.index.db";

    std::unordered_map<std::string, unsigned int> nodeIndex;

    NodeManager(std::string);
    ~NodeManager() {
        delete NodeBlock::nodesDB;
    };

    std::pair<NodeBlock, NodeBlock> addEdge(std::pair<std::string, std::string>);
    unsigned int addRelation(NodeBlock, NodeBlock);
    void close();
    NodeBlock* addNode(std::string); // will redurn DB block address
    NodeBlock* get(std::string);
    std::list<NodeBlock> getGraph(int limit = 10);

};

#endif