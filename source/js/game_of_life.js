const HEIGHT = 10;
const WIDTH = 10;
const FPS_LIMIT = 30;

class GameOfLife {
  constructor(height = HEIGHT, width = WIDTH) {
    this.height = height;
    this.width = width;
    this.grid = [];
    this.initGrid();
  }

  initGrid() {
    // Willekeurige initialisatie
    this.grid = Array.from({ length: this.height }, () =>
      Array.from({ length: this.width }, () => Math.random() < 0.5),
    );

    // Randen altijd dood
    for (let i = 0; i < this.height; i++) {
      this.grid[i][0] = false;
      this.grid[i][this.width - 1] = false;
    }

    for (let j = 0; j < this.width; j++) {
      this.grid[0][j] = false;
      this.grid[this.height - 1][j] = false;
    }
  }

  async run() {
    let previousState = null;
    const frameDuration = 1000 / FPS_LIMIT;
    let frame = 0;

    while (true) {
      this.printGrid();

      frame++;
      console.log("Frame:", frame);

      const nextState = this.getNextState(this.grid);

      if (this.checkStable(previousState, this.grid, nextState)) {
        console.log("System is stable. Stopping.");
        break;
      }

      previousState = this.deepCopy(this.grid);
      this.grid = nextState;

      await this.sleep(frameDuration);
    }
  }

  getNextState(currentState) {
    const newState = Array.from({ length: this.height }, () =>
      Array.from({ length: this.width }, () => false),
    );

    for (let i = 1; i < this.height - 1; i++) {
      for (let j = 1; j < this.width - 1; j++) {
        const neighbours = this.countNeighbours(currentState, i, j);

        if (currentState[i][j]) {
          if (neighbours === 2 || neighbours === 3) {
            newState[i][j] = true;
          }
        } else {
          if (neighbours === 3) {
            newState[i][j] = true;
          }
        }
      }
    }

    return newState;
  }

  countNeighbours(state, i, j) {
    let counter = 0;

    for (let y = -1; y <= 1; y++) {
      for (let x = -1; x <= 1; x++) {
        if (y === 0 && x === 0) continue;

        if (state[i + y][j + x]) {
          counter++;
        }
      }
    }

    return counter;
  }

  checkStable(previousState, currentState, nextState) {
    if (!previousState) return false;

    for (let i = 0; i < this.height; i++) {
      for (let j = 0; j < this.width; j++) {
        if (
          previousState[i][j] !== currentState[i][j] ||
          previousState[i][j] !== nextState[i][j]
        ) {
          return false;
        }
      }
    }

    return true;
  }

  printGrid() {
    // Console clear (Node.js)
    console.clear();

    for (let i = 0; i < this.height; i++) {
      let row = "";
      for (let j = 0; j < this.width; j++) {
        row += this.grid[i][j] ? "#" : ".";
      }
      console.log(row);
    }
    console.log();
  }

  deepCopy(grid) {
    return grid.map((row) => [...row]);
  }

  sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
  }
}

(async () => {
  console.log("Starting Game of Life...");
  const game = new GameOfLife();
  await game.run();
})();
