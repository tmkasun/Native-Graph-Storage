#include "NodeManager.h"

#include <sys/stat.h>


NodeManager::NodeManager(std::string mode){
    if(mode == "app") {
        this->nodeDBT = new std::fstream("streamStore/nodes.db", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
    } else if (mode == "trunc")
    {
        this->nodeDBT = new std::fstream("streamStore/nodes.db", std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
        
    }
 std::ifstream index_db(index_db_loc);
    if (index_db.is_open()) {
        std::string data;
        while (getline(index_db, data)) {
            std::cout << data << '\n';
            // Read and populate nodeIndex map
        }
        index_db.close();
    }
    if (dbSize(nodes_db_loc) % NodeBlock::BLOCK_SIZE != 0) {
        std::cout << "WARNING: " << nodes_db_loc << " might be corrupted!" << std::endl;
    }   

}

unsigned int NodeManager::addNode(std::string nodeId) {
    unsigned int assignedNodeIndex;
    if (this->nodeIndex.find(nodeId) == this->nodeIndex.end()) {
        std::cout << "DEBUG: nodeId not found in index " << nodeId << std::endl;
        NodeBlock sourceBlk = NodeBlock(nodeId, this->nextNodeIndex);
        this->nodeIndex.insert({nodeId, this->nextNodeIndex});
        assignedNodeIndex = this->nextNodeIndex;
        this->nextNodeIndex++;
        sourceBlk.save(this->nodeDBT);
    } else {
        assignedNodeIndex = this->nodeIndex.at(nodeId);
        std::cout << "DEBUG: Found nodeIndex for nodeId " << nodeId << " at " << assignedNodeIndex << std::endl;
    }
    return assignedNodeIndex;
}

void NodeManager::addEdge(std::pair<int, int> edge) {
    std::string sourceId = std::to_string(edge.first);
    std::string destinationId = std::to_string(edge.second);
    unsigned int sourceNodeAddr = this->addNode(sourceId);
    unsigned int destNodeAddr = this->addNode(destinationId);
    std::cout << "DEBUG: Source DB block address " << sourceNodeAddr << " Destination DB block address " << destNodeAddr
              << std::endl;
}

int NodeManager::dbSize(std::string path) {
    /*
        The structure stat contains at least the following members:
        st_dev     ID of device containing file
        st_ino     file serial number
        st_mode    mode of file (see below)
        st_nlink   number of links to the file
        st_uid     user ID of file
        st_gid     group ID of file
        st_rdev    device ID (if file is character or block special)
        st_size    file size in bytes (if file is a regular file)
        st_atime   time of last access
        st_mtime   time of last data modification
        st_ctime   time of last status change
        st_blksize a filesystem-specific preferred I/O block size for
                        this object.  In some filesystem types, this may
                        vary from file to file
        st_blocks  number of blocks allocated for this object
    */
    struct stat result;
    if (stat(path.c_str(), &result) == 0) {
        std::cout << "DEBUG: Size of the " << path << " is " << result.st_size << std::endl;
    } else {
        std::cout << "ERROR: Error while reading file stats of " << path << std::endl;
        return -1;
    }

    return result.st_size;
}

NodeBlock NodeManager::get(unsigned int nodeID) {
    const unsigned int blockAddress = nodeID * NodeBlock::BLOCK_SIZE;
    this->nodeDBT->seekg(blockAddress);
    unsigned int edgeRef;  // = new char [NodeBlock::BLOCK_SIZE];
    unsigned int propRef;
    char usageBlock;
    char label[6];

    if (!this->nodeDBT->get(usageBlock)) {
        std::cout << "ERROR: Error while reading usage data from block " << blockAddress << std::endl;
    }

    if (!this->nodeDBT->read(reinterpret_cast<char *>(&edgeRef), sizeof(unsigned int))) {
        std::cout << "ERROR: Error while reading edge reference data from block " << blockAddress << std::endl;
    }

    if (!this->nodeDBT->read(reinterpret_cast<char *>(&propRef), sizeof(unsigned int))) {
        std::cout << "ERROR: Error while reading prop reference data from block " << blockAddress << std::endl;
    }

    if (!this->nodeDBT->read(&label[0], 6)) {
        std::cout << "ERROR: Error while reading label data from block " << blockAddress << std::endl;
    }
    bool usage = usageBlock == '\1';
    std::cout << "Label = " << label << std::endl;
    std::cout << "Length of label = " << strlen(label) << std::endl;
    return NodeBlock(nodeID, edgeRef, propRef, label, usage);
}
