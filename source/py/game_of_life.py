import random
import time
import copy


HEIGHT = 10
WIDTH = 10
FPS_LIMIT = 30


class GameOfLife:
    def __init__(self, height=HEIGHT, width=HEIGHT):
        self.height = height
        self.width = width
        self.grid = []
        self.init_grid()

    def init_grid(self):
        # Willekeurige initialisatie
        self.grid = [
            [random.choice([True, False]) for _ in range(self.width)]
            for _ in range(self.height)
        ]

        # Randen altijd dood
        for i in range(self.height):
            self.grid[i][0] = False
            self.grid[i][self.width - 1] = False

        for j in range(self.width):
            self.grid[0][j] = False
            self.grid[self.height - 1][j] = False

    def run(self):
        previous_state = None
        frame_duration = 1 / FPS_LIMIT
        frame = 0

        while True:
            self.print_grid(self.grid)

            frame += 1
            print(f"Frame: {frame}")

            next_state = self.get_next_state(self.grid)

            if self.check_stable(previous_state, self.grid, next_state):
                print("System is stable. Stopping.")
                break

            previous_state = copy.deepcopy(self.grid)
            self.grid = next_state

            time.sleep(frame_duration)

    def get_next_state(self, current_state):
        # Nieuwe lege grid
        new_state = [
            [False for _ in range(self.width)]
            for _ in range(self.height)
        ]

        for i in range(1, self.height - 1):
            for j in range(1, self.width - 1):
                neighbours = self.count_neighbours(current_state, i, j)

                if current_state[i][j]:
                    # Levend
                    if neighbours == 2 or neighbours == 3:
                        new_state[i][j] = True
                else:
                    # Dood
                    if neighbours == 3:
                        new_state[i][j] = True

        return new_state

    def count_neighbours(self, state, i, j):
        counter = 0

        for y in range(-1, 2):
            for x in range(-1, 2):
                if y == 0 and x == 0:
                    continue

                if state[i + y][j + x]:
                    counter += 1

        return counter

    def check_stable(self, previous_state, current_state, next_state):
        if previous_state is None:
            return False

        for i in range(self.height):
            for j in range(self.width):
                if (previous_state[i][j] != current_state[i][j] or
                        previous_state[i][j] != next_state[i][j]):
                    return False
        return True

    def print_grid(self, grid):
        # Console leegmaken (werkt op meeste systemen)
        print("\033[H\033[2J", end="")

        for row in grid:
            for cell in row:
                print("#" if cell else ".", end="")
            print()
        print()


if __name__ == "__main__":
    print("Starting Game of Life...")
    game = GameOfLife()
    game.run()
