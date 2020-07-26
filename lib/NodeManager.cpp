#include <string>
#include "NodeManager.h"
#include "NodeBlock.h"

unsigned int NodeManager::addEdge(std::pair<int, int> edge){
    std::string sourceId = std::to_string(edge.first);
    std::string destinationId = std::to_string(edge.second);

    // Store source node 
    if(this->nodeIndex.find(sourceId) == this->nodeIndex.end()){
        std::cout << "DEBUG: SourceID not found in index " << sourceId << std::endl;
        NodeBlock sourceBlk = NodeBlock(sourceId, this->nextNodeIndex);
        this->nodeIndex.insert({sourceId,this->nextNodeIndex});
        this->nextNodeIndex++;
        sourceBlk.save(this->nodeDBT);
    } else
    {
        std::cout << "DEBUG: Found nodeIndex for sourceId " << sourceId << " at " << this->nodeIndex.at(sourceId) << std::endl;
    }

    // Store destination node 
    if(this->nodeIndex.find(destinationId) == this->nodeIndex.end()){
        std::cout << "DEBUG: destinationId not found in index " << destinationId << std::endl;
        NodeBlock destinationBlk = NodeBlock(destinationId, this->nextNodeIndex);
        this->nodeIndex.insert({destinationId,this->nextNodeIndex});
        this->nextNodeIndex++;
        destinationBlk.save(this->nodeDBT);
    } else
    {
        std::cout << "DEBUG: Found nodeIndex for destinationId " << destinationId << " at " << this->nodeIndex.at(destinationId) << std::endl;
    }
    

}