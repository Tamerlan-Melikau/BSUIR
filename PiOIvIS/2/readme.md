# Graph: incidence matrix → adjacency matrix

The program converts an incidence matrix into an adjacency matrix for an **undirected graph**.

## How it works

1. The user enters the number of vertices and the number of edges.
2. Fills the incidence matrix (rows — vertices, columns — edges).
3. For each column (edge), finds the two vertices containing `1`.
4. Adds the edge to the adjacency matrix by placing `1` in the corresponding positions.
5. Outputs the resulting adjacency matrix.