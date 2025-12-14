from collections import deque
import heapq
import tkinter as tk

# ==========================================================
# MAZE SETUP
# ==========================================================
maze = [
    ["S", 0, 1, 0, 0],
    [0, 0, 0, 0, 1],
    [0, 1, 0, 1, 0],
    [1, 0, 0, 1, 0],
    [0, 0, 0, 0, "G"],
]

CELL = 60  # size of cell in pixels


# ==========================================================
# HELPERS
# ==========================================================
def find_positions(maze):
    """Find start (S) and goal (G) coordinates."""
    start = goal = None
    for i in range(len(maze)):
        for j in range(len(maze[0])):
            if maze[i][j] == "S":
                start = (i, j)
            elif maze[i][j] == "G":
                goal = (i, j)
    return start, goal


start, goal = find_positions(maze)


def get_neighbors(x, y, maze):
    """Return valid neighbor cells (up, down, left, right)."""
    moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    out = []
    for dx, dy in moves:
        nx, ny = x + dx, y + dy
        if 0 <= nx < len(maze) and 0 <= ny < len(maze[0]) and maze[nx][ny] != 1:
            out.append((nx, ny))
    return out


def heuristic(a, b):
    """Manhattan distance heuristic."""
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def build_path(visited, goal):
    """Reconstruct path from the visited dictionary (parent pointers)."""
    path = []
    cur = goal
    while cur is not None:
        path.append(cur)
        cur = visited[cur]
    return list(reversed(path))


# ==========================================================
# SEARCH ALGORITHMS (calls fixed to use x, y, maze)
# ==========================================================


def bfs(start, goal, maze):
    queue = deque([start])
    visited = {start: None}
    order = []

    while queue:
        node = queue.popleft()
        order.append(node)

        if node == goal:
            break

        for nb in get_neighbors(node[0], node[1], maze):
            if nb not in visited:
                visited[nb] = node
                queue.append(nb)

    if goal not in visited:
        return [], order, float("inf")

    path = build_path(visited, goal)
    return path, order, len(path) - 1


def dfs(start, goal, maze):
    stack = [start]
    visited = {start: None}
    order = []

    while stack:
        node = stack.pop()
        order.append(node)

        if node == goal:
            break

        for nb in get_neighbors(node[0], node[1], maze):
            if nb not in visited:
                visited[nb] = node
                stack.append(nb)

    if goal not in visited:
        return [], order, float("inf")

    path = build_path(visited, goal)
    return path, order, len(path) - 1


def greedy(start, goal, maze):
    pq = [(heuristic(start, goal), start)]
    visited = {start: None}
    order = []
    seen = set([start])

    while pq:
        _, node = heapq.heappop(pq)
        order.append(node)

        if node == goal:
            break

        for nb in get_neighbors(node[0], node[1], maze):
            if nb not in seen:
                seen.add(nb)
                visited[nb] = node
                heapq.heappush(pq, (heuristic(nb, goal), nb))

    if goal not in visited:
        return [], order, float("inf")

    path = build_path(visited, goal)
    return path, order, len(path) - 1


def a_star(start, goal, maze):
    pq = [(heuristic(start, goal), start)]
    visited = {start: None}
    order = []
    g_cost = {start: 0}

    while pq:
        _, node = heapq.heappop(pq)
        order.append(node)

        if node == goal:
            break

        for nb in get_neighbors(node[0], node[1], maze):
            new_g = g_cost[node] + 1
            if nb not in g_cost or new_g < g_cost[nb]:
                g_cost[nb] = new_g
                visited[nb] = node
                f = new_g + heuristic(nb, goal)
                heapq.heappush(pq, (f, nb))

    if goal not in visited:
        return [], order, float("inf")

    path = build_path(visited, goal)
    return path, order, g_cost[goal]


# ==========================================================
# TKINTER GUI
# ==========================================================
root = tk.Tk()
root.title("Robot Path Planning - BFS | DFS | Greedy | A*")

canvas = tk.Canvas(root, width=5 * CELL, height=5 * CELL, bg="white")
canvas.pack()

info = tk.Label(root, text="", font=("Arial", 14))
info.pack(pady=10)


def draw_grid():
    """Draw base grid with walls, start and goal."""
    canvas.delete("all")
    for i in range(5):
        for j in range(5):
            val = maze[i][j]
            color = "white"
            if val == 1:
                color = "black"
            elif val == "S":
                color = "green"
            elif val == "G":
                color = "red"

            canvas.create_rectangle(
                j * CELL,
                i * CELL,
                j * CELL + CELL,
                i * CELL + CELL,
                fill=color,
                outline="gray",
            )


def animate(order, path, cost):
    """Animate exploration (yellow) then draw final path (blue)."""
    draw_grid()

    def step(i):
        if i < len(order):
            x, y = order[i]
            if maze[x][y] not in ("S", "G"):
                canvas.create_rectangle(
                    y * CELL,
                    x * CELL,
                    y * CELL + CELL,
                    x * CELL + CELL,
                    fill="yellow",
                    outline="gray",
                )
            root.after(350, lambda: step(i + 1))
        else:
            show_path()

    def show_path():
        for x, y in path:
            if maze[x][y] not in ("S", "G"):
                canvas.create_rectangle(
                    y * CELL,
                    x * CELL,
                    y * CELL + CELL,
                    x * CELL + CELL,
                    fill="blue",
                    outline="gray",
                )
        info.config(text=f"Cost: {cost} | Explored: {len(order)} steps")

    step(0)


# ----------------------------------------------------------
# BUTTON HANDLERS
# ----------------------------------------------------------
def run_bfs():
    p, o, c = bfs(start, goal, maze)
    animate(o, p, c)


def run_dfs():
    p, o, c = dfs(start, goal, maze)
    animate(o, p, c)


def run_greedy():
    p, o, c = greedy(start, goal, maze)
    animate(o, p, c)


def run_astar():
    p, o, c = a_star(start, goal, maze)
    animate(o, p, c)


# ----------------------------------------------------------
# BUTTONS
# ----------------------------------------------------------
buttons = tk.Frame(root)
buttons.pack(pady=10)

tk.Button(buttons, text="BFS", width=12, command=run_bfs).grid(row=0, column=0)
tk.Button(buttons, text="DFS", width=12, command=run_dfs).grid(row=0, column=1)
tk.Button(buttons, text="Greedy", width=12, command=run_greedy).grid(row=0, column=2)
tk.Button(buttons, text="A*", width=12, command=run_astar).grid(row=0, column=3)

draw_grid()
root.mainloop()
