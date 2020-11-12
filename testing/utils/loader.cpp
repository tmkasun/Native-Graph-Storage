#ifndef DATA_LOADER
#define DATA_LOADER

// #include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../../lib/internal/JasmineGraphIncrementalStore.h"
#include "../../lib/internal/NodeManager.h"
#include "spdlog/spdlog.h"

class Loader {
   private:
    /* data */
   public:
    static long loadGraph(std::string filePath, NodeManager *nm, int limit) {
        std::ifstream sampleDataFile(filePath);

        std::string edge;
        long numberOfLines = 0;
        while (getline(sampleDataFile, edge) && numberOfLines != limit) {
            std::vector<std::string> v = JasmineGraphIncrementalStore::_split(edge, '\t');
            spdlog::debug("Vertext 1 = {}", stoi(v[0]));
            spdlog::debug("Vertext 2 = {}", stoi(v[1]));
            std::pair<int, int> edgeP = {stoi(v[0]), stoi(v[1])};
            spdlog::debug("{} edge => {}", numberOfLines, edge);

            nm->addEdge(edgeP);
            numberOfLines++;
        }
        spdlog::debug("Number of lines read = {}", numberOfLines);

        sampleDataFile.close();
        return numberOfLines;
    }

    static long loadProperties(std::string filePath, NodeManager *nm, int limit) {
        std::ifstream coraFeatures(filePath);
        std::string nodeProps;
        long numberOfLines = 0;
        while (getline(coraFeatures, nodeProps) && numberOfLines != limit) {
            std::vector<std::string> v = JasmineGraphIncrementalStore::_split(nodeProps, '\t');
            std::string nodeLabel = v[0];
            std::string nodeClassification = v[v.size() - 1];

            char features[180] = {0};
            std::vector<std::string>::iterator it;  // declare an iterator to a vector of strings
            int count = 0;
            for (it = v.begin() + 1; it != v.end() - 1; ++it) {
                if (*it == "1") {
                    features[count / 8] |= 1 << count % 8;
                }
                count += 1;
            }
            NodeBlock *nodeBlock = nm->get(nodeLabel);
            if (nodeBlock) {
                unsigned int ad = nodeBlock->addr;
                nodeBlock->addProperty("features", &features[0]);
            } else {
                spdlog::warn("Warning: Node ({}) not found in the DB", nodeLabel);
            }

            delete nodeBlock;
            numberOfLines++;
        }
        coraFeatures.close();
        return numberOfLines;
    }
    static char *flagsToArray(char *features) {
        long checkSum = 0; // very vouge checkSum, doesn't garentee the intergrity of the data 
        char *featureStates = (char *)malloc(PropertyLink::MAX_VALUE_SIZE * 8);
        long featuresCount = 0;
        for (size_t i = 0; i < PropertyLink::MAX_VALUE_SIZE; i++) {
            char c = features[i];
            for (size_t j = 0; j < 8; j++) {
                bool bit = c & 0x1;
                featureStates[featuresCount] = bit;
                featuresCount++;
                if (bit) {
                    std::cout << "1";
                    checkSum++;
                } else {
                    std::cout << "0";
                }
                c = c >> 1;
            }
        }
        spdlog::info("checksum = {}", checkSum);

        return featureStates;
    }
    static void assertFeatures(std::string expected, char *current) {
        std::vector<std::string> featuresRow = JasmineGraphIncrementalStore::_split(expected, '\t');
        std::vector<std::string>::iterator it;  // declare an iterator to a vector of strings
        long index = 0;
        for (it = featuresRow.begin() + 1; it != featuresRow.end() - 1; ++it) {
            bool originalFeature = false;
            if (*it == "1") {
                originalFeature = true;
            }
            char symbole = (current[index]) ? '1' : '0';
            spdlog::debug("Original = {} from DB = {}", *it, symbole);

            if (!(originalFeature == current[index])) {
                Loader::flagsToArray(current);
                throw "Mismatch in feature flag from DB vs raw data !!";
            }
            index++;
        }
    }
};

#endif