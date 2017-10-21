#include <iostream>
#include <cctype>
#include <fstream>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <unistd.h>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


const char empty    = 0;  // contains water
const int missed   = 3;  // shot into ocean
const int hit      = 4;  // shot and hit
const int P1 = 1;
const int P2 = 2;
const int c = 5;
const int b = 6;
const int d = 7;
const int s = 8;
const int p = 9;

int P1array[10][10];
int P2array[10][10];
int P1opp[10][10];
int P2opp[10][10];
int playernum = 1;
int c_count1;
int c_count2;
int b_count1;
int b_count2;
int d_count1;
int d_count2;
int s_count1;
int s_count2;
int p_count1;
int p_count2;
int P1hit = 0;
int P2hit = 0;

using namespace std;

void welcome();
void Topboard(int array[10][10]);   // (opponents - the one you want to shoot) (only shows hit or misses)
void Bottomboard(int array[10][10]); // this is the current players board (shows hit/misses/and occupied spaces)
void action(int array1[10][10], int array2[10][10], int array3[10][10], int array4[10][10]);
bool checktarget(int, int);
void resetboards(int array1[10][10], int array2[10][10], int array3[10][10], int array4[10][10]);

class Player{
private:
    int CarrierR;
    int CarrierC;
    int BattleshipR;
    int BattleshipC;
    int DestroyerR;
    int DestroyerC;
    int SubmarineR;
    int SubmarineC;
    int PatrolR;
    int PatrolC;
    int direction;

public:
    void Pos(int array[10][10]);
    bool checkvalid(int, int, int, int, int array[10][10]);
    void PlaceShip(int Player[10][10], int, int, int, int, char);
    void PlayerBoard(int array[10][10]);
};

void Player :: Pos(int array[10][10]){
    string currentplayer, opponent;
    if (playernum % 2 == 1){
        currentplayer = "Player 1";
        opponent = "Player 2";
    }
    else if (playernum %2 == 0){
        currentplayer = "Player 2";
        opponent = "Player 1";
    }

    // int CarrierR, BattleshipR, DestroyerR, SubmarineR, PatrolR, direction;
    // int CarrierC, BattleshipC, DestroyerC, SubmarineC, PatrolC;
    bool validity;  // might not have to declare
    cout<<BOLDBLUE<<currentplayer<<RESET<<", please select where you want the following ships to be placed.\nRemember that your ships cannot touch each other.\n"
       <<"***** Make sure "<<BOLDWHITE<<opponent<<RESET<<" is not looking *****\n"<<endl;
    PlayerBoard(array);
    // Carrier
    validity = true;
    do{
        cout<<"Please enter the co-ordinates to place your Aircraft Carrier (5 spaces) on the battlefield:"<<endl
             <<"Enter the row co-ordinate between number 1-10: ";
        cin>> CarrierR;
        cout<<"Enter the column co-ordinate between number 1-10: ";
        cin>> CarrierC;
        cout<<"Choose the direction to place your ship (1-4)\n"
            <<" 1. Left\n 2. Right\n 3. Up\n 4. Down\n";
        cin>> direction;
        validity = checkvalid(CarrierR, CarrierC, 5, direction, array);
    }while(validity == false);
    cout << "\033[2J\033[1;1H";
    PlaceShip(array, CarrierR, CarrierC, direction, 5, c);

    // Battleship
    validity = true;
    do{
        cout<<"Please enter the co-ordinates to place your Battleship (4 spaces) on the battlefield:"<<endl
            <<"Enter the row co-ordinate between number 1-10: ";
        cin>> BattleshipR;
        cout<<"Enter the column co-ordinate between number 1-10: ";
        cin>> BattleshipC;
        cout<<"Choose the direction to place your ship (1-4)\n"
            <<" 1. Left\n 2. Right\n 3. Up\n 4. Down\n";
        cin>> direction;
        validity = checkvalid(BattleshipR, BattleshipC, 4, direction, array);
    }while(validity == false);
    cout << "\033[2J\033[1;1H";
    PlaceShip(array, BattleshipR, BattleshipC, direction, 4, b);

    //Destroyer
    validity = true;
    do{
        cout<<"Please enter the co-ordinates to place your Destroyer (3 spaces) on the battlefield:"<<endl
            <<"Enter the row co-ordinate between number 1-10: ";
        cin>> DestroyerR;
        cout<<"Enter the column co-ordinate between number 1-10: ";
        cin>> DestroyerC;
        cout<<"Choose the direction to place your ship (1-4)\n"
            <<" 1. Left\n 2. Right\n 3. Up\n 4. Down\n";
        cin>> direction;
        validity = checkvalid(DestroyerR, DestroyerC, 3, direction, array);
    }while(validity == false);
    cout << "\033[2J\033[1;1H";
    PlaceShip(array, DestroyerR, DestroyerC, direction, 3, d);

    //Submarine
    validity = true;
    do{
        cout<<"Please enter the co-ordinates to place your Submarine (3 spaces) on the battlefield:"<<endl
            <<"Enter the row co-ordinate between number 1-10: ";
        cin>> SubmarineR;
        cout<<"Enter the column co-ordinate between number 1-10: ";
        cin>> SubmarineC;
        cout<<"Choose the direction to place your ship (1-4)\n"
            <<" 1. Left\n 2. Right\n 3. Up\n 4. Down\n";
        cin>> direction;
        validity = checkvalid(SubmarineR, SubmarineC, 3, direction, array);
    }while(validity == false);
    cout << "\033[2J\033[1;1H";
    PlaceShip(array, SubmarineR, SubmarineC, direction, 3, s);

    //Patrol
    validity = true;
    do{
        cout<<"Please enter the co-ordinates to place your Patrol boat (2 spaces) on the battlefield:"<<endl
            <<"Enter the row co-ordinate between number 1-10: ";
        cin>> PatrolR;
        cout<<"Enter the column co-ordinate between number 1-10: ";
        cin>> PatrolC;
        cout<<"Choose the direction to place your ship (1-4)\n"
            <<" 1. Left\n 2. Right\n 3. Up\n 4. Down\n";
        cin>> direction;
        validity = checkvalid(PatrolR, PatrolC, 2, direction, array);
    }while(validity == false);
    cout << "\033[2J\033[1;1H";
    PlaceShip(array, PatrolR, PatrolC, direction, 2, p);
    cout << "\033[2J\033[1;1H";
}

bool Player :: checkvalid(int row, int col, int size, int dir, int Player[10][10]){
    if(row > 10 || row < 1 || col > 10 || col < 0){
        cout<<BOLDWHITE<<"**Invalid row/column inputs. Enter between 1-10.**\n\n"<<RESET;
        return false;
    }
    else if(dir > 4 || dir < 1){
        cout<<BOLDWHITE<<"**Invalid direction input. Enter between 1-4.**\n\n"<<RESET;
        return false;
    }
    else if((row < size && dir == 3) || (row > 10-size+1 && dir == 4) || (col < size && dir == 1) || (col > 10-size+1 && dir == 2)){
        cout<<BOLDWHITE<<"**Ship does not fit on board. Enter valid spaces.**\n\n"<<RESET;
        return false;
    }
    else{
        row--; col--;
        for(int i = 0; i <= size; i ++){
            if (dir == 1){
                if (Player[row][col-i] == c || Player[row][col-i] == b || Player[row][col-i] == d || Player[row][col-i] == s || Player[row][col-i] == p){
                    cout<<BOLDWHITE<<"**Cannot touch or overlap with another ship. Try a new location.\n\n"<<RESET;
                    return false;
                }
            }
            else if (dir == 2){
                if (Player[row][col+i] == c || Player[row][col+i] == b || Player[row][col+i] == d || Player[row][col+i] == s || Player[row][col+i] == p){
                    cout<<BOLDWHITE<<"**Cannot touch or overlap with another ship. Try a new location.\n\n"<<RESET;
                    return false;
                }
            }
            else if (dir == 3){
                if (Player[row-i][col] == c || Player[row-i][col] == b || Player[row-i][col] == d || Player[row-i][col] == s || Player[row-i][col] == p){
                    cout<<BOLDWHITE<<"**Cannot touch or overlap with another ship. Try a new location.\n\n"<<RESET;
                    return false;
                }
            }
            else if (dir == 4){
                if (Player[row+i][col] == c || Player[row+i][col] == b || Player[row+i][col] == d || Player[row+i][col] == s || Player[row+i][col] == p){
                    cout<<BOLDWHITE<<"**Cannot touch or overlap with another ship. Try a new location.\n\n"<<RESET;
                    return false;
                }
            }
        }
    }
    return true;
}

void Player :: PlaceShip(int Player[10][10], int r, int c, int dir, int length, char ship){
    r--;
    c--;
    for(int i = 0; i < length; i ++){
        if (dir == 1) //left
            Player[r][c-i] = ship;
        else if (dir == 2) //right
            Player[r][c+i] = ship;
        else if (dir == 3) //up
            Player[r-i][c] = ship;
        else if (dir == 4) //down
            Player[r+i][c] = ship;
    }
    PlayerBoard(Player);
}

void Player :: PlayerBoard(int array[10][10]){

    for(int a = 1; a <= 10; a++) { //letter coordinates
        cout << setw(5) << a;
    }
    cout << endl;
    for(int i = 0; i < 10; i++){ //number coordinates
        if(i == 9) cout << i+1;
        else cout << " " << i+1;  //to make it line up with the 10
        for(int j = 0; j < 10 ; j++) {

            if(array[i][j] == empty){  // remember that arrays pass by reference.
                cout << setw(5) << " |" ;
            }
            else if (array[i][j] == c || array[i][j] == b || array[i][j] == d || array[i][j] == s || array[i][j] == p){
                cout << setw(5) << "* |";
            }
        }
        cout << "\n  ";
        for(int a = 0; a < 10; a++)
            cout<<"~~~~|";
        cout<<"\n";
    }
}

void action(int P1[10][10], int P2[10][10], int P1opp[10][10], int P2opp[10][10]){            //current player will be displayed on bottom and opponent on top.
    // P1opp is when P1 is the opponent and P2 is current
    int x, y;
    if (playernum % 2 == 1){ // first time it goes through this, playernum = 3;
        cout<<BOLDBLUE<<"Player 1's"<<RESET<<" turn:";
        Topboard(P2opp);
        Bottomboard(P1);
        }
    else{
        cout<<BOLDBLUE<<"Player 2's"<<RESET<<" turn:";
        Topboard(P1opp);
        Bottomboard(P2);
    }

    // Coordinates to shoot
    bool spot_on;
    do{
        cout<< BOLDWHITE << "Choose your target" << RESET << endl<< "\nRow:";
        cin>> x;
        cout<< "\nColumn:";
        cin>> y;
        spot_on = checktarget(x,y);
    }while(spot_on != true);
    x--;
    y--;

    // CHECKS OTHER PLAYERS BOARD NOW
    if(playernum % 2 == 1){     // meaning P1 is current and P2 is not            // first time it goes through this, playernum = 3;
        if(P2[x][y] == c || P2[x][y] == b || P2[x][y] == d || P2[x][y] == s || P2[x][y] == p){
            cout << BOLDRED << "HIT!" << RESET << endl;
            //now check if boat is sunk
            if(P2[x][y] == c){
                c_count2++;
                if (c_count2 == 5) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P2[x][y] == b){
                b_count2++;
                if (b_count2 == 4) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P2[x][y] == d){
                d_count2++;
                if (d_count2 == 3) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P2[x][y] == s){
                s_count2++;
                if (s_count2 == 3) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P2[x][y] == p){
                p_count2++;
                if (p_count2 == 2) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            P2[x][y] = hit;
            P2opp[x][y] = hit;
            P2hit++;
            //Topboard(P2opp);  // not sure if this is aesthetically pleasing
        }
        else if (P2[x][y] == empty){
            cout << BOLDRED << "MISSED!" << RESET << endl;
            P2opp[x][y] = missed;   // and that should be it
        }
        else
            cout << "You\'ve already hit this target"<<endl;
    }
    else if (playernum % 2 == 0){
        if(P1[x][y] == c || P1[x][y] == b || P1[x][y] == d || P1[x][y] == s || P1[x][y] == p){
            cout << BOLDRED << "HIT!" << RESET << endl;
            // now check if a boat is sunk.
            if(P1[x][y] == c){
                c_count1++;
                if (c_count1 == 5) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P1[x][y] == b){
                b_count1++;
                if (b_count1 == 4) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P1[x][y] == d){
                d_count1++;
                if (d_count1 == 3) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P1[x][y] == s){
                s_count1++;
                if (s_count1 == 3) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            if(P1[x][y] == p){
                p_count1++;
                if (p_count1 == 2) cout<<BOLDYELLOW<<"SHIP SUNK"<<RESET<<endl;
            }
            P1[x][y] = hit;
            P1opp[x][y] = hit;
            P1hit++;
        }
        else if (P1[x][y] == empty){
            cout << BOLDRED << "MISSED!" << RESET << endl;
            P1opp[x][y] = missed;   // and that should be it
        }
    }

    if (P1hit == 17){
        for(int i = 0; i < 20; i++){
            usleep(15000);                //why doesnt this dooo anything!!
            cout<<".\n";
        }
        cout<<BOLDBLUE<<"PLAYER ONE WON"<<RESET<<endl;
        return;
    }
    else if (P2hit == 17){
        for(int i = 0; i < 35; i++){
            usleep(15000);                // didn't do anythinnnggg ugghhhh
            cout<<".\n";
        }
        //return 2;     // SHOULD return to main and say "winner" but it isn't.
        cout<<BOLDBLUE<<"PLAYER TWO WON"<<RESET<<endl;
        return;
    }

    // Ready for next turn

    playernum++;
    string playplay;
    if (playernum % 2 == 1){
        playplay = "Player 1";
    }
    else if (playernum %2 == 0){
        playplay = "Player 2";
    }

    cin.ignore();
    cout<<"Hit enter to continue";
    cin.ignore();
    cout << "\033[2J\033[1;1H";     //clears the terminal

    cout<<BOLDBLUE<<playplay<<RESET<<", hit enter to continue";
    cin.ignore();
    cout<< "\033[2J\033[1;1H";

    action(P1, P2, P1opp, P2opp);
}

bool checktarget(int x,int y){

    if(x>10 || x < 1 || y > 10 || y < 1){
        cout<<endl;
        cout<<BOLDWHITE<<"**Invalid Target**"<<RESET<<endl<<endl;
        return false;
    }
    else return true;
}

void Bottomboard(int array[20][10]) {                          // Shows occupied and hit (don't think we need to show missed?)
    cout<<endl<<BOLDWHITE<<"YOUR BOARD:"<<RESET<<endl;
    for(int a = 1; a <= 10; a++) { //letter coordinates
        cout << setw(5) << a;
    }
    cout<<endl;
    for(int i = 0; i < 10; i++) { //number coordinates
        if(i == 9)
            cout << i+1;
        else
            cout << " " << i+1 ;  //to make it line up with the 10

        for(int j = 0; j < 10 ; j++) {

            if(array[i][j] == c || array[i][j] == b || array[i][j] == d || array[i][j] == s || array[i][j] == p){
                cout << setw(5) << "* |" ;
            }
            else if(array[i][j] == hit ) {
            cout << setw(5) << "X |";
            }
            else cout << setw(5) << " |";
    }
        cout << "\n  ";
        for(int a = 0; a < 10; a++)
            cout<<"~~~~|";
        cout<<"\n";
    }
}

void Topboard(int array[10][10]) {  //                          // Only shows hit or missed
    cout<<endl<<BOLDWHITE<<"OPPONENT'S BOARD:"<<RESET<<endl;
    for(int a = 1; a <= 10; a++) { //letter coordinates
        cout << setw(5) << a;
    }
    cout << endl;
    for(int i = 0; i < 10; i++) { //number coordinates
        if(i == 9)
            cout << i+1;
        else
            cout << " " << i+1 ;  //to make it line up with the 10

        for(int j = 0; j < 10 ; j++) {

            if(array[i][j] == missed){
                cout<< setw(5) << "0 |";
            }
            else if(array[i][j] == hit){
                cout<< setw(5) << "X |";
            }
            else cout << setw(5) << " |" ;

    }
        cout << "\n  ";
        for(int a = 0; a < 10; a++)
            cout<<"~~~~|";
        cout<<"\n";
    }
}

void resetboards(int P1[10][10], int P2[10][10], int P1opp[10][10], int P2opp[10][10]){
        // create a blank board
    for (int x=0; x<10; x++) {
        for (int y=0; y<10; y++) {
            P1[x][y] = empty;
            P2[x][y] = empty;
            P1opp[x][y] = empty;
            P2opp[x][y] = empty;
        }
    }
}

int main(){
    int playagain;

    do{
    welcome();
    Player Player1;
    Player1.Pos(P1array);
    playernum++;
    Player Player2;
    Player2.Pos(P2array);
    playernum++;
    cout<<BOLDYELLOW<<"YOU ARE READY TO BEGIN"<<RESET<<endl<<"Remember to switch turns after each guess.\n";
      // insert any reminders we want to give the players.

    cin.ignore();
    cout<<"Hit enter to continue.\n";
    cin.ignore();
    cout << "\033[2J\033[1;1H";

    action(P1array, P2array, P1opp, P2opp);      // if this works, we can do a do-while loop so they can play again.

    cout<<"\n\n\n\n(0) Quit\n(1) Play Again"<<endl;
    cin>>playagain;
    if(playagain == 1) resetboards(P1array,P2array, P1opp, P2opp);
    }while(playagain != 0);
    cout<<BOLDWHITE<<"Thank you for playing!"<<RESET<<endl;
  return 0;

}

void welcome(){
    cout<< BOLDGREEN<<"Welcome to Battleship!"<<RESET<<endl<<"Battleship is a game for two players where you try "
        << "to guess the location of five ships your opponent has hidden on a grid.\n"
        << "Players take turns calling out a row and column, attempting to name a square containing enemy ships.\n\n";
    cout<<"Make sure to maximize the terminal and that your sound is on to get the full affect of the game!"<<endl<<endl;
    cout<< BOLDBLUE<<"Players: "<<RESET<<"2 players"<<endl<<endl;
    cout<< BOLDBLUE<<"Goal: "<<RESET<<"To sink all of your opponent's ships before he or she does the same to you."<<endl;
    cout<<"Press Enter to continue";
    cin.ignore();
    cout << "\033[2J\033[1;1H";  // this shifts up the terminal
}
