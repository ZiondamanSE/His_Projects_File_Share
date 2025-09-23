#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Forward declarations
static void DepositingBalance();
static void startUpMessage();
static void Start_Game(string userInput);
static void HowToPlay();
static void GameSystem();
static void Round();
static void BettingSystem();
static void ScoreWriteout();
static void GameOver(bool playerwin);

// user values
int userBalance; // Starting pot
string userInput;
bool completeRound, robotIsPlaying;

// Main Values
int playerScore, userRoundBet, p_Dice1, p_Dice2;
int robotScore, robotRoundBet, r_Dice;
int robotBetting[3] = {100, 300, 500};

int gamePot;

// Main code Running
int main()
{
    DepositingBalance();
    startUpMessage();
    return 0;
}

// asking for User to deposit cash before entering
static void DepositingBalance()
{
    cout << "Please Deposit Cash Before starting the game" << endl;
    cout << "Deposit : ";
    cin >> userBalance;

    // preventing user to over deposit with maximal deposit of 5000sek
    while (userBalance < 100 || userBalance > 5000)
    {
        if (userBalance < 100)
            cout << "Insufficient funds, minimal deposit 100sek. please try again" << endl;
        else
            cout << "Insufficient funds, Maximum deposit 5000sek. please try again" << endl;

        cout << "Deposit : ";
        cin >> userBalance;
    }
    system("cls"); // clearing for the menu
}

// Writes message
static void startUpMessage()
{
    cout << "--------------------" << endl;
    cout << "Welcome to betting land" << endl;
    cout << "Your Current Balance is: " << userBalance << endl;
    cout << "--------------------" << endl;
    cout << endl;
    cout << "1 : Play Against computer." << endl;
    cout << "2 : How to play game" << endl;
    cout << "3 : Quit Game" << endl;
    cout << "Please enter your choice: ";

    cin >> userInput;
    Start_Game(userInput);
    system("cls");
}

// Validates the input from the user for the start up menu
static void Start_Game(string userInput) {
    while (userInput != "1" && userInput != "2" && userInput != "3")
    {
        cout << "Invalid choice, please try again: ";
        cin >> userInput;
    }

    if (userInput == "1") { system("cls"); GameSystem(); }
    else if (userInput == "2") { system("cls"); HowToPlay(); }
    else if (userInput == "3") { system("cls"); return; }
}

// writes out the instructions for the game works for new players
static void HowToPlay()
{
    cout << "--------------------" << endl;
    cout << "HOW TO PLAY THE GAME" << endl;
    cout << "--------------------" << endl;
    cout << endl;
    cout << "1. At the start, choose how much money to bet: 100, 300, or 500 SEK." << endl;
    cout << "2. The game is played in up to 3 rounds:" << endl;
    cout << "   - You and the computer each roll two dice." << endl;
    cout << "   - The higher total wins the round." << endl;
    cout << "   - If someone wins 2 rounds in a row, the 3rd round is skipped." << endl;
    cout << "3. If you win the game, you receive your bet plus the computer's bet." << endl;
    cout << "4. If you lose, your bet is deducted from your balance." << endl;
    cout << "5. You can play as many times as you want, until you choose to exit." << endl;
    cout << "6. If you have money left in your balance, you don't need to deposit again." << endl;
    cout << "7. Your total winnings and losses are tracked across all games." << endl;

    cout << endl;
    cout << "Press anything to go back to menu: ";
    cin >> userInput;
    if (!userInput.empty()) { startUpMessage(); }
}

// Starts up the game to and lets the player play
static void GameSystem()
{
    // Initialize game variables
    playerScore = 0;
    robotScore = 0;
    gamePot = 0;

    cout << "Starting game... " << endl;

    system("cls");

    while (playerScore < 2 && robotScore < 2)
    {
        Round();
        ScoreWriteout();
    }

    if (playerScore >= 2)
        GameOver(true);
    else if (robotScore >= 2)
        GameOver(false);
}

static void Round() {
    srand(time(0));

    // Initialize dice values
    p_Dice1 = 0;
    p_Dice2 = 0;
    robotIsPlaying = false;

    BettingSystem();

    // Player rolls two dice
    p_Dice1 = rand() % 6 + 1;
    p_Dice2 = rand() % 6 + 1;
    cout << "Your dice landed on: " << p_Dice1 << " and " << p_Dice2 << endl;

    cout << "Bot is now playing..." << endl;

    // Robot betting and rolling
    robotIsPlaying = true;
    robotRoundBet = robotBetting[rand() % 3];
    gamePot += robotRoundBet;

    r_Dice = (rand() % 6 + 1) + (rand() % 6 + 1);
    cout << "Robot rolled: " << r_Dice << endl;
    cout << "The Game Pot is: " << gamePot << " SEK" << endl;

    system("cls");
}

static void BettingSystem()
{
    if (!robotIsPlaying)
    {
        cout << "Please Set put in your initial bet" << endl;
        cout << "Bet must be in 100, 300, 500sek : ";
        cin >> userRoundBet;
        cout << endl;

        while (userRoundBet != 100 && userRoundBet != 300 && userRoundBet != 500)
        {
            cout << "you have entered wrong betting value  ";
            cout << "Please Set put in your initial bet" << endl;
            cout << "Bet must be in 100, 300, 500sek : ";
            cin >> userRoundBet;
        }

        gamePot += userRoundBet;
        system("cls");
    }
}

static void GameOver(bool playerwin)
{
    system("cls");
    if (playerwin == true)
    {
        cout << "CONGRATULATIONS! YOU WON!" << endl;
        cout << "You receive: " << gamePot << " SEK" << endl;
        userBalance += gamePot;
    }
    else if (playerwin == false)
    {
        cout << "YOU LOST! ROBOT WINS!" << endl;
        cout << "You lose: " << userRoundBet << " SEK" << endl;
        userBalance -= userRoundBet;
    }

    cout << "Your new balance is: " << userBalance << " SEK" << endl;
    cout << "Press any key to return to main menu...";
    cin.ignore();
    cin.get();
    startUpMessage();
}

static void ScoreWriteout()
{
    cout << "--------------------" << endl;
    cout << "ROUND RESULTS" << endl;
    cout << "--------------------" << endl;
    cout << endl;

    cout << "Total Game Pot: " << gamePot << " SEK" << endl;
    cout << endl;

    cout << "Your Dice Roll:" << endl;
    cout << "Dice 1: " << p_Dice1 << endl;
    cout << "Dice 2: " << p_Dice2 << endl;
    cout << "Your Total Score: " << (p_Dice1 + p_Dice2) << endl;
    cout << endl;

    cout << "Robot Dice Roll:" << endl;
    cout << "Robot Total Score: " << r_Dice << endl;
    cout << endl;

    cout << "--------------------" << endl;

    // Determine and display winner
    if ((p_Dice1 + p_Dice2) > r_Dice)
    {
        cout << "CONGRATULATIONS! YOU WON THIS ROUND!" << endl;
        playerScore++;
    }
    else if ((p_Dice1 + p_Dice2) < r_Dice)
    {
        cout << "YOU LOST! ROBOT WINS THIS ROUND!" << endl;
        robotScore++;
    }
    else
    {
        cout << "IT'S A TIE!" << endl;
        cout << "No one gets a point this round" << endl;
    }

    cout << "Current Score - You: " << playerScore << " Robot: " << robotScore << endl;
    cout << "Press any key to continue...";
}