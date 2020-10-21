#include "RelationBlock.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "NodeManager.h"

RelationBlock* RelationBlock::add(NodeBlock source, NodeBlock destination) {
    int RECORD_SIZE = sizeof(unsigned int);

    NodeRelation sourceData;
    NodeRelation destinationData;

    sourceData.address = source.addr;
    destinationData.address = destination.addr;

    unsigned int relationPropAddr = 0;

    long relationBlockAddress = RelationBlock::nextRelationIndex * RelationBlock::BLOCK_SIZE;
    RelationBlock::relationsDB->seekg(relationBlockAddress);

    RelationBlock::relationsDB->write(reinterpret_cast<char*>(&sourceData.address), RECORD_SIZE);
    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&destinationData.address), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << destinationData.address
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&sourceData.nextRelationId), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << sourceData.nextRelationId
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&sourceData.nextPid), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << sourceData.nextPid
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&sourceData.preRelationId), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << sourceData.preRelationId
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&sourceData.prePid), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << sourceData.prePid
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }
    
    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&destinationData.nextRelationId), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << destinationData.nextRelationId
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&destinationData.nextPid), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << destinationData.nextPid
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&destinationData.preRelationId), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << destinationData.preRelationId
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&destinationData.prePid), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << destinationData.prePid
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&relationPropAddr), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << relationPropAddr
                  << " into relation block address " << relationBlockAddress << std::endl;
        return NULL;
    }

    RelationBlock::nextRelationIndex += 1;
    RelationBlock::relationsDB->flush();
    return new RelationBlock(relationBlockAddress, sourceData, destinationData, relationPropAddr);
}

RelationBlock* RelationBlock::get(unsigned int address) {
    int RECORD_SIZE = sizeof(unsigned int);
    RelationBlock* relationDataBlock = NULL;
    if (address == 0) {
        return relationDataBlock;
    }

    RelationBlock::relationsDB->seekg(address);
    NodeRelation source;
    NodeRelation destination;
    unsigned int propertyReference;

    RelationBlock::relationsDB->read(reinterpret_cast<char*>(&source.address),
                                     RECORD_SIZE);  // < ------ relation data offset ID = 0
    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&destination.address),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 1
        std::cout << "ERROR: Error while writing relation destAddr " << destination.address
                  << " into relation block address " << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&source.nextRelationId),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 2
        std::cout << "ERROR: Error while writing relation destAddr " << source.nextRelationId
                  << " into relation block address " << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&source.nextPid),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 3
        std::cout << "ERROR: Error while writing relation destAddr " << source.nextPid
                  << " into relation block address " << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&source.preRelationId),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 4
        std::cout << "ERROR: Error while writing relation destAddr " << source.preRelationId
                  << " into relation block address " << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&source.prePid),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 5
        std::cout << "ERROR: Error while writing relation destAddr " << source.prePid << " into relation block address "
                  << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&destination.nextRelationId),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 6
        std::cout << "ERROR: Error while writing relation destAddr " << destination.nextRelationId
                  << " into relation block address " << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&destination.nextPid),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 7
        std::cout << "ERROR: Error while writing relation destAddr " << destination.nextPid << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&destination.preRelationId),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 8
        std::cout << "ERROR: Error while writing relation destAddr " << destination.preRelationId
                  << " into relation block address " << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&destination.prePid),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 9
        std::cout << "ERROR: Error while writing relation destAddr " << destination.prePid
                  << " into relation block address " << address << std::endl;
        return NULL;
    }

    if (!RelationBlock::relationsDB->read(reinterpret_cast<char*>(&propertyReference),
                                          RECORD_SIZE)) {  // < ------ relation data offset ID = 10
        std::cout << "ERROR: Error while writing relation destAddr " << propertyReference << std::endl;
        return NULL;
    }

    return new RelationBlock(address, source, destination, propertyReference);
}

bool RelationBlock::updateSourceNextRelAddr(unsigned int newAddress) {
    return this->updateRelationRecords(2, newAddress);
}

bool RelationBlock::updateDestinationNextRelAddr(unsigned int newAddress) {
    return this->updateRelationRecords(6, newAddress);
}

bool RelationBlock::updateRelationRecords(int recordOffset, unsigned int data) {
    int dataOffset = RECORD_SIZE * recordOffset;

    RelationBlock::relationsDB->seekg(this->addr + dataOffset);

    if (!RelationBlock::relationsDB->write(reinterpret_cast<char*>(&data), RECORD_SIZE)) {
        std::cout << "ERROR: Error while writing relation destAddr " << this->addr << " into relation block address "
                  << this->addr << std::endl;
        return false;
    }
    RelationBlock::relationsDB->flush();
    return true;
}

bool RelationBlock::isInUse() { return this->usage == '\1'; }
unsigned int RelationBlock::nextRelationIndex = 1;  // Starting with 1 because of the 0 and '\0' differentiation issue

const unsigned long RelationBlock::BLOCK_SIZE = 11 * 8;
std::string RelationBlock::DB_PATH = "streamStore/relations.db";
std::fstream* RelationBlock::relationsDB = NULL;