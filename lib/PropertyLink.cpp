#include "PropertyLink.h"

#include <iostream>
#include <sstream>
#include <vector>

PropertyLink::PropertyLink(unsigned int propertyBlockAddress) : blockAddress(propertyBlockAddress) {
    if (propertyBlockAddress > 0) {
        this->propertiesDB->seekg(propertyBlockAddress);
        std::string name;
        unsigned char value[PropertyLink::MAX_VALUE_SIZE];

        if (!this->propertiesDB->read(reinterpret_cast<char*>(&value), sizeof(PropertyLink::MAX_VALUE_SIZE))) {
            std::cout << "ERROR: Error while reading properties data from block " << blockAddress << std::endl;
        }

    }
};
PropertyLink::PropertyLink() : blockAddress(0){};

unsigned int PropertyLink::insert(std::string name, unsigned char* value) {
    std::cout << "DEBUG: Received name = " << name << std::endl;
    std::cout << "DEBUG: Received value = " << value << std::endl;
    unsigned long PROPERTY_BLOCK_SIZE =
        PropertyLink::MAX_NAME_SIZE + PropertyLink::MAX_VALUE_SIZE + sizeof(unsigned int);
    unsigned int nextAddress = 0;
    unsigned int headAddress;

    if (!blockAddress) { // When no links in the chain
        std::cout << "Insert new property link" << std::endl;
        std::cout << "Next prop index = " << PropertyLink::nextPropertyIndex << std::endl;
        
        headAddress = PropertyLink::nextPropertyIndex * PROPERTY_BLOCK_SIZE;
        this->propertiesDB->seekp(headAddress);
        this->propertiesDB->write(name.c_str(), PropertyLink::MAX_NAME_SIZE);
        this->propertiesDB->write(reinterpret_cast<char*>(value), PropertyLink::MAX_VALUE_SIZE);
        this->propertiesDB->write(reinterpret_cast<char*>(&nextAddress), sizeof(nextAddress));
        PropertyLink::nextPropertyIndex++;
    } else {
        std::cout << "Add new property to link" << std::endl;
    }
    return headAddress;
}

const unsigned long PropertyLink::MAX_NAME_SIZE = 12;
const unsigned long PropertyLink::MAX_VALUE_SIZE = 180;
unsigned int PropertyLink::nextPropertyIndex = 1;  // Starting with 1 because of the 0 and '\0' differentiation issue
std::string PropertyLink::DB_PATH = "streamStore/properties.db";
std::fstream* PropertyLink::propertiesDB = NULL;
