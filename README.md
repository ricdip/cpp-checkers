# cpp-checkers

A C++ implementation of the checkers game using also CMake and GoogleTest for learning purposes.

## Implemented AI algorithms
- **MinMax Alpha-Beta** (fail-hard implementation): search algorithm that seeks to decrease the number of nodes that are evaluated by the MinMax Algorithm in its search tree. It returns the same move as MinMax would, but prunes away branches that cannot influence the final decision. The algorithm maintains two values, alpha and beta, which respectively represent the minimum score that the maximizing player is assured of and the maximum score that the minimizing player is assured of. An implementation of Alpha–Beta Pruning can be **fail-soft** or **fail-hard**. With fail-soft, the algorithm may return values (`value`) that exceed (`value > beta` or `value < alpha`) the alpha and beta bounds set by its function call arguments. The fail-hard implementation limits its function return value into the inclusive range of alpha and beta.

## Implemented Heuristics
- **Game over** heuristic:
    - returns score `INT32_MAX` if max player wins
    - returns score `INT32_MIN` if min player wins
    - returns score `0` otherwise

- **Board pieces** heuristic: returns the sum of all pieces values for both the players (a max player piece value has sign `+`, a min player piece value has sign `-`)

## Structure
All source code is located in the `src` directory:
- `app`: directory that contains an application example that uses the checkers library
- `lib`: directory that contains the checkers shared library
- `tests`: directory that contains all the tests (implemented using GoogleTest) for the checkers shared library

The shared library, the app and the tests are built using CMake with multiple CMakeLists files.

## Dependencies
- **Make**: Makefile execution
- **CMake**: building process
- **GoogleTest**: testing for checkers library

## Build release version
The release build uses optimization flags that decrease the execution time:
- used GNU compiler flags: `-Wall -Wextra -pedantic -Werror -O2`

### Build library and app example
```bash
user@host:~$ make build_release
```

### Build library and tests
```bash
user@host:~$ make build_release_test
```

## Build debug version
The debug build uses flags that help during the development:
- used GNU compiler flags: `-Wall -Wextra -pedantic -Werror -g -fsanitize=address`

### Build library and app example
```bash
user@host:~$ make build_debug
```

### Build library and tests
```bash
user@host:~$ make build_debug_test
```

## Execution

### Run app example
```bash
user@host:~$ make run
```

### Run tests
```bash
user@host:~$ make run_tests
```

### Display help message
```bash
user@host:~$ make help
```

## App example
A very simple app that uses the checkers shared library.

The app has two execution modes:
- interactive execution mode: `./cpp_checkers`
- non-interactive execution mode: `./cpp_checkers <max_depth_AI_1> <max_depth_AI_2>`

In interactive execution mode, the app asks to choose between two game modes:
- `AIvsAI`: both `WHITE` and `BLACK` players are controlled by the AI
- `HumanvsAI`: player `WHITE` is controller by the human player, player `BLACK` is controlled by the AI
For each game mode, the app asks the **max depth** value for the AI to limit the depth of the game tree.

In non-interactive execution mode, the app executes the `AIvsAI` game mode with the max depths passed as inputs.

## Performance
Using the release build of the application, it is recommended to choose a max depth between [1, 7] inclusive. For higher max depths the app may be really slow.

In the following table we show the results of the non-interactive execution mode of the app example with the same max depth for both AIs:

| Depth | Game result                | Time            |
| :---: | -------------------------  | :-------------: |
| 1     | Draw: threefold repetition | 0.010 sec       |
| 2     | Winner: black              | 0.036 sec       |
| 3     | Winner: black              | 0.186 sec       |
| 4     | Draw: threefold repetition | 0.760 sec       |
| 5     | Draw: threefold repetition | 3.852 sec       |
| 6     | Draw: threefold repetition | 49.009 sec      |
| 7     | Draw: threefold repetition | 4 min 28.19 sec |
