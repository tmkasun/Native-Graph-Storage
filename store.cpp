#include <sys/stat.h>

#include <fstream>
#include <iostream>

#include "lib/JasmineGraphIncrementalStore.h"
#include "lib/NodeManager.h"

using namespace std;
const string NODE_DB = "streamStore/nodes.db";
const string EDGE_DB = "streamStore/edges.db";


int main(int argc, const char** argv) {
    cout << "Sample store" << endl;
    NodeManager nm = NodeManager("trunc");
    ifstream sampleDataFile("graph_data/cora/cora.cites");
    JasmineGraphIncrementalStore sampleStore = JasmineGraphIncrementalStore(1, 1);
    string edge;
    for (size_t i = 0; i < 500; i++) {
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
    NodeBlock nb3 = nm.get(200);
    return 0;
}