#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <ctype.h> // this library was included to enable the use of isdigit()
// which checks if a char is a digit or not. Although it could have been done with
// only the standard libs, utulizing this lib makes the code more readable and descriptive
// However, some could say that wouldn't be an issue with coding it manually and using
// comment to decribe what it does. Is this acceptable for this lab?

//CECS 130 Lab 9-
//Hieu Nguyen
// Tic-Tac-Toe Game
using namespace std;

//Defining Class
class Player{
	//Private members
	int score;
	public:
	Player(){
		cout<<"A new player has been created !"<<endl;
		this->score = 0;// initialize the player object's score referenced by "this"
	}
	void updateScore(){
		this->score++;// increasing score by one
	}
	void displayScore(){
		cout<< this->score<< endl;
	}	
};
// Function prototypes
void displayBoard(char cells[3][3]);
bool findCell(char userInput, char cells[3][3]);
void updateCell(int currentPlayer,char userInput,  char cells[3][3]);
bool checkGameStatus(char cells[3][3]);
int findCellAndUpdate(char userInput, char cells[3][3], int currentPlayer);
void randomCell(char cells[3][3]);
bool checkWinner(char cells[3][3], Player players[2]);
// Main program
int main(){
	srand(time(NULL));
	char cells[3][3]={{'1','2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; 
	char userInput;
	int currentPlayer = rand()%2;
	Player players[2]; // player[0] is the computer and player[1] is the use
	bool gameOver = false;
	int exitOrReset = 1;
	cout<< "Welcome to Tic-Tac-Toe"<< endl;
	

//Game Loop:
while(exitOrReset){ // true is associated with reset and false is associated with exit
		if(currentPlayer){ 
		// if the current player is 1(user)
		cout<< "You get to go first"<< endl;
		//if the current player is 0(computer)
		}else cout<< "the computer will go first"<< endl;
		
		//Loop for one Round
		while(!gameOver){
		//Code to be executed while the game is NOT over.
		if(currentPlayer){
			// code to be executed during the user's turn
			displayBoard(cells);
			cout<< "it's your turn"<< endl;
			cin >> userInput;
			if(findCellAndUpdate(userInput, cells, currentPlayer)){
				// if cell updated successfully
				currentPlayer = 0;
			}else // if cell update failed, the currentPlayer will remain the user
			 // until the cell is updated successfully
			 currentPlayer = 1;
				
		}else{// code to be executed during the computer's turn
			findCellAndUpdate(userInput, cells, currentPlayer);
			currentPlayer = 1;
		}
		//Checking Game status
		 if(checkGameStatus(cells) || checkWinner(cells,players)) {
		 	//code to be executed if there is no cell left OR there is a winner.
		 	gameOver = true;	// exit the loop for the round
		 }
		 // checking if it was a draw
		 if(checkGameStatus(cells)&& !checkWinner(cells,players)){
		 // if there are no cell left over, but there was NO winner
			cout<< "DRAW"<< endl;
		 }
		 	
		}
	//code to be executed when the game is over
	displayBoard(cells);
	cout<<"the game is over"<<endl;
	
	// displaying the score
	cout<< "Computer: ";
	players[0].displayScore();
	cout<< "User: ";
	players[1].displayScore();
	
	// asking the user if they want to reset or exit the game
	cout << "Type (0) to Exit or (1) to Reset"<< endl;
	cin>> exitOrReset;
	if(exitOrReset){
	// code to be executed if the user enter 1(reset the game)
		char temp[9] = { '1','2','3','4','5','6','7','8','9' };
		int i, k, j = 0;
		for (i = 0; i < 3; i++) {
			for (k = 0; k < 3; k++) {
				cells[i][k] = temp[j];
				j++;
			}
		}
		gameOver = false;// starting the loop again
		currentPlayer = rand()%2; // randomly selecting who goes first again.
   }
}
//Program Exit
	return 0;
}

// displaying the board
void displayBoard(char cells[3][3]){
	cout<< "Enter a cell from 1-9"<<endl;
	int i,k;
	for(i = 0 ; i < 3; i++){
		for(k= 0; k<3;k++){
			cout<<cells[i][k]<<"  |  ";
		}
		cout<<endl;
		cout<<endl;
	}
}
// check if the cell is occupied or not
bool findCell(char userInput, char cells[3][3]){
	int i, k;
	bool takenOrNot=true;
	for(i = 0; i < 3; i++){
		for(k = 0 ; k <3; k++){
			if(userInput == cells[i][k]) takenOrNot = false;	
		}	
	}
	return takenOrNot; 
}
// picking a random cell for the computer
void randomCell(char cells[3][3]){
	int	i=rand()%3;
	int k= rand()%3;  
	while(!isdigit(cells[i][k])){
		i = rand()%3;
		k = rand()%3;
	}
	cells[i][k] = 'o';
}
// updating the cell
void updateCell(int currentPlayer,char userInput,  char cells[3][3]){
	int i, k;
	for(i = 0; i < 3; i++){
		for(k = 0 ; k <3; k++){
			if(userInput == cells[i][k]&& currentPlayer) {
				// code to be executed if the cell is available 
				//and the current player is 1 (User)
				cells[i][k] = 'x';	
			}	
		}	
	}
}
// calls both the findCell and updateCell
int findCellAndUpdate(char userInput, char cells[3][3], int currentPlayer){
	int successOrFail;
	switch(currentPlayer){
		case 0: // when it's the computer's turn
			randomCell(cells);
			break;
		case 1: // when it's the user's turn
			if(findCell(userInput,cells)){
				cout<< "the cell is not available"<< endl;
				successOrFail = 0;
			}else{
				updateCell(currentPlayer, userInput, cells);
				successOrFail = 1;
			}
			break;			
	}
	return successOrFail;
}
// checks the game status, it returns false if the game is not over and true if the game is over
bool checkGameStatus(char cells[3][3]){
	bool gameOver = true;
	int i , k;
	for(i = 0; i< 3; i++){
		for(k = 0; k < 3; k++){
			if(isdigit(cells[i][k])){
				gameOver = false;
				break;	
			}
		}
	}
	return gameOver;
}
// check winner
bool checkWinner(char cells[3][3], Player players[2]){
	int i, k;
	bool wasThereAWinner= false;		
	//checking horizontally
	if(!wasThereAWinner){
		for(i = 0 ; i < 3; i++){
			if(cells[i][0]== cells[i][1]&& cells[i][0]==cells[i][2]){
				wasThereAWinner = true;
				if(cells[i][0] =='x'){
					cout<< "the user Won!"<< endl;
					players[1].updateScore();
				}
				else{
					cout << "the computer Won!"<< endl;
					players[0].updateScore();
				}	
			}
		}	
	}	
	// check vertically
	if(!wasThereAWinner){ // if there was not a winner using the check above
		for(k = 0; k< 3; k++){
			if(cells[0][k]==cells[1][k]&& cells[0][k]== cells[2][k]){
				wasThereAWinner = true;
				if(cells[0][k]== 'x'){
					cout << "the user Won!"<< endl;
					players[1].updateScore();
				}
				else{
					cout << "the computer Won!"<< endl;
					players[0].updateScore();
				}
			}
		}
	}
	// checking diagonally
	if(!wasThereAWinner){ // if there was not winner using the checks above
		if(cells[0][0] == cells[1][1]&& cells[0][0] == cells[2][2] ){
				wasThereAWinner = true;
				if(cells[0][0]== 'x' || cells[0][2] == 'x' ){
					cout << "the user Won!"<< endl;
					players[1].updateScore();
				}
				else if(cells[0][0] == 'o' || cells[0][2] == 'o'){
					cout<< "the computer Won!" << endl;
					players[0].updateScore();
				}
			}
		else if(cells[0][2] == cells[1][1]&& cells[0][2] == cells[2][0]){
			wasThereAWinner = true;
			cout << "there is a winner diagonally"<< endl;
			if(cells[0][0]== 'x' || cells[0][2] == 'x' ){
				cout << "the user Won!"<< endl;
				players[1].updateScore();
			}
			else if(cells[0][0] == 'o' || cells[0][2] == 'o'){
				cout<< "the computer Won!" << endl;
				players[0].updateScore();
			}
		}
	}	
	// returns true if there was a winner or false otherwise.
	return wasThereAWinner;
}

