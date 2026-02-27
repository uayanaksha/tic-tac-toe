build:
  #!/bin/env bash
  [[ ! -d build ]] && mkdir build;
  g++ -std=c++23 -g \
    -o build/tic-tac-toe \
    src/main.cpp

run: build
  #!/bin/env bash
  ./build/tic-tac-toe
