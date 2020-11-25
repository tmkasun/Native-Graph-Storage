# Native Graph Database

This is a native graph storage/database library implemented in C++. Main goal of this graph storage is to support streaming graph data and high performance graph operations. To cater the these requirement, We(JasmineGraph team) build this **native** streaming graph storage system. And with all we try to make the implementation simple as possible. 

This repository contains only the C++ modules for graph storage system (core Graph store) and there is a Graph Storage system implemented using this core modules in [this repository](https://github.com/tmkasun/streaming_graph_partitioning)


# Architecture

We treat fundamental graph structural elements as first class citizens in the storage system. The Nodes/Vertices, Relations/Edges and their properties have their own storage implementations.
Each of those storage engines are optimized to have low storage fragmentation and fast data insertion/retrieval.

## Nodes/Vertices

Nodes or Vertices in the graph are stored in 
```
<ROOT>/streamStore/nodes.db
```
A node should have an identifier, and in the implementation it can be any string value with not exceeding the length of a value in properties store.
example for node IDs:

- e-mail address (tmkasun@sample.com)
- UUID (abb086aa-8010-420c-8987-a07ba185df12)
- account number (778205432131)
- and more . . . 

A record in this storage has following data structure

![node_structure](https://user-images.githubusercontent.com/3313885/99763010-c8561f80-2b1f-11eb-9f4f-490a3d86738f.png)

A `Node Block` records is a reference holder for a node/vertex record. It has two references for Node properties and Node relations. These references are pointing to a block address in the respective Relations and Properties store.

And also, A `Node Block` record contains `node_label` attribute. But this will hold a value iff the length of the label is less than 6 characters. If it's larger than 6 characters, It gets stored in the properties store.

## Property Block


Both Node/Vertex properties and Relation/Edge properties are stored in 
```
<ROOT>/streamStore/properties.db
```

file in binary format.

A `PropertyBlock` has following data structure in the disk.


![property](https://user-images.githubusercontent.com/3313885/99763008-c7bd8900-2b1f-11eb-9d4d-0874a745c755.png)


A property link has a reference from a `NodeBlock` as below.


![node_prop_relation](https://user-images.githubusercontent.com/3313885/99763013-c8eeb600-2b1f-11eb-81b1-12e6145e532c.png)

Following is a sample graphical view of the properties single link list.

![property_link](https://user-images.githubusercontent.com/3313885/99763027-d0ae5a80-2b1f-11eb-9dc9-0a42da6294c2.png)


## Relations Block


Relations in the graph are stored in 
```
<ROOT>/streamStore/relations.db
```

A `Relation Block` has following data structure in the disk.

![relation_block](https://user-images.githubusercontent.com/3313885/99762989-bc6a5d80-2b1f-11eb-8a18-f08f15f800c4.png)


## Nodes Index

Node index is a lookup table for locating node id and it's relevent block index in the nodes DB


Node index of the graph is stored in 
```
<ROOT>/streamStore/relations.db
```

## Node Manager

We have defined a `NodeManager.h` to integrate and manage all the above Nodes,Properties and Relation data stores. You need to initialize a `NodeManager` instance to do any interactions with Graph storage. 

Basic implementation was inspired by the Neo4J storage architecture[1]. But there are some extensions and additions we have made to support handling streaming graph data.


# Dependencies

# Tests

# References

1. [1]: https://neo4j.com/graph-databases-book/
