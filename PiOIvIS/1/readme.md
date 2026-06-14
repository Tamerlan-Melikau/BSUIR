# Graph: adjacency matrix → incidence matrix

The program converts an **undirected graph** adjacency matrix into an incidence matrix.

## How it works

1. The user enters the size `n` of the square adjacency matrix.
2. Fills the matrix with `0` and `1` (where `1` indicates an edge between vertices).
3. The program automatically counts the number of edges.
4. Builds an incidence matrix of size `n × number_of_edges`.
5. Outputs the resulting matrix.