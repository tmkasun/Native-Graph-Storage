#include <sys/stat.h>

#include <fstream>
#include <iostream>

#include "lib/JasmineGraphIncrementalStore.h"
#include "lib/NodeManager.h"

using namespace std;
const string NODE_DB = "streamStore/nodes.db";
const string EDGE_DB = "streamStore/edges.db";

string readData();
int getSize(string);
void writeData(fstream*, unsigned int);

int main(int argc, const char** argv) {
    cout << "Sample store" << endl;
    // std::cout << "Size of int " << sizeof(unsigned char) << std::endl;
    // fstream* nodeDBT = new fstream(NODE_DB, ios::in | ios::out | ios::app | ios::binary);
    // unsigned char edgeRef[8];
    // unsigned int refAd = 0xF000;
    // unsigned char* samplea;
    // samplea = reinterpret_cast<unsigned char*>(&refAd, sizeof(refAd));
    // // unsigned char* byteA = reinterpret_cast<unsigned char*> (edgeAddr);

    // edgeRef[0] = false;
    // edgeRef[1] = 95;
    // edgeRef[3] = 'A';
    // edgeRef[4] = 'F';
    // edgeRef[7] = 245;
    // writeData(nodeDBT, refAd);

    // nodeDBT->close();
    // delete nodeDBT;

    // getSize(NODE_DB);
    // readData();
    NodeManager nm = NodeManager();
    ifstream sampleDataFile("graph_data/cora/cora.cites");
    JasmineGraphIncrementalStore sampleStore = JasmineGraphIncrementalStore(1, 1);
    string edge;
    for (size_t i = 0; i < 20; i++) {
        getline(sampleDataFile, edge);
        std::vector<std::string> v = JasmineGraphIncrementalStore::_split(edge, '\t');
        std::cout << "Vertext 1 = " << stoi(v[0]) << std::endl;
        std::cout << "Vertext 2 = " << stoi(v[1]) << std::endl;
        std::pair<int,int> edgeP = {stoi(v[0]), stoi(v[1])};
        sampleStore.addEdge(edgeP);
        std::cout << i << " edge  => " << edge << std::endl;
        nm.addEdge(edgeP);
    }
    sampleDataFile.close();
    return -1;
    streampos size;
    fstream nodeDB(NODE_DB, ios::out | ios::app | ios::binary);
    fstream edgeDB(EDGE_DB, ios::out | ios::app | ios::binary);
    nodeDB << "sample node" << endl;
    size = nodeDB.tellp();
    edgeDB << "sample edge" << endl;
    nodeDB.close();
    edgeDB.close();
    return 0;
}

void writeData(fstream* cursor, unsigned int refAddr) {
    // char* edgeRef = reinterpret_cast<char*>(refAddr);
    cursor->write(reinterpret_cast<char*>(&refAddr), sizeof(refAddr));
}

int getSize(string filePath) {
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
    if (stat(filePath.c_str(), &result) == 0) {
        std::cout << "DEBUG: Size of the " << filePath << " is " << result.st_size << std::endl;
    } else {
        std::cout << "ERROR: Error while reading file stats of " << filePath << std::endl;
        return -1;
    }

    return result.st_size;
}

string readData() {
    ifstream dbData("./streamStore/nodes.db", ios::in | ios::binary);
    char data[20];
    int blockSize = 10;
    dbData.seekg(10);
    dbData.read(data, blockSize);
    if (!dbData) {
        std::cout << "Something went wrong while reading the data !!!" << std::endl;
        return "-1";
    }
    std::cout << "Read data " << data << std::endl;
    std::cout << "Now get cursor at " << dbData.tellg() << std::endl;
    return "data";
}
