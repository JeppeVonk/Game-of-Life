#include <cstdlib>
#include <iostream>
#include <thread>

const int HEIGHT    = 10;
const int WIDTH     = 10;
const int FPS_LIMIT = 30;

class GameOfLife {
public:
  GameOfLife();
  GameOfLife(const int &height, const int &width);
  ~GameOfLife();

  void run();

private:
  int height;
  int width;
  bool **grid; // grid[height][width]

  void initGrid(const int &height, const int &width);

  bool **getNextState(bool **const currentState);
  int countNeighbours(bool **const state, const int &i, const int &j);

  bool checkStable(bool **const previousState, bool **const currentState,
                   bool **const nextState);

  void printGrid(bool **const grid);

  void cleanGrid(bool **grid, const int &height, const int &width);
};

GameOfLife::GameOfLife() : height(HEIGHT), width(WIDTH) {
  this->initGrid(this->height, this->width);
}

GameOfLife::GameOfLife(const int &height, const int &width) :
    height(height), width(width) {
  this->initGrid(this->height, this->width);
}

GameOfLife::~GameOfLife() {
  this->cleanGrid(this->grid, this->height, this->width);
}

void GameOfLife::run() {
  bool **previousState = nullptr;

  using clock        = std::chrono::steady_clock;
  auto frameDuration = std::chrono::milliseconds(1000 / FPS_LIMIT);

  int frame = 0;
  while (true) {
    this->printGrid(this->grid);

    frame++;
    std::cout << "Frame: " << frame << std::endl;

    bool **nextState = this->getNextState(this->grid);

    if (this->checkStable(previousState, this->grid, nextState)) {
      break;
    }

    this->cleanGrid(previousState, this->height, this->width);

    previousState = this->grid;
    this->grid    = nextState;

    std::this_thread::sleep_for(frameDuration);
  }
}

void GameOfLife::initGrid(const int &height, const int &width) {
  this->grid = new bool *[height];
  for (int i = 0; i < height; i++) {
    this->grid[i] = new bool[width];

    for (int j = 0; j < width; j++) {
      this->grid[i][j] = (rand() % 2) ? true : false;
    }
  }

  // Randen altijd dood beschouwd
  for (int i = 0; i < height; i++) {
    if (i == 0 || i == height - 1) {
      for (int j = 0; j < width; j++) {
        this->grid[i][j] = false;
      }
    } else {
      this->grid[i][0]         = false;
      this->grid[i][width - 1] = false;
    }
  }
}

bool **GameOfLife::getNextState(bool **const currentState) {
  bool **newState = new bool *[this->height];
  for (int i = 0; i < this->height; i++) {
    newState[i] = new bool[this->width];
    for (int j = 0; j < this->width; j++) {
      newState[i][j] = false;
    }
  }

  if (currentState == nullptr) {
    return newState;
  }

  // Courtesy of https://nl.wikipedia.org/wiki/Game_of_Life

  // Inspecteer alle levende cellen
  for (int i = 1; i < this->height - 1; i++) {
    for (int j = 1; j < this->width - 1; j++) {
      if (currentState[i][j]) {
        // Check of cel 2 of 3 levende buren heeft, zo ja, wordt levend
        switch (this->countNeighbours(currentState, i, j)) {
          case 2:
          case 3: newState[i][j] = true; break;
          default: break;
        }
      }
    }
  }

  // Inspecteer alle lege cellen
  for (int i = 1; i < this->height - 1; i++) {
    for (int j = 1; j < this->width - 1; j++) {
      if (!currentState[i][j]) {
        // Check of cel precies 3 levende buren heeft, zo ja, wordt
        // levend
        if (this->countNeighbours(currentState, i, j) == 3) {
          newState[i][j] = true;
        }
      }
    }
  }

  return newState;
}

int GameOfLife::countNeighbours(bool **const state, const int &i,
                                const int &j) {
  if (state == nullptr) {
    return -1;
  }

  // Randen altijd dood beschouwd
  if (i <= 0 || i >= this->height - 1 || j <= 0 || j >= this->width - 1) {
    return -1;
  }

  int counter = 0;

  // Check alle 8 buurcellen
  // (i-1, j-1) (i-1, j) (i-1, j+1)
  // (i, j-1)   (i, j)   (i, j+1)
  // (i+1, j-1) (i+1, j) (i+1, j+1)
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (y == 0 && x == 0) {
        continue;
      }

      if (state[i + y][j + x]) {
        counter++;
      }
    }
  }

  return counter;
}

bool GameOfLife::checkStable(bool **const previousState,
                             bool **const currentState,
                             bool **const nextState) {
  if (previousState == nullptr || currentState == nullptr ||
      nextState == nullptr) {
    return false;
  }

  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      if (previousState[i][j] != currentState[i][j] ||
          previousState[i][j] != nextState[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void GameOfLife::printGrid(bool **const grid) {
  if (grid == nullptr) {
    return;
  }

  // Leeg console
  std::cout << "\033[2J";

  // Verplaats cursor naar begin
  std::cout << "\033[1;1H";

  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      std::cout << ((grid[i][j]) ? '#' : '.');
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

void GameOfLife::cleanGrid(bool **grid, const int &height, const int &width) {
  if (grid == nullptr) {
    return;
  }

  for (int i = 0; i < height; i++) {
    delete[] grid[i];
  }
  delete[] grid;
  grid = nullptr;
}

int main() {
  std::cout << "Hello, World!" << std::endl;

  GameOfLife gameOfLife;
  gameOfLife.run();

  return 0;
}
