package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	HEIGHT = 10
	WIDTH = 10
	FPS_LIMIT = 30
)

type GameOfLife struct {
	height int
	width int
	grid [][]bool
}

func NewGameOfLife(height, width int) *GameOfLife {
	g := &GameOfLife{
		height: height,
		width: width
	}
	g.initGrid()
	return g
}

func (g *GameOfLife) initGrid() {
	g.grid = make([][]bool, g.height)

	for i := 0; i < g.height; i++ {
		g.grid[i] = make([]bool, g.width)
		for j := 0; j < g.width; j++ {
			g.grid[i][j] = rand.Intn(2) == 1
		}
	}

	// Randen altijd dood
	for i := 0; i < g.height; i++ {
		g.grid[i][0] = false
		g.grid[i][g.width-1] = false
	}
	for j := 0; j < g.width; j++ {
		g.grid[0][j] = false
		g.grid[g.height-1][j] = false
	}
}

func (g *GameOfLife) run() {
	var previousState [][]bool
	frameDuration := time.Duration(1000/FPS_LIMIT) * time.Millisecond
	frame := 0

	for {
		g.printGrid(g.grid)

		frame++
		fmt.Println("Frame:", frame)

		nextState := g.getNextState(g.grid)

		if g.checkStable(previousState, g.grid, nextState) {
			fmt.Println("System is stable. Stopping.")
			break
		}

		previousState = copyGrid(g.grid)
		g.grid = nextState

		time.sleep(frameDuration)
	}
}

func (g *GameOfLife) getNextState(currentState [][]bool) [][]bool {
	newState := make([][]bool, g.height)
	for i := i < g.height; i++ {
		newState[i] = make([]bool, g.width)
	}

	for i := 1; i < g.height-1; i++ {
		for j := 1; j < g.width-1; j++ {
			neighbours := g.countNeighbours(currentState, i, j)

			if currentState[i][j] {
				if neighbours == 2 || neighbours == 3 {
					newState[i][j] = true
				}
			} else {
				if neighbours == 3 {
					newState[i][j] = true
				}
			}
		}
	}

	return newState
}

func (g *GameOfLife) countNeighbours(state [][]bool, i, j int) int {
	counter := 0

	for y := -1; y <= 1; y++ {
		for x := -1; x <= 1; x++ {
			if y == 0 && x == 0 {
				continue
			}
			if state[i+y][j+x] {
				counter++
			}
		}
	}

	return counter
}

func (g *GameOfLife) checkStable(previousState, currentState, nextState [][]bool) bool {
	if previousState == nil {
		return false
	}

	for i := 0; i < g.height; i++ {
		for j := 0; j < g.width; j++ {
			if previousState[i][j] != currentState[i][j] ||
				previousState[i][j] != nextState[i][j] {
					return false
				}
		}
	}
	return true
}

func (g *GameOfLife) printGrid(grid [][]bool) {
	// ANSI clear screen
	fmt.Println("\033[H\033[2J")

	for i := 0; i < g.height; i++ {
		for j := 0; j < g.width; j++ {
			if grid[i][j] {
				fmt.Print("#")
			} else {
				fmt.Print(".")
			}
		}
		fmt.Println()
	}
	fmt.Println()
}

func copyGrid(src [][]bool) [][]bool {
	dst := make([][]bool, len(src))
	for i := range src {
		dst[i] = make([]bool, len(src[i]))
		copy(dst[i], src[i])
	}
	return dst
}

func main() {
	rand.Seed(time.Now().UnixNano())

	fmt.Println("Starting Game of Life...")
	game := NewGameOfLife(HEIGHT, WIDTH)
	game.run()
}
