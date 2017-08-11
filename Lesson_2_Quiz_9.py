# ----------
# User Instructions:
#
# Define a function, search() that returns a list
# in the form of [optimal path length, row, col]. For
# the grid shown below, your function should output
# [11, 4, 5].
#
# If there is no valid path from the start point
# to the goal, your function should return the string
# 'fail'
# ----------

# Grid format:
#   0 = Navigable space
#   1 = Occupied space
import copy

grid = [[0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 1, 1, 1, 0],
        [0, 0, 0, 0, 1, 0]]

init = [0, 0]
goal = [len(grid) - 1, len(grid[0]) - 1]
cost = 0

delta = [[-1, 0],  # go up
         [0, -1],  # go left
         [1, 0],  # go down
         [0, 1]]  # go right

delta_name = ['^', '<', 'v', '>']


def search(grid, init, goal, cost):
    # ----------------------------------------
    # insert code here
    # ----------------------------------------
    grid[init[0]][init[1]] = 1
    path = None

    # Have we reached our goal state?
    if init == goal:
        return [cost, init[0], init[1]]

    expansions = []
    # let's "expand"
    for move in delta:
        # add current position to the next valid expansion position
        pose = [x + y for x, y in zip(init, move)]
        row, col = pose
        # out-of-bounds check
        if col >= 0 and row >= 0 and len(grid) > row and len(grid[row]) > col:
            if grid[row][col] == 0:
                grid[row][col] = 1
                expansions.append([cost+1, row, col])
    for expansion in expansions:
        _path = search(copy.deepcopy(grid), expansion[1:3], goal, expansion[0])
        if _path is not None:
            if path is None:
                path = _path
            if _path[0] < path[0]:
                path = _path
    return path


path = search(grid, init, goal, cost)

if path == None:
    print('fail')
else:
    print(path)
