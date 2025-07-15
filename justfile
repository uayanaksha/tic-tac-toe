build:
  #!/bin/env bash
  [[ ! -d build ]] && mkdir build;
  g++ -std=c++23 -g \
    -o build/tic-tac-toe \
    src/main.cpp

run:
  #!/bin/env bash
  if [ -x build/tic-tac-toe ] ; then 
    ./build/tic-tac-toe
  else
    echo "Build with `just build`"
  fi
