use std::thread;
use std::time::{Duration, SystemTime, UNIX_EPOCH};

const HEIGHT: usize = 10;
const WIDHT: usize = 10;
const FPS_LIMIT: u64 = 30;

struct GameOfLife {
    height: usize,
    width: usize,
    grid: Vec<Vec<bool>>
}

impl GameOfLife {
    fn new(height: usize, width: usize) -> Self {
        let mut game = GameOfLife {
            height,
            width,
            grid: vec![vec![false; width]; height]
        };
        game.init_grid();
        game
    }

    fn init_grid(&mut self) {
        let mut seed = current_time_seed();

        for i in 0..self.height {
            for j in 0..self.width {
                seed = lcg(seed);
                self.grid[i][j] = seed % 2 == 0;
            }
        }

        // Randen altijd dood
        for i in 0..self.height {
            self.grid[i][0] = false;
            self.grid[i][self.width - 1] = false;
        }
        for j in 0..self.width {
            self.grid[0][j] = false;
            self.grid[self.height - 1][j] = false;
        }
    }

    fn run(&mut self) {
        let mut previous_state: Option<Vec<Vec<bool>>> = None;
        let frame_duration = Duration::from_millis(1000 / FPS_LIMIT);
        let mut frame = 0;

        loop {
            self.print_grid();

            frame += 1;
            println!("Frame: {}", frame);

            let next_state = self.get_next_state();

            if self.check_stable(&previous_state, &next_state) {
                println!("System is stable. Stopping.");
                break;
            }

            previous_state = Some(self.grid.clone());
            self.grid = next_state;

            thread::sleep(frame_duration);
        }
    }

    fn get_next_state(&self) -> Vec<Vec<bool>> {
        let mut new_state = vec![vec![false; self.width]; self.height];

        for i in 1..self.height - 1 {
            for j in 1..self.width - 1 {
                let neighbours = self.count_neighbours(i, j);

                if self.grid[i][j] {
                    if neighbours == 2 || neighbours == 3 {
                        new_state[i][j] = true;
                    }
                } else {
                    if neighbours == 3 {
                        new_state[i][j] = true;
                    }
                }
            }
        }

        new_state
    }

    fn count_neighbours(&self, i: usize, j: usize) -> usize {
        let mut counter = 0;

        for y in -1..=1 {
            for x in -1..=1 {
                if y == 0 && x == 0 {
                    continue;
                }

                let ni = (i as isize + y) as usize;
                let nj = (j as isize + x) as usize;

                if self.grid[ni][nj] {
                    counter += 1;
                }
            }
        }

        counter
    }

    fn check_stable(
        &self,
        previous_state: &Option<Vec<Vec<bool>>>,
        next_state: &Vec<Vec<bool>>
    ) -> bool {
        if previous_state.is_none() {
            return false;
        }

        let prev = previous_state.as_ref().unwrap();

        for i in 0..self.height {
            for j in 0..self.width {
                if prev[i][j] != self.grid[i][j]
                    || prev[i][j] != next_state[i][j]
                {
                    return false;
                }
            }
        }

        true
    }

    fn print_grid(&self) {
        // ANSI clear screen
        print!("\x1B[2J\x1B[1;1H");

        for row in &self.grid {
            for &cell in row {
                if cell {
                    print!("#");
                } else {
                    print!(".");
                }
            }
            println!();
        }
        println!();
    }
}

// Simpele pseudo-random generator (LCG)
// Alleen standaardbibliotheek toegestaan -> geen rand crate
fn lcg(seed: u64) -> u64 {
    seed.wrapping_mul(1664525).wrapping_add(1013904223)
}

fn current_time_seed() -> u64 {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64
}

fn main() {
    println!("Starting Game of Life...");
    let mut game = GameOfLife::new(HEIGHT, WIDTH);
    game.run();
}
