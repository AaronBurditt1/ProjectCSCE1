//Project 1
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <unistd.h>
using namespace std;

// Global constant variables
enum Matching{Match = 1, Display = 2, Giveup = 3, Exit = 4};
const int SIZE = 4;


// Function to get the users name
string getName() {
     bool validName = false;
     string userName;

  // This part of the code is too get the users input name and make sure it meets the requirements of an uppercase first and last name.
  while (validName == false){

      cout << "Please enter your name: "; // Takes the users input
      getline(cin, userName);

      bool isValid = true;
      for(int i = 0; i < userName.length(); i++){

          char userUpper = static_cast<char>(userName.at(i));

          if((isalpha(userUpper) == false) && (isspace(userUpper) == false)){
              cout << "That is not a valid input, please try again" << endl;
              isValid = false;
              break;
          }
      }

        if(isValid == true){
          userName.at(0) = toupper(userName.at(0));

          for (int i = 1; i < userName.length(); i++) {
                if (isspace(userName.at(i - 1)) && isalpha(userName.at(i))) {
                    userName.at(i) = toupper(userName.at(i));
                }
          }

          cout << "Welcome, " << userName << "." << endl;
          cout << endl;
          validName = true;
      }
  }
    return userName;
}

// Function to generate a random index for the array
int genRandomIndex() {
    return rand() % SIZE;
}

// function to shuffle genRandomIndex
void shuffle(int cardsinfo[][SIZE]){
    int shuffleLim = 15;

    for(int i = 0; i < shuffleLim; i++){
      int x1 = genRandomIndex();
      int y1 = genRandomIndex();

      int x2 = genRandomIndex();
      int y2 = genRandomIndex();

      int num1 = cardsinfo[x1][y1];
      int num2 = cardsinfo[x2][y2];

      cardsinfo[x1][y1] = num2;
      cardsinfo[x2][y2] = num1;
    }
}

void initialize(int cardsinfo[][SIZE], int cardS[][SIZE]){
    int cardIni = 1;

    for(int i = 0; i < SIZE; i++){
        for(int h = 0; h < SIZE; h++){
            cardsinfo[i][h] = cardIni;
            cardIni++;
            if(cardIni > 8){
                cardIni = 1;
            }
        }
    }

    for(int i = 0; i < SIZE; i++){
        for(int h = 0; h < SIZE; h++){
            cardS[i][h] = 0;
        }
    }
    shuffle(cardsinfo);
}

void showCards(int cardsinfo[][SIZE], int cardS[][SIZE], bool showReal = false){
    cout << " +-0-1-2-3-+" << endl;
    for(int i = 0; i < SIZE; i++){
        cout << i + 0 << "|";
        for(int h = 0; h < SIZE; h++){
             if((showReal == false) && (cardS[i][h] == 0)){
                cout << " *";
             }
             else{
                cout << " " << cardsinfo[i][h];
             }
        }
        cout << " |" << endl;
        }
        cout << " +---------+" << endl;
}

bool allFaceUp(const int cardS[][SIZE]){

    for(int i = 0; i < SIZE; i++){
        for(int h = 0; h < SIZE; h++){
            if(cardS[i][h] == 0){
                return false;
            }
        }
    }
    return true;
}

bool checkInput(const int cardS[][SIZE], int x, int y){
    if(x < 0 || x >= SIZE || y < 0 || y >= SIZE){
        return false;
    }
    else if(cardS[x][y] == 1){
        return false;
    }
    else{
        return true;
    }
}

void match(int cardS[][SIZE], int cardsinfo[][SIZE], int& numPoints){

    showCards(cardsinfo, cardS);
    int x1, y1, x2, y2;

    cout << "Please enter the coordinates for the first card in (x y) format: ";
    cin >> x1 >> y1;

    if(checkInput(cardS, x1, y1) == false){
        cout << "The coords that were entered were not correct, please try again" << endl;
        return;
    }

    cout << "Please enter the coordinates for the second card (x y): ";
    cin >> x2 >> y2;

    if(checkInput(cardS, x2, y2) == false){
        cout << "The coords that were entered were not correct, please try again" << endl;
        return;
    }

    if((x1 == x2) && (y1 == y2)){
        cout << "Please enter different coordinates these have already been used" << endl;
        return;
    }

    cardS[x1][y1] = 1;
    cardS[x2][y2] = 1;
    showCards(cardsinfo, cardS);

    if(cardsinfo[x1][y1] == cardsinfo[x2][y2]){
        numPoints += 5;
        cout << "The cards you picked were a match! Located at (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << " +5 points" << endl;
    }
    else{
        numPoints -= 1;

        cout << "The cards did not match. Located at (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << " -1 points please try again" << endl;

        sleep(5);

        cardS[x1][y1] = 0;
        cardS[x2][y2] = 0;

        system("clear");

    }
    cout << "Your updated points are: " << numPoints << endl;
}
void display(int cardsinfo[][SIZE], int cardS[][SIZE], int& numPoints){
    if(numPoints < 10){
        cout << "You must have at least 10 points to use display" << endl;
        return;
    }
    for(int i = 0; i < SIZE; i++){
        for(int h = 0; h < SIZE; h++){
            if(cardS[i][h] == 0){
                for(int x = 0; x < SIZE; x++){
                    for(int y = 0; y < SIZE; y++){
                        if((x != i || y != h) && (cardsinfo[x][y] == cardsinfo[i][h]) && (cardS[x][y] == 0)){
                            cardS[i][h] = 1;
                            cardS[x][y] = 1;
                            numPoints -= 10;
                            showCards(cardsinfo, cardS);
                            cout << "Your updated points are: " << numPoints << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << "No matching pairs left please try again" << endl;
}

int main (){

  srand(time(NULL));
  string userName;

  int cardsinfo[SIZE][SIZE];
  int cardS[SIZE][SIZE];


  cout << "+---------------------------------------------------------------------------------------------------------+" << endl;
  cout << "|                                  Computer Science and Engineering                                       |" << endl;
  cout << "|                           CSCE 1030 - Computer Science I - Section 003                                  |" << endl;
  cout << "|                        Names: Aaron Burditt, Saul B Castillo, Atishay Jain                              |" << endl;
  cout << "|                                  EUID: atb0188, sbc0143, aj0917                                         |" << endl;
  cout << "|         Emails: AaronBurditt@my.unt.edu, saulcastillo2@my.unt.edu, atishayjain2@my.unt.edu              |" << endl;
  cout << "+---------------------------------------------------------------------------------------------------------+" << endl;

  bool endGame = false;

  while(endGame == false){
    int numPoints = 50;
    initialize(cardsinfo, cardS);

    userName = getName();

    bool playGame = true;

    while((playGame == true) && (numPoints > 0)){

        cout << "+---| MENU |---+" << endl;
        cout << "| 1. MATCH     |" << endl;
        cout << "| 2. DISPLAY   |" << endl;
        cout << "| 3. GIVE UP   |" << endl;
        cout << "| 4. EXIT      |" << endl;
        cout << "+--------------+" << endl;
        cout << endl;
        cout << "Please enter a choice from the above menu: ";

        int userChoice;
        cin >> userChoice;


        switch(userChoice){
            case Match:
                match(cardS, cardsinfo, numPoints);

                if(allFaceUp(cardS)){
                    cout << "Congratulations, you have won the game!" << endl;
                    playGame = false;
                    endGame = true;
                }
                break;
            case Display:
                display(cardsinfo, cardS, numPoints);
                break;
            case Giveup:
                cout << "Are you sure you want to display all card? You will lose all progress. (Y, N): ";

                char userAnswer;
                cin >> userAnswer;

                if(toupper(userAnswer) == 'Y'){
                  cout << "Location of each card: " << endl;

                  showCards(cardsinfo, cardS, true);

                  cout << "Your final points are: " << numPoints << endl;
                  cout << "Thank you for playing! " << userName << endl;

                  playGame = false;
                  endGame = true;
                  break;
                }
                else{
                  break;
                }
            case Exit:
                cout << "Thank you for playing! " << userName << endl;
                playGame = false;
                endGame = true;
                break;
            default:
                cout << "That is an invalid number please refure to the menu and only use 1-4." << endl;
                break;

        }
    }
  }
    return 0;
}
