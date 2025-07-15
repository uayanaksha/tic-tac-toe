#include <bits/stdc++.h>
#include <string>
#include <termios.h>

// Claude code-gen start

class RawMode {
private:
    struct termios orig_termios;

public:
    void enable() {
        tcgetattr(STDIN_FILENO, &orig_termios);

        struct termios raw = orig_termios;
        raw.c_lflag &= ~(ECHO | ICANON);  // Disable echo and canonical mode
        raw.c_cc[VMIN] = 1;   // Minimum characters to read
        raw.c_cc[VTIME] = 0;  // Timeout

        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    void disable() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    ~RawMode() { disable(); }
};

namespace AnsiColors {
    const std::string CLS   = "\033[2J\033[1;1H";
    const std::string RESET = "\033[0m";
    const std::string BOLD  = "\033[1m";
    const std::string DIM   = "\033[2m";

    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string WHITE   = "\033[37m";

};

// Claude code-gen end

class TicTacToe{
  private:
    static const unsigned BOARD_LENGTH = 3;
    std::vector<std::vector<char>> board{
      {' ', ' ', ' '},
      {' ', ' ', ' '},
      {' ', ' ', ' '},
    };

    bool isWinner(char c){
      for(int i{}; i < BOARD_LENGTH; i++)
        if((board.at(0).at(i) == c && board.at(1).at(i) == c && board.at(2).at(i) == c)
            || (board.at(i).at(0) == c && board.at(i).at(1) == c && board.at(i).at(2) == c))
          return true;
      return ((board.at(0).at(0) == c && board.at(1).at(1) == c && board.at(2).at(2) == c) ||
          (board.at(0).at(2) == c && board.at(1).at(1) == c && board.at(2).at(0) == c));
    }

    bool isDraw(){
      char c = ' ';
      for(int i{}; i < BOARD_LENGTH; i++)
        if( board.at(0).at(i) == c 
            || board.at(1).at(i) == c 
            || board.at(2).at(i) == c
            || (board.at(i).at(0) == c 
            || board.at(i).at(1) == c 
            || board.at(i).at(2) == c)
          ) return false;
      return true;
    }

    void redraw(){
      std::cout 
        << AnsiColors::CLS << AnsiColors::WHITE << AnsiColors::BOLD
        << "{" 
        << std::endl
        << "  " << "q:" << "[" << board.at(0).at(0) << "]"
        << "  " << "w:" << "[" << board.at(0).at(1) << "]"
        << "  " << "e:" << "[" << board.at(0).at(2) << "]"
        << std::endl
        << "  " << "a:" << "[" << board.at(1).at(0) << "]"
        << "  " << "s:" << "[" << board.at(1).at(1) << "]"
        << "  " << "d:" << "[" << board.at(1).at(2) << "]"
        << std::endl
        << "  " << "z:" << "[" << board.at(2).at(0) << "]"
        << "  " << "x:" << "[" << board.at(2).at(1) << "]"
        << "  " << "c:" << "[" << board.at(2).at(2) << "]"
        << std::endl
        << "}"
        << AnsiColors::RESET 
        << std::endl;

      std::cout 
        << "Available inputs: " 
        << ( board.at(0).at(0) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " q," << AnsiColors::RESET
        << ( board.at(0).at(1) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " w," << AnsiColors::RESET
        << ( board.at(0).at(2) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " e," << AnsiColors::RESET
        << ( board.at(1).at(0) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " a," << AnsiColors::RESET
        << ( board.at(1).at(1) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " s," << AnsiColors::RESET
        << ( board.at(1).at(2) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " d," << AnsiColors::RESET
        << ( board.at(2).at(0) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " z," << AnsiColors::RESET
        << ( board.at(2).at(1) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " x," << AnsiColors::RESET
        << ( board.at(2).at(2) == ' ' ? AnsiColors::BOLD : AnsiColors::DIM ) << " c," << AnsiColors::RESET
        << std::endl;
    }

    void humanInput(char c){
      char input;
      RawMode raw;
      std::cout 
        << "\'/\' to exit" << std::endl
        << "Enter choice: ";
      raw.enable();
      std::cin >> input;
      raw.disable();
      std::cout << std::endl;

      switch(input){
        case 'Q': if (board.at(0).at(0) == ' ') { board.at(0).at(0) = c; } break;
        case 'W': if (board.at(0).at(1) == ' ') { board.at(0).at(1) = c; } break;
        case 'E': if (board.at(0).at(2) == ' ') { board.at(0).at(2) = c; } break;
        case 'A': if (board.at(1).at(0) == ' ') { board.at(1).at(0) = c; } break;
        case 'S': if (board.at(1).at(1) == ' ') { board.at(1).at(1) = c; } break;
        case 'D': if (board.at(1).at(2) == ' ') { board.at(1).at(2) = c; } break;
        case 'Z': if (board.at(2).at(0) == ' ') { board.at(2).at(0) = c; } break;
        case 'X': if (board.at(2).at(1) == ' ') { board.at(2).at(1) = c; } break;
        case 'C': if (board.at(2).at(2) == ' ') { board.at(2).at(2) = c; } break;
        case 'q': if (board.at(0).at(0) == ' ') { board.at(0).at(0) = c; } break;
        case 'w': if (board.at(0).at(1) == ' ') { board.at(0).at(1) = c; } break;
        case 'e': if (board.at(0).at(2) == ' ') { board.at(0).at(2) = c; } break;
        case 'a': if (board.at(1).at(0) == ' ') { board.at(1).at(0) = c; } break;
        case 's': if (board.at(1).at(1) == ' ') { board.at(1).at(1) = c; } break;
        case 'd': if (board.at(1).at(2) == ' ') { board.at(1).at(2) = c; } break;
        case 'z': if (board.at(2).at(0) == ' ') { board.at(2).at(0) = c; } break;
        case 'x': if (board.at(2).at(1) == ' ') { board.at(2).at(1) = c; } break;
        case 'c': if (board.at(2).at(2) == ' ') { board.at(2).at(2) = c; } break;
        case '/': exit(1);
        default: 
          std::println("Invalid Input");
          break;
      }
    }

    void machineInput(char c){
    }

  public:
    void Init(){ 
      do {
        redraw();
        humanInput('x');
        if (isWinner('x')) { 
          redraw();
          std::println("{}Player Won!{}", AnsiColors::GREEN, AnsiColors::RESET ); 
          break;
        }
        if (isDraw()) { 
          redraw();
          std::println("{}[Draw]{}: No moves left!", AnsiColors::YELLOW, AnsiColors::RESET); 
          break; 
        }

        redraw();
        machineInput('o');
        if (isWinner('o')) { 
          redraw();
          std::println("{}Player Lost!{}", AnsiColors::RED, AnsiColors::RESET ); 
          break;
        }
        if (isDraw()) { 
          redraw();
          std::println("{}[Draw]{}: No moves left!", AnsiColors::YELLOW, AnsiColors::RESET); 
          break; 
        }
      } while(true);
    }
};

int main(void){
  TicTacToe game{};
  game.Init();
  return 0;
}
