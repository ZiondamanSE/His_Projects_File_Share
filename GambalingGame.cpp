#include <iostream> // Printing and consol control
#include <string> // bace string packege
#include <ctime> // Random
#include <thread> // Extra System control

using namespace std;

int totoal_User_Balence;
string user_Input; // Handels User Inputs

// Game Values
int player_Score, player_Per_Round_Bet, p_Dice_Roal1, p_Dice_Roal2;
int computer_Score, computer_Per_Round_Bet, c_Dice_Roal1, c_Dice_Roal2;
int robot_Betting[3] = {100, 300, 500}; // Set Robot Betting Values
int total_Game_pot, round_Total;

bool round_is_Compleated, robot_is_Playering;

// Function declarations
void Start_Menu_UI();
void Menu_UI_Controler(string Player);
void Game_Instrushons();
void Game_Maniger();
void Round_Maniger();
void ScoreUI();
void Betting_Maniger();
void End_Maniger(bool user_won_Game);

/* Asking User to Deposit Cash */
void Depositing_Cash() {
    // Prompting User to set in Cash
    cout << "Please Deposit Cash Before starting the game" << endl;
    cout << "Deposit : ";
    cin >> totoal_User_Balence;

    // Preventing User to over/under Deposit
    while (totoal_User_Balence < 100 || totoal_User_Balence > 5000)
    {
        if (totoal_User_Balence < 100)
            cout << "Insufficient funds, minimal deposit 100sek. please try again" << endl;
        else
            cout << "Insufficient funds, Maximum deposit 5000sek. please try again" << endl;

        cout << "Deposit : ";
        cin >> totoal_User_Balence;
    }

    system("cls"); //clears text
}

/* Handels the Writing Out the UI */
void Start_Menu_UI() {
    // Write outs the Main Menu
    cout << "--------------------" << endl;
    cout << "Welcome to betting land" << endl;
    cout << "Your Current Balance is: " << totoal_User_Balence << endl;
    cout << "--------------------" << endl;
    cout << endl;
    cout << "1 : Play Against computer." << endl;
    cout << "2 : How to play game" << endl;
    cout << "3 : Quit Game" << endl;
    cout << "Please enter your choice: ";

    // Collects user input and puts atchon
    cin >> user_Input;
    Menu_UI_Controler(user_Input);

    system("cls"); //clears text

}

/* Handels User Menu Input */
void Menu_UI_Controler(string Player) {
    // faile safe if user selcects outside main optisons
    while (user_Input != "1" && user_Input != "2" && user_Input != "3")
    {
        cout << "Invalid choice, please try again: ";
        cin >> user_Input;
    }

    system("cls"); //clears text

    // Turns input into Acthson
    if (user_Input == "1") { system("cls"); Game_Maniger(); }
    else if (user_Input == "2") { system("cls"); Game_Instrushons(); }
    else if (user_Input == "3") { system("cls"); return; }
}

/* Prints Out Game Instushons For New Players */
void Game_Instrushons() {
    // Write outs Game Instushons for player
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

    // ask for user input
    cout << "Press anything to go back to menu: ";
    cin >> user_Input;

    system("cls"); // clears text

    // Sends user back to main menu
    if (!user_Input.empty()) { Start_Menu_UI(); }
}

/* Main Game Maniger Handels Rounds and Points */
void Game_Maniger() {
    // Clears old Game values
    player_Score = 0;
    computer_Score = 0;

    cout << "Starting game... " << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Makes system wait 2 Seconds

    system("cls");

    // Provents Extra rounds Playing
    while (player_Score < 2 && computer_Score < 2 && round_Total != 3)
    {
        Betting_Maniger();
        Round_Maniger(); // Playes a Round
        ScoreUI(); // writes out Round winner
    }

    // Writes out the winner
    if (player_Score >= 2)
        End_Maniger(1);
    else if (computer_Score >= 2)
        End_Maniger(0);

}

/* Main Round Maniger Handels Dice Rolling and Turns */
void Round_Maniger() {

    // Clears values Per Round
    p_Dice_Roal1 = 0; p_Dice_Roal2 = 0;
    c_Dice_Roal1 = 0; c_Dice_Roal2 = 0;
    robot_is_Playering = false;

    // Player rolls two dice
    p_Dice_Roal1 = rand() % 6 + 1;
    p_Dice_Roal2 = rand() % 6 + 1;
    cout << "Your dice landed on: " << p_Dice_Roal1 << " and " << p_Dice_Roal2 << endl;

    this_thread::sleep_for(chrono::seconds(4)); // Makes system wait 4 Seconds for user understandment
    system("cls");

    cout << "Computer is now playing..." << endl;
    cout << endl;
    this_thread::sleep_for(chrono::seconds(4)); // Makes system wait to emnulate computer is playing
    system("cls");

    // Computer Beting System
    robot_is_Playering = true;
    computer_Per_Round_Bet = robot_Betting[rand() % 3];

    // Rolls two dice
    c_Dice_Roal1 = rand() % 6 + 1;
    c_Dice_Roal2 = rand() % 6 + 1;

    // writes out reslult
    cout << "Robot rolled: " << c_Dice_Roal1 + c_Dice_Roal2 << endl;
    cout << "The Game Pot is: " << total_Game_pot << " SEK" << endl;

    round_Total++;

    this_thread::sleep_for(chrono::seconds(4));
    robot_is_Playering = false;
    system("cls");

}

/* Writes Round Score and Points */
void ScoreUI() {

    cout << "--------------------" << endl;
    cout << "ROUND RESULTS" << endl;
    cout << "--------------------" << endl;
    cout << endl;

    cout << "Total Game Pot: " << total_Game_pot << " SEK" << endl;
    cout << endl;

    cout << "Your Dice Roll:" << endl;
    cout << "Dice 1: " << p_Dice_Roal1 << endl;
    cout << "Dice 2: " << p_Dice_Roal2 << endl;
    cout << "Your Total Score: " << (p_Dice_Roal1 + p_Dice_Roal2) << endl;
    cout << endl;

    cout << "Computer Dice Roll:" << endl;
    cout << "Dice 1: " << c_Dice_Roal1 << endl;
    cout << "Dice 2: " << c_Dice_Roal2 << endl;
    cout << "Computer Total Score: " << (c_Dice_Roal1 + c_Dice_Roal2) << endl;
    cout << endl;

    cout << "--------------------" << endl;

    // Determine and display winner
    if ((p_Dice_Roal1 + p_Dice_Roal2) > (c_Dice_Roal1 + c_Dice_Roal2))
    {
        cout << "CONGRATULATIONS! YOU WON THIS ROUND!" << endl;
        player_Score++;
    }
    else if ((p_Dice_Roal1 + p_Dice_Roal2) < (c_Dice_Roal1 + c_Dice_Roal2))
    {
        cout << "YOU LOST! COMPUTER WINS THIS ROUND!" << endl;
        computer_Score++;
    }
    else
    {
        cout << "IT'S A TIE!" << endl;
        cout << "No one gets a point this round" << endl;
    }

    cout << "Current Score - You: " <<player_Score << " Robot: " << computer_Score << endl;
    cout << "Press any key to continue...";
    cin >> user_Input;

    system("cls");
}

/* Main Betting Manigers Handels Betting and Final Pot */
void Betting_Maniger() { // add comments later on

    // Proventing user to bet with imagenerty cash
    if (totoal_User_Balence == 100) {
        cout << "You only have 100sek left do you wish to go all in? (y/n): " << endl;
        cin >> user_Input;

        // Going All in System
        if (user_Input == "y") {
            total_Game_pot = totoal_User_Balence;
            totoal_User_Balence = 0;
        } else {
            Start_Menu_UI();
            return;
        }

        system("cls");
    }
    else if (totoal_User_Balence < 300) {
        cout << "You can only bet 100sek" << endl;
        cout << "Press any key to bet 100sek: ";
        cin >> user_Input;
        player_Per_Round_Bet = 100;

        // adding to the pot att
        total_Game_pot = player_Per_Round_Bet;
        totoal_User_Balence -= player_Per_Round_Bet;

        system("cls");
    }
    else if (totoal_User_Balence < 500) {
        cout << "You can bet 100 or 300sek" << endl;
        cout << "Enter your bet (100 or 300): ";
        cin >> player_Per_Round_Bet;

        while (player_Per_Round_Bet != 100 && player_Per_Round_Bet != 300) // proventing player to give an invaled input
        {
            cout << "you have entered wrong betting value  ";
            cout << "Please Set put in your initial bet" << endl;
            cout << "Bet must be in 100, 300sek : ";
            cin >> player_Per_Round_Bet;
        }

        // adding to the pot att
        total_Game_pot = player_Per_Round_Bet;
        totoal_User_Balence -= player_Per_Round_Bet;

        system("cls");
    }
    else if (totoal_User_Balence >= 500)
    {
        cout << "Please Set put in your initial bet" << endl;
        cout << "Bet must be in 100, 300, 500sek : ";
        cin >> player_Per_Round_Bet;
        cout << endl;

        while (player_Per_Round_Bet != 100 && player_Per_Round_Bet != 300 && player_Per_Round_Bet != 500)
        {
            cout << "you have entered wrong betting value  ";
            cout << "Please Set put in your initial bet" << endl;
            cout << "Bet must be in 100, 300, 500sek : ";
            cin >> player_Per_Round_Bet;
        }

        total_Game_pot = player_Per_Round_Bet;
        totoal_User_Balence -= player_Per_Round_Bet;

        system("cls");
    }
    else {
        cout << "you insafishent funds to bed.";
        this_thread::sleep_for(chrono::seconds(4));
        system("cls");

    }
}

/* Main End Game Maninger Decaling Who Wone and Deposit The Cash To the Winner */
void End_Maniger(bool user_won_Game) {

    if (user_won_Game == true)
    {
        cout << "CONGRATULATIONS! YOU WON!" << endl;
        cout << "You receive: " << total_Game_pot + computer_Per_Round_Bet << " SEK" << endl;
        totoal_User_Balence += total_Game_pot + computer_Per_Round_Bet;
    }
    else if (user_won_Game == false)
    {
        cout << "YOU LOST! ROBOT WINS!" << endl;
        cout << "You lose: " << total_Game_pot << " SEK" << endl;
        // Money already deducted in betting, no need to deduct again
    }

    cout << "Your new balance is: " << totoal_User_Balence << " SEK" << endl;
    cout << "Press any key to return to main menu...";
    cin >> user_Input;

    system("cls");
    Start_Menu_UI();

}

/* Main Start up Code Runner (Mainy starts up the game) */
int main() {
    srand(time(0)); // Initialize random seed

    Depositing_Cash();
    Start_Menu_UI();

    cin.ignore();
    cin.get();
    return 0;
}