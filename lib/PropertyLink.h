#include <cstring>
#include <fstream>
#include <set>
#include <string>

#ifndef PROPERTY_LINK
#define PROPERTY_LINK

class PropertyLink {
   private:
    unsigned int blockAddress; // contains the address of the first element in the list
    PropertyLink *next;
    static const unsigned long BLOCK_SIZE;  // Size of a property block in bytes

   public:
    std::pair<std::string, unsigned char[180]> property; // property key ---> property value
    PropertyLink(std::pair<std::string, unsigned char[180]>);
};

#endif