from tkinter import messagebox
from collections import deque
import heapq
import tkinter as tk
import random
from typing import List, Tuple, Optional

# ==========================================================
# TYPES
# ==========================================================
Pos = Tuple[int, int]
Maze = List[List[int | str]]

# ==========================================================
# GLOBAL STATE
# ==========================================================
ROWS, COLS = 8, 8
CELL = 60
CURRENT_CELL = CELL
WEIGHT_COLOR = "#f4b183"  # light orange
ANIMATION_DELAY = 150  # milliseconds (default)
CANVAS_SIZE = 450
MIN_CELL = 12  # prevent unreadable cells
MAX_NUMBER_GRID = 30
MIN_HEURISTIC_CELL = 20

maze: Maze = []
start: Optional[Pos] = None
goal: Optional[Pos] = None

algorithm_choice = "BFS"  # Used only in Algorithm mode
preference_choice = "Time"  # Used only in Preference mode
wall_density = 0.25  # 25%

dashboard_window = None


# ==========================================================
# GUI HELPERS
# ==========================================================
def center_window(root, width=900, height=None):
    """Center a Tkinter window on the screen."""
    root.update_idletasks()

    screen_w = root.winfo_screenwidth()
    screen_h = root.winfo_screenheight()

    if height is None:
        height = root.winfo_reqheight()

    x = (screen_w // 2) - (width // 2)
    y = (screen_h // 2) - (height // 2)

    root.geometry(f"{width}x{height}+{x}+{y}")


# ==========================================================
# SEARCH HELPERS
# ==========================================================
def run_preference_search():
    """Run all algorithms and select the best based on preference."""

    algorithms = {
        "BFS": bfs,
        "DFS": dfs,
        "Greedy": greedy,
        "A*": astar,
    }

    results = []

    for name, algo in algorithms.items():
        path, order, _ = algo()

        if not path:
            continue

        results.append(
            {
                "name": name,
                "algo": algo,
                "path": path,
                "order": order,
                "cost": compute_path_cost(path),
                "nodes": len(order),
            }
        )

    if not results:
        return None

    if preference_choice == "Time":
        return min(results, key=lambda r: r["nodes"])

    return min(results, key=lambda r: r["cost"])


def is_solvable():
    """Check if start can reach goal (BFS connectivity check)."""
    if not start or not goal:
        return False

    q = deque([start])
    visited = {start}

    while q:
        x, y = q.popleft()
        if (x, y) == goal:
            return True

        for nx, ny in get_neighbors(x, y):
            if (nx, ny) not in visited:
                visited.add((nx, ny))
                q.append((nx, ny))

    return False


def get_neighbors(x, y):
    """Return valid non-wall neighbors."""
    moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    rows = len(maze)
    cols = len(maze[0]) if rows > 0 else 0

    result = []
    for dx, dy in moves:
        nx, ny = x + dx, y + dy
        if 0 <= nx < rows and 0 <= ny < cols and maze[nx][ny] != "W":
            result.append((nx, ny))

    return result


def get_neighbors_with_cost(x, y):
    """Return neighbors with terrain cost."""
    result = []
    for nx, ny in get_neighbors(x, y):
        cost = maze[nx][ny] if isinstance(maze[nx][ny], int) else 1
        result.append((nx, ny, cost))
    return result


def heuristic(a, b):
    """Manhattan distance heuristic."""
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def heuristic_to_goal(r, c):
    """Return heuristic value from (r,c) to current goal."""
    if not goal:
        return None
    return heuristic((r, c), goal)


def build_path(parent, goal):
    """Reconstruct path from parent map."""
    path = []
    cur = goal
    while cur is not None:
        path.append(cur)
        cur = parent[cur]
    return path[::-1]


# ==========================================================
# COST UTILITIES
# ==========================================================
def compute_path_cost(path):
    """Compute true path cost using maze weights."""
    if not path:
        return float("inf")

    cost = 0
    for r, c in path[1:]:
        cost += maze[r][c] if isinstance(maze[r][c], int) else 1
    return cost


def compute_search_cost(order):
    """Compute cost of explored nodes."""
    cost = 0
    for r, c in order[1:]:  # skip start
        cost += maze[r][c] if isinstance(maze[r][c], int) else 1
    return cost


# ==========================================================
# SEARCH ALGORITHMS
# ==========================================================
def bfs():
    q = deque([start])
    parent = {start: None}
    order = []

    while q:
        node = q.popleft()
        order.append(node)
        if node == goal:
            break

        for nb in get_neighbors(*node):
            if nb not in parent:
                parent[nb] = node
                q.append(nb)

    if goal not in parent:
        return [], order, float("inf")

    path = build_path(parent, goal)
    return path, order, len(path) - 1


def dfs():
    stack = [start]
    parent = {start: None}
    order = []

    while stack:
        node = stack.pop()
        order.append(node)
        if node == goal:
            break

        for nb in reversed(get_neighbors(*node)):
            if nb not in parent:
                parent[nb] = node
                stack.append(nb)

    if goal not in parent:
        return [], order, float("inf")

    path = build_path(parent, goal)
    return path, order, len(path) - 1


def greedy():
    pq = [(heuristic(start, goal), start)]
    parent = {start: None}
    visited = set([start])
    order = []

    while pq:
        _, node = heapq.heappop(pq)
        order.append(node)
        if node == goal:
            break

        for nx, ny, _cost in get_neighbors_with_cost(*node):
            if (nx, ny) not in visited:
                visited.add((nx, ny))
                parent[(nx, ny)] = node
                heapq.heappush(pq, (heuristic((nx, ny), goal), (nx, ny)))

    if goal not in parent:
        return [], order, float("inf")

    path = build_path(parent, goal)
    return path, order, len(path) - 1


def astar():
    """Standard A* search."""
    pq = [(heuristic(start, goal), 0, start)]
    parent = {start: None}
    g_cost = {start: 0}
    order = []

    while pq:
        _, _, node = heapq.heappop(pq)
        order.append(node)

        if node == goal:
            break

        for nx, ny, cost in get_neighbors_with_cost(*node):
            new_g = g_cost[node] + cost

            if (nx, ny) not in g_cost or new_g < g_cost[(nx, ny)]:
                g_cost[(nx, ny)] = new_g
                parent[(nx, ny)] = node
                f = new_g + heuristic((nx, ny), goal)
                heapq.heappush(pq, (f, new_g, (nx, ny)))

    if goal not in parent:
        return [], order, float("inf")

    path = build_path(parent, goal)
    return path, order, g_cost[goal]


# ==========================================================
# GUI ANIMATION
# ==========================================================
def animate(canvas, root, order, path, info, show_heuristic):
    canvas.delete("all")
    for i in range(len(maze)):
        for j in range(len(maze[i])):
            color = "white"
            if maze[i][j] == "W":
                color = "black"
            elif maze[i][j] == "S":
                color = "green"
            elif maze[i][j] == "G":
                color = "red"
            elif isinstance(maze[i][j], int):
                color = WEIGHT_COLOR
            canvas.create_rectangle(
                j * CURRENT_CELL,
                i * CURRENT_CELL,
                j * CURRENT_CELL + CURRENT_CELL,
                i * CURRENT_CELL + CURRENT_CELL,
                fill=color,
                outline="gray",
            )
            if isinstance(maze[i][j], int):
                canvas.create_text(
                    j * CURRENT_CELL + CURRENT_CELL // 2,
                    i * CURRENT_CELL + CURRENT_CELL // 2,
                    text=str(maze[i][j]),
                    fill="black",
                    font=("Arial", max(10, CURRENT_CELL // 3), "bold"),
                )

    def step(i):
        if i < len(order):
            x, y = order[i]
            if maze[x][y] not in ("S", "G"):
                canvas.create_rectangle(
                    y * CURRENT_CELL,
                    x * CURRENT_CELL,
                    y * CURRENT_CELL + CURRENT_CELL,
                    x * CURRENT_CELL + CURRENT_CELL,
                    fill="yellow",
                    outline="gray",
                )
            root.after(ANIMATION_DELAY, lambda: step(i + 1))
        else:
            for x, y in path:
                if maze[x][y] not in ("S", "G"):
                    canvas.create_rectangle(
                        y * CURRENT_CELL,
                        x * CURRENT_CELL,
                        y * CURRENT_CELL + CURRENT_CELL,
                        x * CURRENT_CELL + CURRENT_CELL,
                        fill="blue",
                        outline="gray",
                    )
            # --------------------
            # FINAL METRICS DISPLAY
            # --------------------
            path_length = len(path) - 1 if path else float("inf")
            path_cost = compute_path_cost(path)
            search_cost = compute_search_cost(order)
            nodes_explored = len(order)

            info.config(
                text=(
                    f"Path Length: {path_length} | "
                    f"Path Cost: {path_cost} | "
                    f"Search Cost: {search_cost} | "
                    f"Nodes Explored: {nodes_explored}"
                )
            )

            # --------------------
            # CLEAR PATH OVERLAY (keep weights visible)
            # --------------------
            def clear_path():
                canvas.delete("all")
                for i in range(len(maze)):
                    for j in range(len(maze[i])):
                        cell = maze[i][j]
                        if cell == "W":
                            color = "black"
                        elif cell == "S":
                            color = "green"
                        elif cell == "G":
                            color = "red"
                        elif isinstance(cell, int):
                            color = WEIGHT_COLOR
                        else:
                            color = "white"

                        canvas.create_rectangle(
                            j * CURRENT_CELL,
                            i * CURRENT_CELL,
                            j * CURRENT_CELL + CURRENT_CELL,
                            i * CURRENT_CELL + CURRENT_CELL,
                            fill=color,
                            outline="gray",
                        )

                        if isinstance(cell, int):
                            canvas.create_text(
                                j * CURRENT_CELL + CURRENT_CELL // 2,
                                i * CURRENT_CELL + CURRENT_CELL // 2,
                                text=str(cell),
                                fill="black",
                                font=("Arial", max(10, CURRENT_CELL // 3), "bold"),
                            )
                if show_heuristic.get():
                    for i in range(len(maze)):
                        for j in range(len(maze[i])):
                            if maze[i][j] != "W":
                                h = heuristic_to_goal(i, j)
                                if h is not None:
                                    canvas.create_text(
                                        j * CURRENT_CELL + CURRENT_CELL - 5,
                                        i * CURRENT_CELL + CURRENT_CELL - 5,
                                        text=str(h),
                                        fill="gray25",
                                        anchor="se",
                                        font=("Arial", max(8, CURRENT_CELL // 5)),
                                    )

            # clear path after 1.5 seconds
            root.after(1500, clear_path)

    step(0)


# ==========================================================
# RANDOM MAZE GENERATION WITH COSTS
# ==========================================================
def generate_random_maze():
    global maze, start, goal

    while True:
        maze = [[0 for _ in range(COLS)] for _ in range(ROWS)]

        # walls
        for i in range(ROWS):
            for j in range(COLS):
                if random.random() < wall_density:
                    maze[i][j] = "W"

        # terrain costs
        for i in range(ROWS):
            for j in range(COLS):
                if maze[i][j] == 0:
                    maze[i][j] = random.randint(1, 20)

        # start & goal
        start = (random.randint(0, ROWS - 1), random.randint(0, COLS - 1))
        goal = (random.randint(0, ROWS - 1), random.randint(0, COLS - 1))
        while goal == start:
            goal = (random.randint(0, ROWS - 1), random.randint(0, COLS - 1))

        maze[start[0]][start[1]] = "S"
        maze[goal[0]][goal[1]] = "G"

        # CHECK CONNECTIVITY
        if is_solvable():
            break


# ==========================================================
# MAIN WINDOW / GUI
# ==========================================================
def start_window():
    root = tk.Tk()
    root.title("Choose Mode")
    center_window(root)
    tk.Label(root, text="Select Mode:", font=("Arial", 14)).pack(pady=10)

    def open_main(mode):
        root.destroy()
        main_window(mode)

    tk.Button(
        root, text="Random Mode", width=20, command=lambda: open_main("random")
    ).pack(pady=5)
    tk.Button(
        root, text="Manual Mode", width=20, command=lambda: open_main("manual")
    ).pack(pady=5)
    root.mainloop()


def compare_algorithms_dashboard(root):
    global dashboard_window

    # If dashboard already exists, bring it to front
    if dashboard_window is not None and dashboard_window.winfo_exists():
        dashboard_window.lift()
        dashboard_window.focus_force()
        return
    if not start or not goal:
        messagebox.showwarning("Missing Data", "Place Start and Goal first")
        return

    algorithms = {
        "BFS": bfs,
        "DFS": dfs,
        "Greedy": greedy,
        "A*": astar,
    }

    results = []

    for name, algo in algorithms.items():
        path, order, _ = algo()

        path_cost = compute_path_cost(path)
        search_cost = compute_search_cost(order)

        results.append(
            {
                "name": name,
                "path_len": len(path) - 1 if path else float("inf"),
                "path_cost": path_cost,
                "search_cost": search_cost,
                "explored": len(order),
            }
        )

    # --------------------
    # DASHBOARD WINDOW
    # --------------------
    dashboard_window = tk.Toplevel(root)
    dash = dashboard_window
    dash.title("Algorithm Comparison Dashboard")

    def on_close():
        global dashboard_window
        dashboard_window = None
        dash.destroy()

    dash.protocol("WM_DELETE_WINDOW", on_close)

    tk.Label(
        dash, text="Algorithm Performance Comparison", font=("Arial", 16, "bold")
    ).pack(pady=10)

    header = tk.Frame(dash)
    header.pack(pady=5)

    headers = ["Algorithm", "Path Length", "Path Cost", "Search Cost", "Nodes Explored"]

    for col, text in enumerate(headers):
        tk.Label(
            header, text=text, width=18, font=("Arial", 10, "bold"), anchor="center"
        ).grid(row=0, column=col)
    for r in results:
        row = tk.Frame(dash)
        row.pack()

        values = [
            r["name"],
            r["path_len"],
            r["path_cost"],
            r["search_cost"],
            r["explored"],
        ]

        for col, val in enumerate(values):
            tk.Label(row, text=val, width=18, anchor="center").grid(row=0, column=col)


def go_back_to_home(current_root):
    current_root.destroy()
    start_window()


def main_window(mode):
    global \
        maze, \
        algorithm_choice, \
        preference_choice, \
        start, \
        goal, \
        ROWS, \
        COLS, \
        CURRENT_CELL
    last_painted = {"cell": None}
    ROWS, COLS = 8, 8
    start, goal = None, None
    # RESET STATE WHEN ENTERING A MODE
    if mode == "manual":
        maze = [[0 for _ in range(COLS)] for _ in range(ROWS)]
        start = None
        goal = None
    elif mode == "random":
        generate_random_maze()

    root = tk.Tk()
    root.title(f"Interactive Pathfinding - {mode.capitalize()} Mode")
    root.update_idletasks()
    center_window(root, width=900)

    show_heuristic = tk.BooleanVar(root, value=False)

    top_bar = tk.Frame(root)
    top_bar.pack(fill="x", pady=5)

    tk.Button(
        top_bar, text="⬅ Back to Home", command=lambda: go_back_to_home(root)
    ).pack(side="left", padx=10)

    CURRENT_CELL = CELL
    canvas = tk.Canvas(root, width=CANVAS_SIZE, height=CANVAS_SIZE, bg="white")
    canvas.pack()
    info = tk.Label(root, font=("Arial", 14))
    info.pack(pady=5)
    algo_used_label = tk.Label(root, font=("Arial", 12, "italic"))
    algo_used_label.pack()
    # ====================
    # BOTTOM CONTROL BAR
    # ====================
    bottom_bar = tk.Frame(root)
    bottom_bar.pack(fill="x", padx=10, pady=5)

    left_controls = tk.Frame(bottom_bar)
    left_controls.pack(side="left", expand=True)

    right_controls = tk.Frame(bottom_bar)
    right_controls.pack(side="right", expand=True)

    right_controls.columnconfigure(0, weight=1)
    mode_var = tk.StringVar(value="wall")

    # --------------------
    # DRAW GRID
    # --------------------
    def draw_grid():
        global CURRENT_CELL
        canvas.delete("all")
        if not maze:
            return

        rows = len(maze)
        cols = len(maze[0])

        cell_w = CANVAS_SIZE // cols
        cell_h = CANVAS_SIZE // rows
        CURRENT_CELL = max(MIN_CELL, min(cell_w, cell_h))

        for i in range(rows):
            for j in range(cols):
                cell = maze[i][j]

                if cell == "W":
                    color = "black"
                elif cell == "S":
                    color = "green"
                elif cell == "G":
                    color = "red"
                elif isinstance(cell, int):
                    color = WEIGHT_COLOR
                else:
                    color = "white"

                x1 = j * CURRENT_CELL
                y1 = i * CURRENT_CELL
                x2 = x1 + CURRENT_CELL
                y2 = y1 + CURRENT_CELL

                canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline="gray")

                # draw weight only if cell is large enough
                # --------------------
                # DRAW WEIGHT NUMBER
                # --------------------
                if (
                    isinstance(cell, int)
                    and rows <= MAX_NUMBER_GRID
                    and cols <= MAX_NUMBER_GRID
                ):
                    canvas.create_text(
                        x1 + CURRENT_CELL // 2,
                        y1 + CURRENT_CELL // 2,
                        text=str(cell),
                        fill="black",
                        font=("Arial", max(8, CURRENT_CELL // 3), "bold"),
                    )
                # --------------------
                # DRAW HEURISTIC
                # --------------------
                if (
                    show_heuristic.get()
                    and goal
                    and cell != "W"
                    and CURRENT_CELL >= MIN_HEURISTIC_CELL
                ):
                    h = heuristic_to_goal(i, j)
                    if h is not None:
                        canvas.create_text(
                            x1 + CURRENT_CELL - 3,
                            y1 + CURRENT_CELL - 3,
                            text=str(h),
                            fill="gray25",
                            anchor="se",
                            font=("Arial", CURRENT_CELL // 4),
                        )

    # --------------------
    # MOUSE INTERACTION
    # --------------------
    weight_value = tk.IntVar(value=1)

    def paint_cell(event):
        global start, goal

        r, c = event.y // CURRENT_CELL, event.x // CURRENT_CELL
        if r >= len(maze) or c >= len(maze[0]):
            return

        # Prevent flicker: same cell during drag
        if last_painted["cell"] == (r, c):
            return
        last_painted["cell"] = (r, c)
        if mode != "manual":
            return

        cell = maze[r][c]

        # Weight painting mode
        if weight_enabled.get():
            if cell != "W" and (r, c) != start and (r, c) != goal:
                maze[r][c] = weight_value.get()
                draw_grid()
            return

        # Normal editing modes
        if mode_var.get() == "wall":
            # Do not overwrite start or goal
            if (r, c) == start or (r, c) == goal:
                return

            # Toggle wall:
            # - weight -> wall
            # - empty -> wall
            # - wall -> empty
            if cell == "W":
                maze[r][c] = 0
            else:
                maze[r][c] = "W"

        elif mode_var.get() == "start":
            if start:
                maze[start[0]][start[1]] = 0
            start = (r, c)
            maze[r][c] = "S"

        elif mode_var.get() == "goal":
            if goal:
                maze[goal[0]][goal[1]] = 0
            goal = (r, c)
            maze[r][c] = "G"

        draw_grid()

    def reset_paint(_event):
        last_painted["cell"] = None

    canvas.bind("<ButtonRelease-1>", reset_paint)
    canvas.bind("<Button-1>", paint_cell)
    canvas.bind("<B1-Motion>", paint_cell)

    # --------------------
    # CONTROLS
    # --------------------
    controls = tk.Frame(left_controls)
    controls.pack(anchor="w")
    if mode == "manual":
        # --------------------
        # CENTERED EDIT BUTTONS
        # --------------------
        edit_frame = tk.Frame(controls)
        edit_frame.grid(row=0, column=0, columnspan=4, pady=5)

        def set_mode(mode):
            weight_enabled.set(False)  # disable weight paint
            mode_var.set(mode)

        tk.Button(
            edit_frame, text="Wall", width=8, command=lambda: set_mode("wall")
        ).pack(side="left", padx=5)

        tk.Button(
            edit_frame, text="Start", width=8, command=lambda: set_mode("start")
        ).pack(side="left", padx=5)

        tk.Button(
            edit_frame, text="Goal", width=8, command=lambda: set_mode("goal")
        ).pack(side="left", padx=5)
        # --------------------
        # CENTERED WEIGHT CONTROLS
        # --------------------
        weight_frame = tk.Frame(controls)
        weight_frame.grid(row=1, column=0, columnspan=4, pady=5)

        weight_enabled = tk.BooleanVar(value=False)

        tk.Checkbutton(
            weight_frame, text="Enable Weight Paint", variable=weight_enabled
        ).pack(side="left", padx=10)

        tk.Label(weight_frame, text="Weight Value").pack(side="left", padx=5)

        def on_weight_change(*args):
            weight_enabled.set(True)  # auto-enable weight paint

        weight_value.trace_add("write", on_weight_change)

        weight_slider = tk.Scale(
            weight_frame,
            from_=1,
            to=20,
            orient="horizontal",
            length=180,
            variable=weight_value,
        )
        weight_slider.pack(side="left")

    search_mode = tk.StringVar(root)
    search_mode.set("Algorithm")

    # --------------------
    # ALGORITHM AND PREFERENCE SELECTOR
    # --------------------
    algo_frame = tk.Frame(right_controls)
    algo_frame.pack(anchor="e", pady=5)

    # reserve vertical space so layout never jumps
    tk.Label(algo_frame, text="Search Mode:").grid(row=0, column=0, sticky="w")
    tk.OptionMenu(algo_frame, search_mode, "Algorithm", "Preference").grid(
        row=0, column=1, sticky="w"
    )
    selector_container = tk.Frame(algo_frame, height=40)
    selector_container.grid(row=1, column=1, sticky="w")
    selector_container.pack_propagate(False)

    algo_select_frame = tk.Frame(selector_container)

    algo_select_frame.pack(anchor="w")
    algo_select_frame.grid(row=1, column=1, sticky="w")

    algo_var = tk.StringVar(root)
    algo_var.set("BFS")
    tk.OptionMenu(algo_select_frame, algo_var, "BFS", "DFS", "Greedy", "A*").pack()

    def on_algo_change(*args):
        if search_mode.get() == "Algorithm":
            algo_used_label.config(text=f"Algorithm Used: {algo_var.get()}")

    algo_var.trace_add("write", on_algo_change)

    tk.Label(algo_frame, text="Preference:").grid(row=1, column=0)
    pref_select_frame = tk.Frame(selector_container)
    pref_select_frame.grid(row=2, column=1, sticky="w")

    pref_var = tk.StringVar(root)
    pref_var.set("Time")
    tk.OptionMenu(pref_select_frame, pref_var, "Time", "Cost").pack()

    def update_mode(*args):
        if search_mode.get() == "Algorithm":
            pref_select_frame.grid_remove()
            algo_select_frame.grid()
            algo_used_label.config(text=f"Algorithm Used: {algo_var.get()}")
        else:
            algo_select_frame.grid_remove()
            pref_select_frame.grid()
            algo_used_label.config(text="Algorithm Used: A* (Preference-Based)")

    search_mode.trace_add("write", update_mode)
    update_mode()

    tk.Checkbutton(
        right_controls,
        text="Show Heuristic",
        variable=show_heuristic,
        command=draw_grid,
    ).pack(anchor="e", pady=2)
    # --------------------
    # GENERATE MAZE CONTROLS
    # --------------------
    maze_group = tk.LabelFrame(
        left_controls,
        text="Maze Setup",
        padx=10,
        pady=8,
    )
    maze_group.pack(pady=5)

    for i in range(4):
        maze_group.columnconfigure(i, weight=1)
    tk.Label(maze_group, text="Rows:").grid(row=0, column=0)
    row_spin = tk.Spinbox(maze_group, from_=3, to=30, width=5)
    row_spin.grid(row=0, column=1)
    tk.Label(maze_group, text="Cols:").grid(row=0, column=2)
    col_spin = tk.Spinbox(maze_group, from_=3, to=30, width=5)
    col_spin.grid(row=0, column=3)
    analysis_group = tk.LabelFrame(
        left_controls,
        text="Analysis",
        padx=10,
        pady=8,
    )
    analysis_group.pack(pady=5)

    tk.Button(
        analysis_group,
        text="Compare Algorithms",
        width=18,
        command=lambda: compare_algorithms_dashboard(root),
    ).pack()
    # --------------------
    # WALL DENSITY (RANDOM MODE ONLY)
    # --------------------
    if mode == "random":
        tk.Label(maze_group, text="Wall Density (%)").grid(
            row=2, column=0, columnspan=4
        )

        wall_density_var = tk.IntVar(value=25)

        wall_slider = tk.Scale(
            maze_group,
            from_=0,
            to=60,
            orient="horizontal",
            length=200,
            variable=wall_density_var,
        )
        wall_slider.grid(row=3, column=0, columnspan=4, pady=4)

    def generate_maze_button():
        global ROWS, COLS, maze, start, goal, wall_density

        try:
            r = int(row_spin.get())
            c = int(col_spin.get())
        except ValueError:
            messagebox.showerror("Invalid Input", "Rows and Columns must be numbers")
            return

        if not (3 <= r <= 30 and 3 <= c <= 30):
            messagebox.showerror(
                "Invalid Grid Size", "Rows and Columns must be between 3 and 30"
            )
            return

        ROWS, COLS = r, c
        ROWS = int(row_spin.get())
        COLS = int(col_spin.get())

        if mode == "random":
            wall_density = wall_density_var.get() / 100.0
            generate_random_maze()
        else:
            maze = [[0 for _ in range(COLS)] for _ in range(ROWS)]
            start = None
            goal = None
        draw_grid()
        info.config(text="Maze ready")

        root.update_idletasks()
        center_window(root, width=900)
        root.minsize(900, root.winfo_height())

    tk.Button(
        maze_group, text="Generate Maze", width=18, command=generate_maze_button
    ).grid(row=1, column=0, columnspan=4, pady=6)
    run_frame = tk.Frame(right_controls)
    run_frame.pack(anchor="e", pady=5)

    tk.Button(
        run_frame,
        text="Run Algorithm",
        width=20,
        command=lambda: run_algorithm(algo_var, pref_var, canvas, info),
    ).pack()
    # --------------------
    # ANIMATION SPEED CONTROL
    # --------------------
    speed_frame = tk.Frame(right_controls)
    speed_frame.pack(anchor="e", pady=5)

    tk.Label(speed_frame, text="Animation Speed").pack(side="left", padx=5)

    speed_var = tk.IntVar(value=ANIMATION_DELAY)

    def on_speed_change(val):
        global ANIMATION_DELAY
        ANIMATION_DELAY = int(val)

    speed_slider = tk.Scale(
        speed_frame,
        from_=20,
        to=500,
        orient="horizontal",
        length=200,
        variable=speed_var,
        command=on_speed_change,
    )
    speed_slider.pack(side="left")

    # --------------------
    # RUN ALGORITHM
    # --------------------
    def run_algorithm(algo_var, pref_var, canvas, info):
        global preference_choice

        if not start or not goal:
            info.config(text="Place Start and Goal first")
            return

        if search_mode.get() == "Algorithm":
            preference_choice = "Time"
            algo_map = {"BFS": bfs, "DFS": dfs, "Greedy": greedy, "A*": astar}
            algo = algo_map[algo_var.get()]

        else:  # Preference-based
            preference_choice = pref_var.get()

            if preference_choice == "Time":
                algo = greedy
            else:  # Cost
                algo = astar

        path, order, _cost = algo()

        if search_mode.get() == "Algorithm":
            algo_used_label.config(text=f"Algorithm Used: {algo_var.get()}")
        else:  # Preference-based
            preference_choice = pref_var.get()
            result = run_preference_search()

            if not result:
                info.config(text="No path found")
                return

            algo_used_label.config(
                text=f"Algorithm Used: {result['name']} ({preference_choice} Preference)"
            )

            animate(
                canvas,
                root,
                result["order"],
                result["path"],
                info,
                show_heuristic,
            )
            return

        animate(canvas, root, order, path, info, show_heuristic)

    draw_grid()
    root.update_idletasks()
    center_window(root, width=900)
    root.minsize(900, root.winfo_height())


# ========================
# START PROGRAM
# ========================
start_window()
