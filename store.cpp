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
    // char a[2] = {'a', 'b'};
    // a[1] |= 1 ;
    // cout << a << endl;
    // for (size_t i = 0; i < 8; i++)
    // {
    //     bool b = (a[1] >> i) & 1;
    //     cout << b;
    // }
    // // 10000110
    // // 1+32+64
    // // 97

    // return -1;
    NodeManager nm = NodeManager("trunc");
    JasmineGraphIncrementalStore sampleStore = JasmineGraphIncrementalStore(1, 1);

    ifstream sampleDataFile("graph_data/cora/cora.cites");
    string edge;
    for (size_t i = 0; i < 500; i++) {
        getline(sampleDataFile, edge);

        std::vector<std::string> v = JasmineGraphIncrementalStore::_split(edge, '\t');
        std::cout << "Vertext 1 = " << stoi(v[0]) << std::endl;
        std::cout << "Vertext 2 = " << stoi(v[1]) << std::endl;
        std::pair<int, int> edgeP ={ stoi(v[0]), stoi(v[1]) };
        sampleStore.addEdge(edgeP);
        std::cout << i << " edge  => " << edge << std::endl;

        nm.addEdge(edgeP);
    }

    sampleDataFile.close();


    ifstream coraFeatures("graph_data/cora/cora.content");
    string nodeProps;
    for (size_t i = 0; i < 10; i++)
    {
        getline(coraFeatures, nodeProps);
        cout << nodeProps << endl;
        std::vector<std::string> v = JasmineGraphIncrementalStore::_split(nodeProps, '\t');
        string nodeLabel = v[0];
        string nodeClassification = v[v.size()-1];

        unsigned char features[180] ={ 0 };
        vector<string>::iterator it;  // declare an iterator to a vector of strings
        int count = 0;
        for (it = v.begin()+1; it!=v.end()-1; ++it) {
            if (*it == "1") {
                features[count/8] |= 1 << count%8;
            }
            count += 1;
        }
        cout << features << endl;
        cout <<  count << endl;
        NodeBlock nodeBlock = nm.get(nodeLabel);
        // std::pair<std::string, unsigned char[]> property ={ "features", features };

        // nodeBlock.insertProperty(property);


    }
    coraFeatures.close();

    nm.close();
    return 0;
}