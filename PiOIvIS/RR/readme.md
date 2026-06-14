# Dinic's algorithm

**Dinic's algorithm** is an algorithm for finding the maximum flow in a directed graph. It runs in O(E·V²) or O(E·√V) for unit capacities.

## Key concepts

- **Maximum flow** — the maximum amount of "substance" that can be sent from the source to the sink while respecting edge capacity constraints.
- **Residual network** — a graph showing how much flow can still be pushed through each edge.
- **Blocking flow** — a flow that cannot be increased without exceeding capacity on some edge.

## How it works

1. Build a level graph using BFS
2. Find a blocking flow using DFS
3. Repeat steps 1-2 until there is no path from source to sink

## Complexity

| Case | Time complexity |
|------|-----------------|
| General case | O(V²E) |
| Unit capacities | O(min(V^(2/3), √E)·E) |
| Bipartite graphs | O(√V·E) |

## Use cases

Logistics (cargo optimization), supply chain planning, network traffic distribution, transportation network analysis, computer vision (image segmentation), task scheduling in clusters, fluid flow modeling in pipelines.