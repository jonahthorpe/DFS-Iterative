// AIMethodsDFSIterative.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
// used to store visited states for fast checking
#include <unordered_set>
// used for path
#include <stack>
// Used to write to file
#include <fstream>
#include <chrono> 
using namespace std::chrono;

using namespace std;

// define moves - better readability
enum Move {
	North,
	East,
	South,
	West,
	Null
};

class EightPuzzle {

public:

	string startState = "";
	unordered_set<string> visitedStates;
	string visitedStatesString = "";

	void getStartState(void) {
		// set up available tiles
		string boardTiles = "abcdefgh_";
		// set up current tile position
		int tile = 0;
		// initialise puzzle board
		string input = "";
		// while there a tiles to place
		while (boardTiles.length() != 0) {
			// output available tiles
			getTileMessage(tile, boardTiles);
			// gets user input
			cin >> input;
			// if input is empty change it a _
			// allows the user to input empty instead of _
			if (input == "empty") {
				input = "_";
			}
			// make suer input is of length 1
			// and is in available tiles
			if (input.length() == 1 and boardTiles.find(input) != string::npos) {
				// add it to the board
				startState.append(input);
				// remove from available tile
				boardTiles.erase(boardTiles.find(input), 1);
				// move onto next position
				tile++;
			}
			else {
				// otherwise not valid, give output message
				cout << "Choice not a valid tile, Please try again\n";
			}
		}

		//output start State
		for (int i = 0; i < 9; i++)
		{
			if (i % 3 == 0) {
				cout << "\n";
			}
			cout << startState[i];
			cout << " ";

		}
		cout << "\n";
	}



	void generateStates() {
		stack <string> stack;
		stack.push(startState);
		string currentState;
		vector<Move> validMoves;
		// iterate until there a no more states not visited
		while (!stack.empty()) {
			// make the states at the top of the stack the current state
			currentState = stack.top();
			// remove from stack
			stack.pop();
			// recheck if state has been visited
			// state in stack may have been visited at a later time
			if (visitedStates.find(currentState) == visitedStates.end()) {
				// mark state as visisted
				visitedStates.insert(currentState);
				// add state to visited string
				// used to output states as it is quicker than iterating through unorder set
				// or outputting as it searches
				visitedStatesString.append(currentState);
				visitedStatesString.append("\n");
				// get all possibles moves from current state
				validMoves = getValidMoves(currentState);
				// iterate through the moves
				for (Move move : validMoves) {
					// make move
					string newState = makeMove(move, currentState);
					// if new state has not been visisted
					if (visitedStates.find(newState) == visitedStates.end()) {
						// add it to the stack
						stack.push(newState);
					}
				}
			}
			
		}
	}


private:

	void getTileMessage(int tile, string boardTiles) {
		cout << "Available tiles: ";
		// ouput available tiles
		cout << boardTiles;
		// out put current position
		cout << "\nWhat tile would you like at ";
		// output the column
		cout << tile % 3;
		cout << ", ";
		// output the row
		cout << tile / 3;
		cout << "\n";
	}


	vector <Move> getValidMoves(string currentState) {
		// get valid moves from current states
		vector<Move> validMoves;
		// get the posistion of the empty set
		int emptyTileIndex = currentState.find("_");
		switch (emptyTileIndex) {
			// top left
		case (0):
			validMoves = { East, South };
			break;
			// top middle
		case (1):
			validMoves = { East, South, West };
			break;
			//top right
		case (2):
			validMoves = { South, West };
			break;
			// middle left
		case (3):
			validMoves = { North, East, South };
			break;
			// middle middle
		case (4):
			validMoves = { North, East, South, West };
			break;
			//middle right
		case (5):
			validMoves = { North, South, West };
			break;
			// bottom left
		case (6):
			validMoves = { North, East };
			break;
			// bottom middle
		case (7):
			validMoves = { North, East, West };
			break;
			// bottom right
		case (8):
			validMoves = { North, West };
			break;
		}
		return validMoves;
	}

	string makeMove(Move move, string currentState) {
		int emptyTileIndex = currentState.find("_");
		int newEmptyTileIndex;
		// get position of empty tile after move
		switch (move) {
		case North:
			newEmptyTileIndex = emptyTileIndex - 3;
			break;
		case South:
			newEmptyTileIndex = emptyTileIndex + 3;
			break;
		case East:
			newEmptyTileIndex = emptyTileIndex + 1;
			break;
		case West:
			newEmptyTileIndex = emptyTileIndex - 1;
			break;

		}
		// get tile value of that position
		char tileValue = currentState[newEmptyTileIndex];
		currentState[emptyTileIndex] = tileValue;
		currentState.replace(newEmptyTileIndex, 1, "_");

		return currentState;
	}
};


int main()
{

	// create state1
	EightPuzzle puzzle1;
	cout << "State 1\n";
	puzzle1.getStartState();
	// get all reachable states
	cout << "Getting States.\n";
	ofstream reachableStates1("reachableStates1.txt");
	auto start1 = high_resolution_clock::now();
	puzzle1.generateStates();
	auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1) * 1e-6 ;

	// To get the value of duration use the count() 
	// member function on the duration object 
	reachableStates1 << puzzle1.visitedStatesString;
	reachableStates1.close();
	cout << "Finished in ";
	cout << duration1.count();
	cout << " seconds\n";


	// ask if user wants to output the reachable states
	bool answer = false;
	string input;
	while (!answer) {
		cout << "Do you want to ouput the states? (yes or no) \n";
		cin >> input;
		if (input == "yes") {
			answer = true;
			cout << puzzle1.visitedStatesString;
		}
		else if (input == "no") {
			answer = true;
		}
		else {
			cout << "Not a valid input \n";
		}
	}

	// create state2
	EightPuzzle puzzle2;
	cout << "State 2\n";
	puzzle2.getStartState();
	// get all reachable states
	cout << "Getting States.\n";
	ofstream reachableStates2("reachableStates2.txt");
	auto start2 = high_resolution_clock::now();
	puzzle2.generateStates();
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2) * 1e-6;

	// To get the value of duration use the count() 
	// member function on the duration object 
	reachableStates2 << puzzle2.visitedStatesString;
	reachableStates2.close();
	cout << "Finished in ";
	cout << duration2.count();
	cout << " seconds\n";

	// ask if user wants to output the reachable states
	answer = false;
	while (!answer) {
		cout << "Do you want to ouput the states? (yes or no) \n";
		cin >> input;
		if (input == "yes") {
			answer = true;
			cout << puzzle1.visitedStatesString;
		}
		else if (input == "no") {
			answer = true;
		}
		else {
			cout << "Not a valid input \n";
		}
	}

	// output the number of reachable states (will always be 181400)
	cout << "The size of R(S1) is ";
	cout << puzzle1.visitedStates.size();
	cout << "\n";
	cout << "The size of R(S2) is ";
	cout << puzzle2.visitedStates.size();
	cout << "\n";

	// check if they share any states
	// if they do, there is no exlusive states (0)
	// if they don't, all states are exlusive (181400)
	cout << "The size of R(S1)/R(S2) is ";
	if (puzzle1.visitedStates.find(puzzle2.startState) != puzzle1.visitedStates.end()) {
		cout << 0;
	}
	else {
		cout << puzzle1.visitedStates.size();
	}
	// stop output terminal closing straight away after completion
	string end;
	cin >> end;
}
