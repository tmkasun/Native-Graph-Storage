# Native Graph Database

This is a native graph storage/database library implemented in C++. Main goal of this graph storage is to support streaming graph data and high performance graph operations. To cater the these requirement, We(JasmineGraph team) build this **native** streaming graph storage system.

This repository contains only the C++ modules for graph storage system (core Graph store) and there is a Graph Storage system implemented using this core modules in [this repository](https://github.com/tmkasun/streaming_graph_partitioning)


# Architecture

We treat fundamental graph structural elements as first class citizens in the storage system. The Nodes/Vertices, Relations/Edges and their properties have their own storage implementations.
Each of those storage engines are optimized to have low storage fragmentation and fast data insertion/retrieval.

## Nodes/Vertices

Nodes or Vertices in the graph are stored in 
```
<ROOT>/streamStore/nodes.db
```

A record in this storage has following data structure



Basic implementation was inspired by the Neo4J storage architecture[1]. But there are some extensions and additions we have made to support handling streaming graph data.


# Dependencies

# Tests

# References

1. [1]: https://neo4j.com/graph-databases-book/