# Cycle detection in directed graphs (igraph)

The program builds a directed graph from an edge list and finds all simple cycles.

## How it works

1. An edge list is defined in the code (e.g., `[('A', 'B'), ('B', 'C'), ('C', 'A')]`).
2. The program builds a directed graph using the `igraph` library.
3. Checks whether the graph contains cycles using the `is_dag()` method (DAG — directed acyclic graph).
4. Finds all **simple cycles** (cycles where vertices do not repeat except the first/last) using the `simple_cycles()` method.
5. Outputs:
   - the list of graph vertices,
   - whether the graph is directed,
   - whether cycles exist,
   - all found cycles using vertex names.