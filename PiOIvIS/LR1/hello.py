import igraph as ig

edges = [('A', 'B'), ('B', 'C'), ('C', 'A'), ('C', 'D'), ('D', 'E'), ('E', 'A')]
g = ig.Graph.TupleList(edges, directed=True)

print(f"Nodes: {g.vs['name']}")
print(f"Is Directed: {g.is_directed()}")

is_acyclic = g.is_dag()
print(f"Has cycles? {not is_acyclic}")

all_cycles_ids = g.simple_cycles()
named_cycles = [[g.vs[node_id]['name'] for node_id in cycle] for cycle in all_cycles_ids]

print(f"Found cycles: {named_cycles}")