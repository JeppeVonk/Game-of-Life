package source.java;

import java.util.Random;

public class GameOfLife {

  private static final int HEIGHT = 10;
  private static final int WIDTH = 10;
  private static final int FPS_LIMIT = 30;

  private int height;
  private int width;
  private boolean[][] grid;

  public GameOfLife() {
    this.height = HEIGHT;
    this.width = WIDTH;
    initGrid();
  }

  public GameOfLife(int height, int width) {
    this.height = height;
    this.width = width;
    initGrid();
  }

  private void initGrid() {
    grid = new boolean[height][width];
    Random random = new Random();

    // Willekeurige initialisatie
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        grid[i][j] = random.nextBoolean();
      }
    }

    // Randen altijd dood
    for (int i = 0; i < height; i++) {
      grid[i][0] = false;
      grid[i][width - 1] = false;
    }
    for (int j = 0; j < width; j++) {
      grid[0][j] = false;
      grid[height - 1][j] = false;
    }
  }

  public void run() {
    boolean[][] previousState = null;
    long frameDuration = 1000 / FPS_LIMIT;

    int frame = 0;

    while (true) {
      printGrid(grid);

      frame++;
      System.out.println("Frame: " + frame);

      boolean[][] nextState = getNextState(grid);

      if (checkStable(previousState, grid, nextState)) {
        System.out.println("System is stable. Stopping.");
        break;
      }

      previousState = grid;
      grid = nextState;

      try {
        Thread.sleep(frameDuration);
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }

  private boolean[][] getNextState(boolean[][] currentState) {
    boolean[][] newState = new boolean[height][width];

    for (int i = 1; i < height - 1; i++) {
      for (int j = 1; j < width - 1; j++) {
        int neighbours = countNeighbours(currentState, i, j);

        if (currentState[i][j]) {
          // Levend
          if (neighbours == 2 || neighbours == 3) {
            newState[i][j] = true;
          }
        } else {
          // Dood
          if (neighbours == 3) {
            newState[i][j] = true;
          }
        }
      }
    }

    return newState;
  }

  private int countNeighbours(boolean[][] state, int i, int j) {
    int counter = 0;

    for (int y = -1; y <= 1; y++) {
      for (int x = -1; x <= 1; x++) {
        if (y == 0 && x == 0)
          continue;

        if (state[i + y][j + x]) {
          counter++;
        }
      }
    }

    return counter;
  }

  private boolean checkStable(boolean[][] previousState,
                              boolean[][] currentState, boolean[][] nextState) {
    if (previousState == null)
      return false;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (previousState[i][j] != currentState[i][j] ||
            previousState[i][j] != nextState[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  private void printGrid(boolean[][] grid) {
    // Console clear (werkt in meeste terminals)
    System.out.print("\033[H\033[2J");
    System.out.flush();

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        System.out.print(grid[i][j] ? "#" : ".");
      }
      System.out.println();
    }
    System.out.println();
  }

  public static void main(String[] args) {
    System.out.println("Starting Game of Life...");
    GameOfLife game = new GameOfLife();
    game.run();
  }
}
