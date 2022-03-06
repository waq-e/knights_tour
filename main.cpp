#include <iostream>
#include <array>
#include <iterator>

using std::array;
using std::cout;
using std::endl;

std::array<int, 8> validateMovesFromPos(int posX, int posY, std::array<std::array<int, 8>, 8> &board);
void makeMove(int move, int &Xpos, int &y, array<array<int, 8>, 8>& board);
bool isValidMoveAvailable(array<int, 8> array1);
void knights_tour(array<array<int, 8>, 8> board);
int pickRandomMoveFromChoices(array<int, 8> listOfMoves);

int main() {
	array<array<int, 8>, 8> board{};

	knights_tour(board);

	return 0;
}

void knights_tour(array<array<int, 8>, 8> board) {
	int totalMovesMade{0};

	int Xpos{4};   // start near center of chessboard
	int Ypos{3};

	array<int, 8> listOfValidMoves = validateMovesFromPos(Xpos, Ypos, board);

	while (isValidMoveAvailable(listOfValidMoves)) {
		totalMovesMade++;
		int move = pickRandomMoveFromChoices(listOfValidMoves);
		cout << "#" << totalMovesMade << ": ";
		makeMove(move, Xpos, Ypos, board);
		listOfValidMoves = validateMovesFromPos(Xpos, Ypos, board);
	}



}

int pickRandomMoveFromChoices(array<int, 8> listOfMoves) {
	array<int, 8> arValidMoveNumbers{-1};
	srand(time(nullptr));
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
		choiceOfValidMove = rand() % (countValidMoves);
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"
void makeMove(int move, int& Xpos, int& Ypos, array<array<int, 8>, 8>& board) {
	array<int, 8> horizontalMove{2, 1, -1, -2, -2, -1, 1, 2};
	array<int, 8> verticalMove{-1, -2, -2, -1, 1, 2, 2, 1};
	board[Xpos][Ypos] = 1;
	cout << "Making move " << move << ", from " << Xpos << "," << Ypos << "  to  ";
	Xpos += horizontalMove[move];
	Ypos += verticalMove[move];
	cout << Xpos << "," << Ypos << endl;
	board[Xpos][Ypos] = 1;
}
#pragma clang diagnostic pop


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