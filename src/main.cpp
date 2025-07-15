#include <bits/stdc++.h>
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
    const std::string RESET =   "\033[0m";
    const std::string BOLD =    "\033[1m";
    const std::string DIM =     "\033[2m";
    const std::string ITALIC =  "\033[3m";
    const std::string UNDERLINE = "\033[4m";
    const std::string BLINK =   "\033[5m";
    const std::string REVERSE = "\033[7m";
    const std::string STRIKETHROUGH = "\033[9m";

    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";

    const std::string BG_BLACK = "\033[40m";
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_YELLOW = "\033[43m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CYAN = "\033[46m";
    const std::string BG_WHITE = "\033[47m";
};

// Claude code-gen end

class TicTacToe{
  private:
    std::vector<std::vector<char>> board{
      {' ', ' ', ' '},
      {' ', ' ', ' '},
      {' ', ' ', ' '},
    };
    char current = 'x';
    static const unsigned BOARD_LENGTH = 3;

    std::array<bool, 4> finished(){
      static bool ended = false;
      static bool isDraw = false;
      static bool xWon = false;
      static bool oWon = false;
      // game end conditions
      const std::vector<bool> conditions {
        (board[0][0] != ' ' && board[0][0] == board[1][0] && board[1][0] == board[2][0]),
        (board[0][1] != ' ' && board[0][1] == board[1][1] && board[1][1] == board[2][1]),
        (board[0][2] != ' ' && board[0][2] == board[1][2] && board[1][2] == board[2][2]),
        (board[0][0] != ' ' && board[0][0] == board[0][1] && board[0][1] == board[0][2]),
        (board[1][0] != ' ' && board[1][0] == board[1][1] && board[1][1] == board[1][2]),
        (board[2][0] != ' ' && board[2][0] == board[2][1] && board[2][1] == board[2][2]),
        (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]),
        (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]),
      };

      // checking for matching conditions
      for (auto condition : conditions) {
        if(condition){
          ended = true, isDraw = false;
          if (current == 'x'){
            xWon = false;
            oWon = true;
          } else {
            xWon = true;
            oWon = false;
          }
          return std::array{ended, isDraw, xWon, oWon};
        }      
      }

      // If empty cell exists ; then match will continue
      for (auto row: board){
        for (auto cell: row){
          if (cell == ' '){
            return std::array{ended, isDraw, xWon, oWon};
          }
        }
      }

      // Draw match
      ended = true, isDraw = true;
      return std::array{ended, isDraw, xWon, oWon};
    }

    void redraw(){
      std::println("{}", "{");
      std::print("  {}[{}]", 'q', board.at(0).at(0));
      std::print("  {}[{}]", 'w', board.at(0).at(1));
      std::println("  {}[{}]", 'e', board.at(0).at(2));
      std::print("  {}[{}]", 'a', board.at(1).at(0));
      std::print("  {}[{}]", 's', board.at(1).at(1));
      std::println("  {}[{}]", 'd', board.at(1).at(2));
      std::print("  {}[{}]", 'z', board.at(2).at(0));
      std::print("  {}[{}]", 'x', board.at(2).at(1));
      std::println("  {}[{}]", 'c', board.at(2).at(2));
      std::println("{}", "}");
    }

    void setInput(){
      using namespace AnsiColors;
      char input;
      std::cout 
        << "Available inputs: " 
        << ( board.at(0).at(0) == ' ' ? BOLD : DIM ) << " q," << RESET
        << ( board.at(0).at(1) == ' ' ? BOLD : DIM ) << " w," << RESET
        << ( board.at(0).at(2) == ' ' ? BOLD : DIM ) << " e," << RESET
        << ( board.at(1).at(0) == ' ' ? BOLD : DIM ) << " a," << RESET
        << ( board.at(1).at(1) == ' ' ? BOLD : DIM ) << " s," << RESET
        << ( board.at(1).at(2) == ' ' ? BOLD : DIM ) << " d," << RESET
        << ( board.at(2).at(0) == ' ' ? BOLD : DIM ) << " z," << RESET
        << ( board.at(2).at(1) == ' ' ? BOLD : DIM ) << " x," << RESET
        << ( board.at(2).at(2) == ' ' ? BOLD : DIM ) << " c," << RESET
        << std::endl;

      RawMode raw;
      std::cout << "Enter choice: ";
      raw.enable();
      std::cin >> input;
      raw.disable();
      std::cout << std::endl;

      switch(input){
        case 'Q': if (board.at(0).at(0) == ' ') { board.at(0).at(0) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'W': if (board.at(0).at(1) == ' ') { board.at(0).at(1) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'E': if (board.at(0).at(2) == ' ') { board.at(0).at(2) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'A': if (board.at(1).at(0) == ' ') { board.at(1).at(0) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'S': if (board.at(1).at(1) == ' ') { board.at(1).at(1) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'D': if (board.at(1).at(2) == ' ') { board.at(1).at(2) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'Z': if (board.at(2).at(0) == ' ') { board.at(2).at(0) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'X': if (board.at(2).at(1) == ' ') { board.at(2).at(1) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'C': if (board.at(2).at(2) == ' ') { board.at(2).at(2) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'q': if (board.at(0).at(0) == ' ') { board.at(0).at(0) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'w': if (board.at(0).at(1) == ' ') { board.at(0).at(1) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'e': if (board.at(0).at(2) == ' ') { board.at(0).at(2) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'a': if (board.at(1).at(0) == ' ') { board.at(1).at(0) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 's': if (board.at(1).at(1) == ' ') { board.at(1).at(1) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'd': if (board.at(1).at(2) == ' ') { board.at(1).at(2) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'z': if (board.at(2).at(0) == ' ') { board.at(2).at(0) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'x': if (board.at(2).at(1) == ' ') { board.at(2).at(1) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        case 'c': if (board.at(2).at(2) == ' ') { board.at(2).at(2) = current; current = (current == 'x') ? 'o' : 'x'; } break;
        default: 
          std::println("Invalid Input");
          break;
      }
      
    }

  public:
    void Init(){ 
      do {
        std::print("\033[2J\033[1;1H");
        redraw();
        setInput();
      } while(!finished()[0]);
      std::print("\033[2J\033[1;1H");
      redraw();
      auto [ended, isDraw, xWon, oWon] = finished();
      if (isDraw) std::println("{}[Draw]{}: No moves left!", AnsiColors::YELLOW, AnsiColors::RESET);
      if (xWon)   std::println("{}[Winner] X{}", AnsiColors::GREEN, AnsiColors::RESET );
      if (oWon)   std::println("{}[Winner] o{}", AnsiColors::GREEN, AnsiColors::RESET );
    }

};

int main(void){
  TicTacToe game{};
  game.Init();
  return 0;
}
