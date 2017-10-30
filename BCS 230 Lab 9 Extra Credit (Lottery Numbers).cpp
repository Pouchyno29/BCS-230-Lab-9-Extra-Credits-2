/**
   Programmer's name    : Stanley
   Class                : BCS 230 Foundations of Computer Programming II
   Date                 : 11/01/2017
   Lab                  : Lab9 Extra Credits - 2
   Professor's name     : Moaath Alrajab
   Software uses        : Code:blocks
**/

/**
	Problem: You are assigned to program a game that simulates a monthly lottery.
	Every month, seven distinct random integers between 1 to 20 (inclusive) are
	drawn. Using a vector, do the followings:

		a. Generates seven distinct random numbers between 1 and 20 (inclusive)
			and stores them in a vector.

		b. Sorts the vector containing the lottery numbers.

		c. Prompts the player to select seven distinct integers between 1 and 20 and
		   stores the numbers in the vector.

		d. Determines whether the player guessed the lottery numbers correctly. If
		   the player guessed the lottery numbers correctly, it outputs the right
		   message.

	Your program should allow a player to play the game as many times as the
	player wants to play. Before each play, generate a new set of lottery numbers.
**/

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void banner();
void initializing(vector<int> lotteryNumbers,  vector<int> userNumbers);
void getNumber(vector<int> &lotteryNumbers);
void sortNumbers(vector<int> &lotteryNumbers, int size);
void displayNumbers( const vector<int> lotteryNumbers);
void takeInput(vector<int> &userNumbers);
bool checkNumber(const vector<int> lotteryNumbers, int temp);
void isWinnig(const vector<int> lotteryNumbers,  vector<int> userNumbers);
void getUserNumbersHistory();
void checkIfInRange(int &num);
void saveWiningNumbers(const vector<int> userNumbers);
void playAgain(vector<int> lotteryNumbers,  vector<int> userNumbers);
void saveLotteryNumbers(const vector<int> lotteryNumbers);
void getLotteryNumbersHistory();

int main()
{
    vector<int> lotteryNumbers;
    vector<int> userNumbers;

    initializing(lotteryNumbers,  userNumbers);

    return 0;
}

void initializing(vector<int> lotteryNumbers,  vector<int> userNumbers){
    banner();
    // Variable to take input from the user
    int option;
    // Variable to check if and when the user want to stop playing
    bool exit = false;

    do{
        // Show the user all option available
        cout << string(6, ' ') << "1. To play lottery." << endl;
        cout << string(6, ' ') << "2. To see your winning history." << endl;
        cout << string(6, ' ') << "3. To see the lottery numbers' history." << endl;
        cout << string(6, ' ') << "4. To quite." << endl;
        cout << string(6, ' ') << "Make a selection: ";
        // Take input from the user
        cin >> option;

        // Check if the user make the right selection base on the game menu
        if( (option < 1) || (option > 4)){
            // If it is not let the user know the number entered is not the right one
            cout << string(6, ' ') << endl << "You do not make the correct selection!!!" << endl;
            // Pause the game and wait for the user to press any key before continue
            cout << string(6, ' '); system("Pause");
            //Clean the screen before going to the main menu
            if (system("CLS")) {system("clean");}
            // Show the banner
            banner();
        }else{
           // Skip a line
           cout << endl;

            switch(option){
            case 1:
                // Let the user know what to enter
                cout << string(6, ' ') << "Please guess seven different numbers" << endl;
                cout << string(6, ' ') << "Between 1 and 20 inclusively." << endl;

                 // Generate seven random numbers for the lottery's numbers
                 getNumber(lotteryNumbers);
                 // Sort the lottery's numbers from smaller to larger
                 // sortNumbers(lotteryNumbers, 7);
                 // Display the lottery's numbers
                 // cout << string(6, ' ') << "The lottery numbers are: "; -- Uncomment this line for testing
                 // displayNumbers(lotteryNumbers);                        -- Uncomment this line for testing
                 // Take the seven numbers from the user
                 takeInput(userNumbers);
                 // Check if the user guess the right seven numbers
                 isWinnig(lotteryNumbers, userNumbers);
                 // Show the banner
                 banner();
                break;
            case 2:
                // Show all the user's winning numbers
                getUserNumbersHistory();
                // Pause the game and wait for the user to press any key before continue
                cout << string(6, ' '); system("Pause");
                //Clean the screen before going to the main menu
                if (system("CLS")) {system("clean");}
                 // Show the banner
                 banner();
                break;
            case 3:
                // Show all the lottery's numbers
                getLotteryNumbersHistory();
                // Pause the game and wait for the user to press any key before continue
                cout << string(6, ' '); system("Pause");
                //Clean the screen before going to the main menu
                if (system("CLS")) {system("clean");}
                 // Show the banner
                 banner();
                break;
            case 4:
                //
                cout << string(6, ' ') << "The game will be closed" << endl;
                exit = true;
                // Pause the game and wait for the user to press any key before continue
                cout << string(6, ' '); system("Pause");
                break;
            }
        }

    }while( exit != true );

}

// This function will generate all seven random numbers for the lottery
void getNumber(vector<int> &lotteryNumbers){

    //Make sure the lottery vector is empty before starting the game
    lotteryNumbers.clear();

    srand (time(NULL));
    int temp;
    // Variable to check if a number already on the list
    bool isExist = true;

    // Loop to generate all seven random numbers
    for(int index = 0; index < 7; index++){
        //generate 7 numbers between 1 and 20
        temp = (rand() % 20 + 1);
        // If it is the first number
        if(index < 1){
            // Then just add it to the vector
            lotteryNumbers.push_back(temp);
        }else{
            // If it is not the first number
            do{
                // Then check if that number is already on the vector
                 if(checkNumber(lotteryNumbers, temp) == true){
                    // If it is then get a new number
                    temp = (rand() % 20 + 1);
                 }else{
                     // If the new number is not on the vector
                     // Then break out of this loop
                    break;
                 }
            // Loop as long as the number is already on the vector
            }while(true);
            // if the number is not already on the vector
            // Add the new number to the vector
            lotteryNumbers.push_back(temp);
        }
    }
    // After all seven numbers are generate then save them to a file
    saveLotteryNumbers(lotteryNumbers);
    // Skip a line
    cout << endl;
}

/*
   The main purpose of this function was to sort the lottery's numbers
   From smaller to larger using Bubble, cause it is only seven numbers.
   But this function will also be used to sort the user's numbers.
*/
void sortNumbers(vector<int> &lotteryNumbers, int size){

	int temp;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(lotteryNumbers[j] > lotteryNumbers[j + 1]){
                temp = lotteryNumbers[j];
                lotteryNumbers[j] = lotteryNumbers[j + 1];
                lotteryNumbers[j + 1] = temp;
            }
        }
    }
}

// This function will be used to display the lottery's number
// A well as the user's numbers
void displayNumbers( const vector<int> lotteryNumbers){
    int size = lotteryNumbers.size();

    // Loop from one up to the size of the vector
    for(int index = 0; index < size; index++){
        // Print out each number from vector
        cout << lotteryNumbers[index] << " ";
    }
    // Skip a line when all the numbers are printed
    cout << endl;
}

// This function will be use to allow the user
// To enter all his/her seven numbers
void takeInput(vector<int> &userNumbers){

    // Clear the user's vector before taking input from the user
    userNumbers.clear();

    // Variable to take input from the user
    int num;
    // Determine the size of the vector
    int size = 7;
    // Loop from 1 up to seven to take seven numbers from the user
    for(int index = 0; index < size; index++){
         // Let the user know what number hi/she is entering
         cout << string(6, ' ') << "Please enter " << (index + 1) << " number: ";
         // Take a single number from the user
         cin >> num;

        // Check if the number is within range (1-20)
        checkIfInRange(num);

        // Check if it is the first number
        if(index < 1){
            // If it is then just add it to the list
            userNumbers.push_back(num);
        }else{
                // If it is not the first number
            do{
                // Then check if that number is already on the vector
                 if(checkNumber(userNumbers, num) == true){
                    // If it is then ask the user for a new number
                    cout << string(6, ' ') << num << " is already exist, please enter a different number: ";
                    cin >> num;
                    // Check if the new number is within range (1-20)
                    checkIfInRange(num);
                 }else{
                     // If the new number is not on the vector
                     // Then break out of this loop
                    break;
                 }
            // Loop as long as the number is already on the vector
            }while(true);
            // if the number is not already on the vector
            // Add the new number to the vector
            userNumbers.push_back(num);
    }

  }
}

// This function will Check if the current number is
// already on the vector
bool checkNumber(vector<int> lotteryNumbers, int temp){
    // Determine the size of the vector
    int size = lotteryNumbers.size();
    // Loop from 1 up to the size of the vector
    for(int index = 0; index < size; index++){
        // Check if each element of the vector is equal to the current number
        if(temp == lotteryNumbers.at(index)){
            // If it is then return true
            return true;
        }
    }
    // If we get to this point then the number is not on the vector
    return false;
}

// This function will check if the user win the game
// By guessing all seven numbers
void isWinnig(vector<int> lotteryNumbers,  vector<int> userNumbers){

    //Get the size of the
    int size = userNumbers.size();

    //Temporary save the user's numbers
    vector<int>temp = userNumbers;

    //Temporary save the lottery's numbers
    vector<int>temp2 = lotteryNumbers;

    // Sort the user's number from smaller to larger using Bubble sort
    sortNumbers(temp, size);

    // Sort the lottery's number from smaller to larger using Bubble sort
    sortNumbers(temp2, size);

    // Check if the user's number is the same as the lottery 's number
    if(temp == temp2){

        // If there are the same then the user won
        cout << endl << string(6, ' ') << "You have guess the right numbers." << endl;

        // Save the user's wining number to a file
           saveWiningNumbers(userNumbers);

        //Pause the screen and for any key to be pressed before continue
        cout << string(6, ' '); system("Pause");

        // Skip a line
        cout << endl;

        /* Ask the user if he/she wants to play again
           If yes then start a new game
           If no the go to the main menu
        */
        playAgain(lotteryNumbers, userNumbers);


    }else{ // if the user did not guess all seven numbers correctly
        // Skip a line
        cout << endl;
        // Let the user knows that he/she lose the game
        cout << string(6, ' ') << "You did not guess the right numbers." << endl;

        //Show the lottery's numbers that the user was supposed to guess correctly
        cout << string(6, ' ') << "The winning numbers are: ";
        cout << string(6, ' '); displayNumbers(lotteryNumbers);

        //Show the user his/her numbers
        cout << string(6, ' ') << "Your numbers are: ";
        cout << string(13, ' '); displayNumbers(userNumbers);

        //Pause the screen and for any key to be pressed before continue
        cout << string(6, ' '); system("Pause");

        //Skip a line
        cout << endl;

        /* Ask the user if he/she wants to play again
           If yes then start a new game
           If no the go to the main menu
        */
        playAgain(lotteryNumbers, userNumbers);

    }
}
/*
   This function will  print out the user's numbers from the file
   This function can also be used to let the user know how many times
   He/She won the lottery and from what numbers
*/
void getUserNumbersHistory(){

    //Clean the screen before showing the numbers
    if (system("CLS")) {system("clean");};
    // Show the banner
    banner();

    cout << string(6, ' ') << "Your wining lottery's numbers history." << endl;

    ifstream readNumber("WiningNumber.txt");

    int count = 0;
    string line;
    if(readNumber.is_open()){

        // Skip the first line on the file
        getline(readNumber,line);

        while(!readNumber.eof()){
            getline(readNumber, line);
            cout << string(6, ' ') << ++count << " - " << line << endl;
        }
    }
    cout << endl;
}

//This function check if the user enter a number between 1 and 20 including 1 and 20
void checkIfInRange(int &num){


     do{
        //If the new number is within range
        if( (num >= 1) && (num <= 20)){
            //Then get out of this loop
            break;
        }else{
            cout << string(6, ' ') <<  num << " is out of range!!!" << endl;
            //Ask for a new number
            cout << string(6, ' ') << "please enter a number between 1 and 20 inclusively: ";
            cin >> num;
            checkIfInRange(num);
        }

     }while(true);

}

// This function will save the user's winning numbers to a file
void saveWiningNumbers(const vector<int> userNumbers){

    ofstream saveNumber("WiningNumber.txt", ios::in |ios::out | ios::app  );
    // If the file is opened
    if(saveNumber.is_open()){

        // Before started saving the user's numbers move the cursor to the next line
        saveNumber << endl;

        // Set the vector's index to ZERO
        int index = 0;
        //While the vector's index is less than the size of the vector
        while(index < userNumbers.size()){
            // Save each number from the vector to the file
            saveNumber << userNumbers.at(index) << " ";
            // Add one to the index to move to the next number from the vector
            index++;
        }
        // Close the file
        saveNumber.close();
    }else{
        //If the numbers cant be save, let the user know
        cout << string(6, ' ') << "Numbers could not be save!!!" << endl;
    }
}

// This function is to check if the user wants to play again
void playAgain(vector<int> lotteryNumbers,  vector<int> userNumbers){
    //Set an option variable to take the user's input
    char option;
    // Show some messages
    cout << string(6, ' ') << "Do you want to play again?" << endl;
    cout << string(6, ' ') << "Enter Y/y for yes or N/n for no: ";
    // take user's input
    cin >> option;
    //Skip a few lines
    cout << endl << endl;
    // If the user enter Y
    if(option == 'Y' || option == 'y'){
       //Clean the screen before before start a new game
       if (system("CLS")) {system("clean");};
       // Show the banner
       banner();
       // Let the user know what to enter
       cout << string(6, ' ') << "Please guess seven different numbers" << endl;
       cout << string(6, ' ') << "Between 1 and 20 inclusively." << endl;
       // Generate seven random numbers for the lottery's numbers
       getNumber(lotteryNumbers);

       // Sort the lottery's numbers
       // sortNumbers(lotteryNumbers, 7);
       // Display the lottery's numbers
       //cout << string(6, ' ') << "The lottery numbers are: ";
       //displayNumbers(lotteryNumbers);

        // Take the seven numbers from the user
        takeInput(userNumbers);
        // Skip two lines
        cout << endl << endl;
        // Check if the user win the lottery by guessing the right seven numbers
        isWinnig(lotteryNumbers, userNumbers);
        // Skip two lines
        cout << endl << endl;
    }else{
        // If the user does not want to play, let the user know he/she will return to the main menu
        cout << string(6, ' ') << "You will return to the main menu..." << endl;
        // Pause the game and wait for the user to press any key before continue
        cout << string(6, ' '); system("Pause");
        //Clean the screen before going to the main menu
        if (system("CLS")) {system("clean");};
    }
}

// This function will save all the lottery's numbers to a file
void saveLotteryNumbers(const vector<int> lotteryNumbers){

    fstream saveNumber;
    saveNumber.open("LotteryNumbers.txt", ios::in | ios::out | ios::app );

    // If the file is opened
    if(saveNumber.is_open()){

        saveNumber << endl;

        // Set the vector index to ZERO
        int index = 0;
        // Loop as long as the index is less than the size of the vector
        while(index < lotteryNumbers.size()){
            // Save each number to the file
            saveNumber << lotteryNumbers.at(index) << " ";
            // Add one the index to move to the next number from the vector
            index++;
        }
        // Close the file
        saveNumber.close();
    }else{
        cout << string(6, ' ') << "Numbers could not be save!!!" << endl;
    }
}

// This function will print out all the lottery's number
void getLotteryNumbersHistory(){

    //Clean the screen before showing the numbers
    if (system("CLS")) {system("clean");};

    // Show the banner
    banner();

    cout << string(6, ' ') << "The lottery's numbers history." << endl;

    ifstream readNumber("LotteryNumbers.txt");

    int count = 0;
    string line;
    if(readNumber.is_open()){

        // Skip the first line on the file
          getline(readNumber,line);

        while(!readNumber.eof()){
            getline(readNumber, line);
            cout << string(6, ' ') << ++count << " - " << line << endl;
        }
    }
    // Skip a line
    cout << endl;
}

void banner(){
//if (system("CLS")) {system("clean");};          //Clean the screen before do anything
cout << endl;
cout << " ##############################################################################" << endl;
cout << " #####   ######  ########    ###    ##    ## ##       ######## ##    ##   #####" << endl;
cout << " #####  ##    ##    ##      ## ##   ###   ## ##       ##        ##  ##    #####" << endl;
cout << " #####  ##          ##     ##   ##  ####  ## ##       ##         ####     #####" << endl;
cout << " #####   ######     ##    ##     ## ## ## ## ##       ######      ##      #####" << endl;
cout << " #####        ##    ##    ######### ##  #### ##       ##          ##      #####" << endl;
cout << " #####  ##    ##    ##    ##     ## ##   ### ##       ##          ##      #####" << endl;
cout << " #####   ######     ##    ##     ## ##    ## ######## ########    ##      #####" << endl;
cout << " #####                                                                    #####" << endl;
cout << " #####  ##        #######  ######## ######## ######## ########  ##    ##  #####" << endl;
cout << " #####  ##       ##     ##    ##       ##    ##       ##     ##  ##  ##   #####" << endl;
cout << " #####  ##       ##     ##    ##       ##    ##       ##     ##   ####    #####" << endl;
cout << " #####  ##       ##     ##    ##       ##    ######   ########     ##     #####" << endl;
cout << " #####  ##       ##     ##    ##       ##    ##       ##   ##      ##     #####" << endl;
cout << " #####  ##       ##     ##    ##       ##    ##       ##    ##     ##     #####" << endl;
cout << " #####  ########  #######     ##       ##    ######## ##     ##    ##     #####" << endl;
cout << " #####                                                                    #####" << endl;
cout << " #####   ######  ######## ##    ## ######## ######## ########             #####" << endl;
cout << " #####  ##    ## ##       ###   ##    ##    ##       ##     ##            #####" << endl;
cout << " #####  ##       ##       ####  ##    ##    ##       ##     ##            #####" << endl;
cout << " #####  ##       ######   ## ## ##    ##    ######   ########             #####" << endl;
cout << " #####  ##       ##       ##  ####    ##    ##       ##   ##              #####" << endl;
cout << " #####  ##    ## ##       ##   ###    ##    ##       ##    ##             #####" << endl;
cout << " #####   ######  ######## ##    ##    ##    ######## ##     ##            #####" << endl;
cout << " ##############################################################################" << endl;
cout << endl;
}


