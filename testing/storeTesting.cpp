#include <chrono>  // For timing
#include <cstring>
#include <fstream>
#include <iostream>

#include "../lib/internal/NodeBlock.h"
#include "../util/logger/Logger.h"
#include "./utils/loader.cpp"

using namespace std;

int main(int argc, const char** argv) {
    spdlog::set_level(spdlog::level::info);

    spdlog::info("Testing streaming store . . .");
    GraphConfig gc;
    gc.graphID = 1;
    gc.partitionID = 1;
    gc.maxLabelSize = 10;
    gc.openMode = "trunk";
    NodeManager* nm = new NodeManager(gc);

    spdlog::info("Start loading cora cites graph data");
    auto t1 = std::chrono::high_resolution_clock::now();

    long loaded = Loader::loadGraph("graph_data/cora/cora.cites", nm, -1);

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    spdlog::info("Cora cites graph data loaded in {} milliseconds", duration / 1000);

    spdlog::info("Start loading cora content properties data");
    long loadedProperties = Loader::loadProperties("graph_data/cora/cora.content", nm, -1);
    auto t3 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();

    spdlog::info("Cora content properties loaded in {} milliseconds", duration2 / 1000);

    spdlog::info("Start testing on the loaded data");

    string test35 =
        "35	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	1	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	1	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	1	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	1	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	1	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	1	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	1	0	0	0	0	0	0	0	0	0	0	"
        "0	1	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	1	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	1	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	1	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	1	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	1	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	1	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	1	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	1	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	1	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "1	0	1	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	1	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	Genetic_Algorithms";

    NodeBlock* nodeBlock = nm->get("35");
    std::list<NodeBlock> edges = nodeBlock->getEdges();
    if (edges.size() != 168) {
        throw "Number of edges expected for 35 is 168 but received " + std::to_string(edges.size());
    }
    spdlog::debug("Number of edges = {}", edges.size());
    map<string, char*> allProperties = nodeBlock->getAllProperties();
    char* features35 = Loader::flagsToArray(allProperties["features"]);

    Loader::assertFeatures(test35, features35);

    string raw1050679 =
        "1050679	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	1	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	1	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	1	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	1	0	0	0	0	0	0	0	0	0	"
        "0	0	1	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	1	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	0	0	0	0	0	0	0	0	"
        "0	0	0	0	0	Genetic_Algorithms";
    NodeBlock* n1050679 = nm->get("1050679");
    std::list<NodeBlock> e1050679 = n1050679->getEdges();
    if (e1050679.size() != 4) {
        throw "Number of edges expected for 1050679 is 4 but received " + std::to_string(e1050679.size());
    }
    spdlog::debug("Number of edges 5064 = {}", e1050679.size());

    map<string, char*> p1050679 = n1050679->getAllProperties();
    char* features = Loader::flagsToArray(p1050679["features"]);
    string l1050679 = std::string(p1050679["label"]);
    if (l1050679 != "1050679") {
        throw "Label does not match with the DB record!!";
    }
    Loader::assertFeatures(raw1050679, features);
    delete n1050679;

    NodeBlock* n1114352 = nm->get("1114352");
    std::list<NodeBlock> e1114352 = n1114352->getEdges();
    if (e1114352.size() != 4) {
        throw "Number of edges expected for 1114352 is 4 but received " + std::to_string(e1114352.size());
    }
    spdlog::debug("Number of edges 1114352 = {}", e1114352.size());
    for (auto nb : e1114352) {
        std::cout << "1114352\t" << nb.id << std::endl;
        spdlog::info("1114352\t{}", nb.id);
    }

    map<string, char*> p1114352 = n1114352->getAllProperties();
    char* f1114352 = Loader::flagsToArray(p1114352["features"]);
    string l1114352 = std::string(p1114352["label"]);
    if (l1114352 != "1114352") {
        throw "Label does not match with the DB record!!";
    }
    // Loader::assertFeatures(raw1050679, features);
    delete n1114352;

    nm->close();
    delete nm;
}
