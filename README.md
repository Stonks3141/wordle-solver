# Wordle Solver
This solver uses a decision tree stored as JSON to solve a Wordle. The user tells it what colors they get, and the solver gives them the best word to use. The decision tree is generated using a C program, and the solver is displayed as a webpage.

The solver is available online at https://stonks3141.github.io/wordle-solver.

## Guess distribution:

There are 2309 possible wordle solutions.

| Number of guesses | Frequency |
|-|-|
|1|0|
|2|23|
|3|816|
|4|1399|
|5|71|
|6|0|

Average: 3.66 guesses

## Usage

Compile `main.c` and run `./main | sed 's/,}/}/g;s/,$//' > wordle.json`. The sed command strips trailing commas from the JSON.
