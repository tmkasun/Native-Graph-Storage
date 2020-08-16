#include <cstring>
#include <fstream>
#include <set>
#include <string>

#ifndef PROPERTY_LINK
#define PROPERTY_LINK

class PropertyLink {
   private:
    unsigned int blockAddress; // contains the address of the first element in the list
    PropertyLink *next = NULL;
    
   public:
    std::string name;
    unsigned char *value;

    static const unsigned long MAX_NAME_SIZE;  // Size of a property name in bytes
    static const unsigned long MAX_VALUE_SIZE;  // Size of a property value in bytes
    static unsigned int nextPropertyIndex; // Next available property block index // unless open in wipe data mode(trunc) need to set this value to property db seekp()/BLOCK_SIZE
    static std::string DB_PATH;
    static std::fstream *propertiesDB;

    PropertyLink(unsigned int);
    PropertyLink();
    
    unsigned int insert(std::string, unsigned char[]);


};

#endif