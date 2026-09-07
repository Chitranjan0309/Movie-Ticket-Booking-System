# Movie Ticket Booking System — C++ source

## Build
```
cd src
g++ -std=c++17 -Wall -Wextra -o ../cinema main.cpp
```
No header files are used (course rule) — every class's declaration and
implementation live together in its own `.cpp`, and `main.cpp` `#include`s
them in dependency order, so the whole program compiles as a single
translation unit.

## Run
```
cd ..
./cinema            # interactive console menu
./cinema --demo     # scripted run that exercises F1-F8 and all 4 edge cases
                     # with no keyboard input (see demo_run_output.txt for
                     # a saved transcript of exactly this run)
```

## Layout
- `src/` — one `.cpp` per class (18 files), see the assignment report for
  what each one is responsible for.
- `demo_run_output.txt` — full output of `./cinema --demo`, reproduced in
  the report's Step G.
- `diagram_sources/` — the Graphviz (`class_diagram.dot`) and
  matplotlib (`sequence_diagram.py`) sources used to render Figures 1 and 2
  in the report, plus the original Mermaid class-diagram source
  (`class_diagram.mmd` — kept for reference; the .dot version is what was
  actually rendered, since Mermaid CLI's headless Chrome wasn't available
  in the build environment).

## Verified
- Compiles with zero warnings under `-Wall -Wextra`.
- Re-compiled and re-run under `-fsanitize=address,undefined`: zero leaks,
  zero errors.
