import tkinter as tk
from tkinter import ttk, messagebox
import heapq

# Dijkstra Algorithm
def dijkstra(graph, start, end):
    pq = [(0, start, [])]
    visited = set()
    while pq:
        dist, node, path = heapq.heappop(pq)
        if node in visited:
            continue
        visited.add(node)
        path = path + [node]
        if node == end:
            return dist, path
        for neigh, w in graph.get(node, []):
            if neigh not in visited:
                heapq.heappush(pq, (dist+w, neigh, path))
    return float("inf"), []

class MapApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Delivery Route Planner (Clickable Map)")

        self.graph = {}
        self.node_pos = {}
        self.node_radius = 8

        self.canvas = tk.Canvas(root, width=600, height=450, bg="white")
        self.canvas.grid(row=0, column=0, columnspan=4, pady=5)
        self.canvas.bind("<Button-1>", self.place_node)

        ttk.Label(root, text="Point A").grid(row=1, column=0)
        ttk.Label(root, text="Point B").grid(row=1, column=1)
        ttk.Label(root, text="Dist").grid(row=1, column=2)

        self.A = ttk.Entry(root); self.B = ttk.Entry(root); self.D = ttk.Entry(root)
        self.A.grid(row=2, column=0); self.B.grid(row=2, column=1); self.D.grid(row=2, column=2)
        ttk.Button(root, text="Add Road", command=self.add_edge).grid(row=2, column=3)

        ttk.Label(root, text="Start").grid(row=3, column=0)
        ttk.Label(root, text="End").grid(row=3, column=1)
        self.start = ttk.Entry(root); self.end = ttk.Entry(root)
        self.start.grid(row=4, column=0); self.end.grid(row=4, column=1)
        ttk.Button(root, text="Find Path", command=self.find_path).grid(row=4, column=3)

        self.output = tk.Text(root, width=60, height=6)
        self.output.grid(row=5, columnspan=4, pady=8)

        self.node_count = 0

    def place_node(self, event):
        x, y = event.x, event.y
        node_name = f"N{self.node_count+1}"
        self.node_pos[node_name] = (x, y)
        self.graph[node_name] = []
        self.node_count += 1

        self.canvas.create_oval(x-8, y-8, x+8, y+8, fill="black")
        self.canvas.create_text(x, y-15, text=node_name)
        messagebox.showinfo("Node Added", f"Node {node_name} placed at ({x},{y})")

    def add_edge(self):
        try:
            a = self.A.get(); b = self.B.get(); d = int(self.D.get())
            if a not in self.graph or b not in self.graph:
                messagebox.showerror("Error", "Invalid nodes. Click map to add nodes first.")
                return

            self.graph[a].append((b, d))
            self.graph[b].append((a, d))

            ax, ay = self.node_pos[a]; bx, by = self.node_pos[b]
            self.canvas.create_line(ax, ay, bx, by, arrow=tk.LAST)
            mx, my = (ax+bx)//2, (ay+by)//2
            self.canvas.create_text(mx, my, text=str(d), fill="red")

            self.A.delete(0, tk.END); self.B.delete(0, tk.END); self.D.delete(0, tk.END)
        except:
            messagebox.showerror("Error", "Invalid input")

    def find_path(self):
        start = self.start.get(); end = self.end.get()
        dist, path = dijkstra(self.graph, start, end)
        self.output.delete("1.0", tk.END)
        if dist == float("inf"):
            self.output.insert(tk.END, "No route found")
            return
        self.output.insert(tk.END, f"Shortest Distance: {dist}\nRoute: {' -> '.join(path)}")

if __name__ == "__main__":
    root = tk.Tk()
    MapApp(root)
    root.mainloop()
