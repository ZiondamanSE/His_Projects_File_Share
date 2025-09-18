#include <iostream>
#include <string>
using namespace std;

// Forward declarations
static void DepostingBallens();
static void Star_Game(string userInput);
static void HowToPlay();
static void PlayingGame();
static void startUpMessige();

// Global variables
int userBallens; // Starting pot
string userInput;

int main()
{
    DepostingBallens();
    startUpMessige();
    return 0;
}

static void DepostingBallens()
{
    cout << "Pleaces Deposit Cash Before starting the game" << endl;
    cout << "Desposit : ";
    cin >> userBallens;

    while (userBallens < 100 || userBallens > 5000)
    {
        if (userBallens > 100)
            cout << "insinicent funds, minnimal deposit 100sek. pleace try agin" << endl;
        else
            cout << "insinicent funds, Maximall deposit 5000sek. pleace try agin" << endl;

        cout << "Desposit : ";
        cin >> userBallens;
    }
}

// Writes out the menu
static void startUpMessige()
{
    cout << "--------------------" << endl;
    cout << "Welcome to betting land" << endl;
    cout << "Your Current Balance is: " << userBallens << endl;
    cout << "--------------------" << endl;
    cout << endl;
    cout << "1 : Play Against computer." << endl;
    cout << "2 : How to play game" << endl;
    cout << "3 : Quit Game" << endl;
    cout << "Please enter your choice:";

    cin >> userInput;
    Star_Game(userInput);
}


// Validates the input form the user for the start up menu
static void Star_Game(string userInput) {
    while (userInput != "1" && userInput != "2" && userInput != "3")
    {
        cout << "Invalid choice, please try again: ";
        cin >> userInput;
    }

    if (userInput == "1") { system("cls"); PlayingGame(); }
    else if (userInput == "2") { system("cls"); HowToPlay(); }
    else if (userInput == "3") { system("cls"); return; }
}

// writes out the instrushons for the game works for new players
static void HowToPlay()
{
    cout << "--------------------" << endl;
    cout << "HOW TO PLAY THE GAME" << endl;
    cout << "--------------------" << endl;

    cout << endl;
    cout << "Press anything to go back to menu: ";
    cin >> userInput;
    if (!userInput.empty()) { startUpMessige(); }
}

// Starts up the game to and lets the player play
static void PlayingGame()
{
    cout << "Starting game... " << endl;

}
