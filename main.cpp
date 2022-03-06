#include <iostream>
#include <array>
#include <iterator>
#include <random>
#include <ctime>
#include <iomanip>
#include <chrono>

using namespace std;

std::array<int, 8> validateMovesFromPos(int posX, int posY, std::array<std::array<int, 8>, 8> &board);
void makeMove(int move, int &Xpos, int &y, array<array<int, 8>, 8>& board);
bool isValidMoveAvailable(array<int, 8> array1);
int knights_tour(array<array<int, 8>, 8> board);
int pickRandomMoveFromChoices(array<int, 8> listOfMoves);

int main() {
	array<array<int, 8>, 8> board{};

	int max{0};
	for (int k = 1; k <= 1000; ++k) {
		int result = knights_tour(board);
		if (result > max) max = result;
		cout << "Game #" << k << ":\tresult = " << result << endl;
	}
	cout << "Best game made " << max << " moves.." << endl;

	return 0;
}

int knights_tour(array<array<int, 8>, 8> board) {
	int totalMovesMade{0};

	int Xpos{4};   // start near center of chessboard
	int Ypos{3};

	array<int, 8> listOfValidMoves = validateMovesFromPos(Xpos, Ypos, board);

	while (isValidMoveAvailable(listOfValidMoves)) {
		totalMovesMade++;
		int move = pickRandomMoveFromChoices(listOfValidMoves);
//		cout << "#" << totalMovesMade << ": ";
		makeMove(move, Xpos, Ypos, board);
		listOfValidMoves = validateMovesFromPos(Xpos, Ypos, board);
	}

	return totalMovesMade;
}

int pickRandomMoveFromChoices(array<int, 8> listOfMoves) {
	std::default_random_engine engine{static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())};
	array<int, 8> arValidMoveNumbers{-1};

	int countValidMoves{0};
	int i{0};
	for ( ; i < listOfMoves.size(); i++) {
		if (listOfMoves[i] == 0) {
			arValidMoveNumbers[countValidMoves] = i;
			countValidMoves++;
		}

	}
	int choiceOfValidMove;
	if (countValidMoves > 1) {
		std::uniform_int_distribution<int> randomInt{0, countValidMoves};
		choiceOfValidMove = randomInt(engine);;
	} else {
		choiceOfValidMove = 0;
	}

	return arValidMoveNumbers[choiceOfValidMove];
}

bool isValidMoveAvailable(array<int, 8> listOfValidMoves) {
	for (auto move : listOfValidMoves) {
		if (move == 0) return true;
	}

	return false;
}

void makeMove(int move, int& Xpos, int& Ypos, array<array<int, 8>, 8>& board) {
	array<int, 8> horizontalMove{2, 1, -1, -2, -2, -1, 1, 2};
	array<int, 8> verticalMove{-1, -2, -2, -1, 1, 2, 2, 1};
	board[Xpos][Ypos] = 1;
//	cout << "Making move " << move << ", from " << Xpos << "," << Ypos << "  to  ";
	Xpos += horizontalMove[move];
	Ypos += verticalMove[move];
//	cout << Xpos << "," << Ypos << endl;
	board[Xpos][Ypos] = 1;
}

array<int, 8> validateMovesFromPos(int posX, int posY, array<array<int, 8>, 8> &board) {
	array<int, 8> horizontalMove{2, 1, -1, -2, -2, -1, 1, 2};
	array<int, 8> verticalMove{-1, -2, -2, -1, 1, 2, 2, 1};
	array<int, 8> valid{3, 3, 3, 3, 3, 3, 3, 3};
	for (auto i = 0; i < 8; i++) {
		if ((posX + horizontalMove[i]) >= 0 &&
		    (posX + horizontalMove[i]) <= 7) {
			valid[i] -= 1;
		}
		if ((posY + verticalMove[i]) >= 0 &&
		    (posY + verticalMove[i]) <= 7) {
			valid[i] -= 1;
		}
		if (valid[i] == 1) {
			if (board[posX + horizontalMove[i]][posY + verticalMove[i]] == 0) {
				valid[i] -= 1;
//				cout << "  valid!" << endl;
			}
		}

	}
	return valid;
}