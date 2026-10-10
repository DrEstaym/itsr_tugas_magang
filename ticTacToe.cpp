#include <bits/stdc++.h>
using namespace std;

class Player {
    private:
        string name;
        char designation; // X or O
    
    public:
        Player() {
            this->name = "NULL";
        }

        Player(string name, char desig) {
            this->name = name;
            this->designation = desig;
        }

        string getName() {return name;}
        char getDesig() {return designation;}
};

class Game {
    private:
        vector<char> board;
        Player CurrentPlayer;
        Player P1, P2;

        bool isBoardFull() {
            //return true if there is no valid moves
            return (getValidMoves().size() == 0) ? true : false;
        }

        vector<int> getValidMoves() {
            vector<int> valid;
            for(int i = 0; i < 9; i++) {
                if(board[i] == '.') valid.push_back(i);
            }
            return valid;
        }
        
        bool checkWin(char currentDesig) {
            const vector<vector<int>> winCondition = {
                {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                {0, 4, 8}, {3, 4, 6}
            };

            for(int i = 0; i < 8; i++) {
                int count = 0;
                for(int j = 0; j < 3; j++) {
                    if(board[winCondition[i][j]] == currentDesig) {
                        count++;
                    }
                }

                //If it's three, then a win to the current desig
                if(count == 3) return true;
            }

            return false;
        }

        bool checkValidMove(int pos) {
            vector<int> validMoves = getValidMoves();
            for(int i = 0; i < validMoves.size(); i++) {
                if(validMoves[i] == pos) return true;
            }

            return false;
        }
    public:
        Game() {
            this->board = vector<char>(9, '.');
        }

        void printBoard() {
            printf("%c %c %c\n", board[0], board[1], board[2]);
            printf("%c %c %c\n", board[3], board[4], board[5]);
            printf("%c %c %c\n", board[6], board[7], board[8]);

            cout << "Current player: " << CurrentPlayer.getName() << "\n";
        }

        void play(Player P1, Player P2) {
            system("clear");

            this->P1 = P1;
            this->P2 = P2;

            cout << "Game Start" << endl;

            //Set current player if it's null
            if(CurrentPlayer.getName() == "NULL") CurrentPlayer = P1;

            gameLoop();
        }

        void clearBoard() {
            board = vector<char>(9, '.');
        }

        void gameLoop() {
            loop:
            clearBoard();
            while(!isBoardFull()) {
                string currentName = CurrentPlayer.getName();
                char currentDesig = CurrentPlayer.getDesig();

                //Player 1
                if(currentName == "Player1") {
                    //Print board
                    printBoard();

                    //Input
                    int pos;
                    do{
                        cout << "Enter move (" << currentDesig << ") : "; cin >> pos; cout << "\n";
                        if(!checkValidMove(pos)) {
                            cout << "Invalid move. Try again\n";
                        }
                    } while (!checkValidMove(pos));

                    //If valid
                    board[pos] = currentDesig;
                    
                    //Change current to the other person
                    CurrentPlayer = P2;
                }
                
                //Player 2
                if(currentName == "Player2") {
                    //Print board
                    printBoard();

                    //Input
                    int pos;
                    do{
                        cout << "Enter move (" << currentDesig << ") : "; cin >> pos; cout << "\n";
                        if(!checkValidMove(pos)) {
                            cout << "Invalid move. Try again\n";
                        }
                    } while (!checkValidMove(pos));

                    //If valid
                    board[pos] = currentDesig;
                    
                    //Change current to the other person
                    CurrentPlayer = P1;
                }

                //Check win condition
                if(checkWin(currentDesig)) {
                    cout << currentName << " Won!!!" << "\n";
                    break;
                }
            }

            //Check if it's broken bcs of full board or a win
            if(isBoardFull()) {
                cout << "The result is a Draw" << "\n";
            } 

            //play again
            char inst;
            cout << "Play again? (y/n) "; cin >> inst;
            if(inst < 'a') inst += ('a' - 'A');

            if(inst == 'y') {
                goto loop;
            }
        }
};

int main() {
    Game game;
    Player p1("Player1", 'X');
    Player p2("Player2", 'O');
    
    game.play(p1, p2);
}