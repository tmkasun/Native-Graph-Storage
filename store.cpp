#include <sys/stat.h>

#include <fstream>
#include <iostream>

#include "lib/internal/JasmineGraphIncrementalStore.h"
#include "lib/internal/NodeManager.h"

using namespace std;
const string NODE_DB = "streamStore/nodes.db";
const string EDGE_DB = "streamStore/edges.db";

int main(int argc, const char** argv) {
    cout << "Sample store" << endl;

    // // std::pair<string, unsigned *char> test = {name, &fk};
    // return -1;
    NodeManager nm = NodeManager("trunc");
    JasmineGraphIncrementalStore sampleStore = JasmineGraphIncrementalStore(1, 1);

    ifstream sampleDataFile("graph_data/cora/cora.cites");
    string edge;
    long numberOfLines = 0;
    while (getline(sampleDataFile, edge)) {
        std::vector<std::string> v = JasmineGraphIncrementalStore::_split(edge, '\t');
        std::cout << "Vertext 1 = " << stoi(v[0]) << std::endl;
        std::cout << "Vertext 2 = " << stoi(v[1]) << std::endl;
        std::pair<int, int> edgeP = {stoi(v[0]), stoi(v[1])};
        sampleStore.addEdge(edgeP);
        std::cout << numberOfLines << " edge  => " << edge << std::endl;

        nm.addEdge(edgeP);
        numberOfLines++;
    }
    std::cout << "Number of lines read = " << numberOfLines << std::endl;
    sampleDataFile.close();

    ifstream coraFeatures("graph_data/cora/cora.content");
    string nodeProps;
    while (getline(coraFeatures, nodeProps)) {
        getline(coraFeatures, nodeProps);
        cout << nodeProps << endl;
        std::vector<std::string> v = JasmineGraphIncrementalStore::_split(nodeProps, '\t');
        string nodeLabel = v[0];
        string nodeClassification = v[v.size() - 1];

        char features[180] = {0};
        vector<string>::iterator it;  // declare an iterator to a vector of strings
        int count = 0;
        for (it = v.begin() + 1; it != v.end() - 1; ++it) {
            if (*it == "1") {
                features[count / 8] |= 1 << count % 8;
            }
            count += 1;
        }
        cout << features << endl;
        cout << count << endl;
        NodeBlock* nodeBlock = nm.get(nodeLabel);
        if (nodeBlock) {
            nodeBlock->addProperty("features", &features[0]);
        } else {
            std::cout << "Warning: Node not found in the DB!!" << std::endl;
        }

        delete nodeBlock;
    }
    coraFeatures.close();
    // NodeBlock* nodeBlock = nm.get("1106112");
    // PropertyLink* current = &(nodeBlock->properties);
    // delete nodeBlock;
    // do {
    //     cout << "Name = " << current->name << " value = " << current->value << endl;
    //     current = current->next();
    // } while (current);

    nm.close();
    return 0;
}