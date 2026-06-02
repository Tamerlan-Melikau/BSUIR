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
        print("\n--- Список инцидентности (остаточная сеть) ---")
        for i, edges in enumerate(self.graph):
            print(f"Вершина {i}:")
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
            plt.title(f"Максимальный поток: {total_flow} (Исток: {s} -> Сток: {t})", 
                      fontsize=14, fontweight='bold')
        else:
            plt.title(f"Граф потока (Исток: {s} -> Сток: {t})", 
                      fontsize=14, fontweight='bold')
        
        from matplotlib.patches import Patch
        legend_elements = [
            Patch(facecolor='lightgreen', alpha=0.8, label='Исток'),
            Patch(facecolor='lightcoral', alpha=0.8, label='Сток'),
            Patch(facecolor='lightblue', alpha=0.8, label='Промежуточная вершина')
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
        
        plt.title(f"Остаточная сеть (Синие - прямые рёбра, Красные - обратные)", 
                  fontsize=12)
        plt.axis('off')
        plt.tight_layout()
        plt.show()


def load_graph_from_file(filename):
    try:
        with open(filename, 'r') as f:
            lines = f.read().strip().split('\n')
            if not lines:
                raise ValueError("Пустой файл")
            n, m = map(int, lines[0].split())
            s, t = map(int, lines[1].split())
            
            if len(lines) < 2 + m:
                raise ValueError(f"Недостаточно строк: ожидается {2+m}, получено {len(lines)}")
            
            dinic = Dinic(n)
            for i in range(2, 2 + m):
                u, v, c = map(int, lines[i].split())
                if u >= n or v >= n:
                    raise ValueError(f"Вершина {u} или {v} вне диапазона 0..{n-1}")
                dinic.add_edge(u, v, c)
            return dinic, s, t
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")
        return None, None, None


def load_graph_from_console():
    try:
        n = int(input("Введите количество вершин: "))
        if n < 0:
            raise ValueError("Количество вершин не может быть отрицательным")
        
        m = int(input("Введите количество рёбер: "))
        s = int(input("Введите номер истока: "))
        t = int(input("Введите номер стока: "))
        
        if s >= n or t >= n:
            raise ValueError(f"Исток или сток вне диапазона 0..{n-1}")
        
        dinic = Dinic(n)
        print("Введите рёбра в формате: from to capacity")
        for i in range(m):
            u, v, c = map(int, input(f"Ребро {i+1}: ").split())
            if u >= n or v >= n:
                raise ValueError(f"Вершина {u} или {v} вне диапазона 0..{n-1}")
            if c < 0:
                raise ValueError(f"Пропускная способность не может быть отрицательной: {c}")
            dinic.add_edge(u, v, c)
        return dinic, s, t
    except Exception as e:
        print(f"Ошибка ввода: {e}")
        return None, None, None


def run_tests():
    # ПУНКТ 4a: Пустой граф
    print("\n" + "=" * 60)
    print("ТЕСТ 1: Пустой граф (0 вершин)")
    dinic_empty = Dinic(0)
    print(f"Пустой граф создан: n={dinic_empty.n}")
    
    print("\n" + "=" * 60)
    print("ТЕСТ 2: Граф с одной вершиной")
    dinic_one = Dinic(1)
    dinic_one.add_edge(0, 0, 100)  # ПУНКТ 4c: Петля
    print(f"Поток из 0 в 0: {dinic_one.max_flow(0, 0)} (ожидается 0)")
    dinic_one.print_incidence_list()
    
    print("\n" + "=" * 60)
    print("ТЕСТ 3: Простой граф с двумя вершинами")
    dinic_two = Dinic(2)
    dinic_two.add_edge(0, 1, 5)
    flow = dinic_two.max_flow(0, 1)
    print(f"Поток из 0 в 1: {flow} (ожидается 5)")
    dinic_two.visualize_graph(0, 1, dinic_two.get_flow(0, 1))
    
    print("\n" + "=" * 60)
    print("ТЕСТ 4: Граф с кратными рёбрами")
    dinic_multi = Dinic(2)
    dinic_multi.add_edge(0, 1, 3)
    dinic_multi.add_edge(0, 1, 4)
    flow = dinic_multi.max_flow(0, 1)
    print(f"Суммарный поток: {flow} (ожидается 7)")
    dinic_multi.visualize_graph(0, 1, dinic_multi.get_flow(0, 1))


def main():
    print("Алгоритм Диница (максимальный поток) — представление: список инцидентности")
    print("Выберите способ загрузки графа:")
    print("1. Загрузить из файла")
    print("2. Ввести с консоли")
    print("3. Запустить автоматические тесты")
    choice = input("Ваш выбор: ")

    if choice == "1":
        filename = input("Введите имя файла: ")
        dinic, s, t = load_graph_from_file(filename)
        if dinic:
            flow = dinic.max_flow(s, t)
            print(f"Максимальный поток из {s} в {t}: {flow}")
            dinic.print_incidence_list()
            
            show_viz = input("Показать визуализацию графа? (y/n): ").lower()
            if show_viz == 'y':
                dinic.visualize_graph(s, t, dinic.get_flow(s, t))
                show_residual = input("Показать остаточную сеть? (y/n): ").lower()
                if show_residual == 'y':
                    dinic.visualize_residual_network(s, t)
        else:
            print("Не удалось загрузить граф.")
    elif choice == "2":
        dinic, s, t = load_graph_from_console()
        if dinic:
            flow = dinic.max_flow(s, t)
            print(f"Максимальный поток из {s} в {t}: {flow}")
            dinic.print_incidence_list()
            
            show_viz = input("Показать визуализацию графа? (y/n): ").lower()
            if show_viz == 'y':
                dinic.visualize_graph(s, t, dinic.get_flow(s, t))
                show_residual = input("Показать остаточную сеть? (y/n): ").lower()
                if show_residual == 'y':
                    dinic.visualize_residual_network(s, t)
        else:
            print("Ошибка ввода.")
    elif choice == "3":
        run_tests()
    else:
        print("Неверный выбор, запускаю тесты по умолчанию.")
        run_tests()


if __name__ == "__main__":
    main()