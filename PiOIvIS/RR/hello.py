from collections import deque
import sys
import matplotlib.pyplot as plt
import networkx as nx

sys.setrecursionlimit(10**6)

class Edge:
    def __init__(self, to, rev, capacity):
        self.to = to
        self.rev = rev
        self.capacity = capacity

    def __repr__(self):
        return f"Edge(to={self.to}, capacity={self.capacity})"


class Dinic:
    def __init__(self, n):
        self.n = n
        self.graph = [[] for _ in range(n)]
        self.original_capacities = {}

    def add_edge(self, fr, to, cap):
        forward = Edge(to, len(self.graph[to]), cap)
        backward = Edge(fr, len(self.graph[fr]), 0)
        self.graph[fr].append(forward)
        self.graph[to].append(backward)
        self.original_capacities[(fr, to)] = self.original_capacities.get((fr, to), 0) + cap

    def bfs_levels(self, s, t):
        self.level = [-1] * self.n
        q = deque()
        self.level[s] = 0
        q.append(s)

        while q:
            v = q.popleft()
            for e in self.graph[v]:
                if e.capacity > 0 and self.level[e.to] < 0:
                    self.level[e.to] = self.level[v] + 1
                    q.append(e.to)
        return self.level[t] >= 0

    def dfs_flow(self, v, t, f, it):
        if v == t:
            return f
        for i in range(it[v], len(self.graph[v])):
            it[v] = i
            e = self.graph[v][i]
            if e.capacity > 0 and self.level[v] < self.level[e.to]:
                ret = self.dfs_flow(e.to, t, min(f, e.capacity), it)
                if ret > 0:
                    e.capacity -= ret
                    self.graph[e.to][e.rev].capacity += ret
                    return ret
        return 0

    def max_flow(self, s, t):
        if s == t:
            return 0
        flow = 0
        INF = 10**18
        while self.bfs_levels(s, t):
            it = [0] * self.n
            while True:
                pushed = self.dfs_flow(s, t, INF, it)
                if pushed == 0:
                    break
                flow += pushed
        return flow

    def get_flow(self, s, t):
        flow_dict = {}
        for u in range(self.n):
            for e in self.graph[u]:
                if e.capacity < self.original_capacities.get((u, e.to), 0):
                    flow = self.original_capacities.get((u, e.to), 0) - e.capacity
                    if flow > 0:
                        flow_dict[(u, e.to)] = flow
        return flow_dict

    def print_incidence_list(self):
        print("\n--- Incidence list (residual network) ---")
        for i, edges in enumerate(self.graph):
            print(f"Vertex {i}:")
            for e in edges:
                print(f"- {e.to} (cap: {e.capacity})")
        print("-----------------------------------------------")

    def visualize_graph(self, s, t, flow=None):
        G = nx.DiGraph()
        
        for i in range(self.n):
            G.add_node(i)
        
        edge_labels = {}
        for u in range(self.n):
            for e in self.graph[u]:
                if e.capacity > 0 and u != e.to:
                    G.add_edge(u, e.to)
                    orig_cap = self.original_capacities.get((u, e.to), 0)
                    if flow and (u, e.to) in flow:
                        edge_labels[(u, e.to)] = f"{flow[(u, e.to)]}/{orig_cap}"
                    else:
                        edge_labels[(u, e.to)] = f"0/{orig_cap}"
        
        plt.figure(figsize=(12, 8))
        pos = nx.spring_layout(G, k=2, iterations=50)
        
        node_colors = []
        for node in G.nodes():
            if node == s:
                node_colors.append('lightgreen')
            elif node == t:
                node_colors.append('lightcoral')
            else:
                node_colors.append('lightblue')
        
        nx.draw_networkx_nodes(G, pos, node_color=node_colors, node_size=500, alpha=0.8)
        nx.draw_networkx_edges(G, pos, edge_color='gray', arrows=True, 
                               arrowsize=20, arrowstyle='->', width=2)
        nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')
        nx.draw_networkx_edge_labels(G, pos, edge_labels, font_size=10)
        
        if flow:
            total_flow = sum(flow.values())
            plt.title(f"Maximum flow: {total_flow} (Source: {s} -> Sink: {t})", 
                      fontsize=14, fontweight='bold')
        else:
            plt.title(f"Flow graph (Source: {s} -> Sink: {t})", 
                      fontsize=14, fontweight='bold')
        
        from matplotlib.patches import Patch
        legend_elements = [
            Patch(facecolor='lightgreen', alpha=0.8, label='Source'),
            Patch(facecolor='lightcoral', alpha=0.8, label='Sink'),
            Patch(facecolor='lightblue', alpha=0.8, label='Intermediate vertex')
        ]
        plt.legend(handles=legend_elements, loc='upper right')
        
        plt.axis('off')
        plt.tight_layout()
        plt.show()
    
    def visualize_residual_network(self, s, t):
        G = nx.DiGraph()
        
        for i in range(self.n):
            G.add_node(i)
        
        edge_colors = []
        edge_labels = {}
        
        for u in range(self.n):
            for e in self.graph[u]:
                if e.capacity > 0:
                    G.add_edge(u, e.to)
                    edge_labels[(u, e.to)] = f"{e.capacity}"
                    if (u, e.to) in self.original_capacities:
                        edge_colors.append('blue')
                    else:
                        edge_colors.append('red')
        
        plt.figure(figsize=(12, 8))
        pos = nx.spring_layout(G, k=2, iterations=50)
        
        node_colors = []
        for node in G.nodes():
            if node == s:
                node_colors.append('lightgreen')
            elif node == t:
                node_colors.append('lightcoral')
            else:
                node_colors.append('lightblue')
        
        nx.draw_networkx_nodes(G, pos, node_color=node_colors, node_size=500, alpha=0.8)
        nx.draw_networkx_edges(G, pos, edge_color=edge_colors, arrows=True, 
                               arrowsize=20, arrowstyle='->', width=2)
        nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')
        nx.draw_networkx_edge_labels(G, pos, edge_labels, font_size=9)
        
        plt.title(f"Residual network (Blue - forward edges, Red - backward edges)", 
                  fontsize=12)
        plt.axis('off')
        plt.tight_layout()
        plt.show()


def load_graph_from_file(filename):
    try:
        with open(filename, 'r') as f:
            lines = f.read().strip().split('\n')
            if not lines:
                raise ValueError("Empty file")
            n, m = map(int, lines[0].split())
            s, t = map(int, lines[1].split())
            
            if len(lines) < 2 + m:
                raise ValueError(f"Insufficient lines: expected {2+m}, got {len(lines)}")
            
            dinic = Dinic(n)
            for i in range(2, 2 + m):
                u, v, c = map(int, lines[i].split())
                if u >= n or v >= n:
                    raise ValueError(f"Vertex {u} or {v} out of range 0..{n-1}")
                dinic.add_edge(u, v, c)
            return dinic, s, t
    except Exception as e:
        print(f"Error reading file: {e}")
        return None, None, None


def load_graph_from_console():
    try:
        n = int(input("Enter number of vertices: "))
        if n < 0:
            raise ValueError("Number of vertices cannot be negative")
        
        m = int(input("Enter number of edges: "))
        s = int(input("Enter source vertex: "))
        t = int(input("Enter sink vertex: "))
        
        if s >= n or t >= n:
            raise ValueError(f"Source or sink out of range 0..{n-1}")
        
        dinic = Dinic(n)
        print("Enter edges in format: from to capacity")
        for i in range(m):
            u, v, c = map(int, input(f"Edge {i+1}: ").split())
            if u >= n or v >= n:
                raise ValueError(f"Vertex {u} or {v} out of range 0..{n-1}")
            if c < 0:
                raise ValueError(f"Capacity cannot be negative: {c}")
            dinic.add_edge(u, v, c)
        return dinic, s, t
    except Exception as e:
        print(f"Input error: {e}")
        return None, None, None


def run_tests():
    # ITEM 4a: Empty graph
    print("\n" + "=" * 60)
    print("TEST 1: Empty graph (0 vertices)")
    dinic_empty = Dinic(0)
    print(f"Empty graph created: n={dinic_empty.n}")
    
    print("\n" + "=" * 60)
    print("TEST 2: Graph with one vertex")
    dinic_one = Dinic(1)
    dinic_one.add_edge(0, 0, 100)  # ITEM 4c: Self-loop
    print(f"Flow from 0 to 0: {dinic_one.max_flow(0, 0)} (expected 0)")
    dinic_one.print_incidence_list()
    
    print("\n" + "=" * 60)
    print("TEST 3: Simple graph with two vertices")
    dinic_two = Dinic(2)
    dinic_two.add_edge(0, 1, 5)
    flow = dinic_two.max_flow(0, 1)
    print(f"Flow from 0 to 1: {flow} (expected 5)")
    dinic_two.visualize_graph(0, 1, dinic_two.get_flow(0, 1))
    
    print("\n" + "=" * 60)
    print("TEST 4: Graph with multiple edges")
    dinic_multi = Dinic(2)
    dinic_multi.add_edge(0, 1, 3)
    dinic_multi.add_edge(0, 1, 4)
    flow = dinic_multi.max_flow(0, 1)
    print(f"Total flow: {flow} (expected 7)")
    dinic_multi.visualize_graph(0, 1, dinic_multi.get_flow(0, 1))


def main():
    print("Dinic's algorithm (maximum flow) — representation: incidence list")
    print("Choose graph loading method:")
    print("1. Load from file")
    print("2. Enter from console")
    print("3. Run automatic tests")
    choice = input("Your choice: ")

    if choice == "1":
        filename = input("Enter filename: ")
        dinic, s, t = load_graph_from_file(filename)
        if dinic:
            flow = dinic.max_flow(s, t)
            print(f"Maximum flow from {s} to {t}: {flow}")
            dinic.print_incidence_list()
            
            show_viz = input("Show graph visualization? (y/n): ").lower()
            if show_viz == 'y':
                dinic.visualize_graph(s, t, dinic.get_flow(s, t))
                show_residual = input("Show residual network? (y/n): ").lower()
                if show_residual == 'y':
                    dinic.visualize_residual_network(s, t)
        else:
            print("Failed to load graph.")
    elif choice == "2":
        dinic, s, t = load_graph_from_console()
        if dinic:
            flow = dinic.max_flow(s, t)
            print(f"Maximum flow from {s} to {t}: {flow}")
            dinic.print_incidence_list()
            
            show_viz = input("Show graph visualization? (y/n): ").lower()
            if show_viz == 'y':
                dinic.visualize_graph(s, t, dinic.get_flow(s, t))
                show_residual = input("Show residual network? (y/n): ").lower()
                if show_residual == 'y':
                    dinic.visualize_residual_network(s, t)
        else:
            print("Input error.")
    elif choice == "3":
        run_tests()
    else:
        print("Invalid choice, running default tests.")
        run_tests()


if __name__ == "__main__":
    main()