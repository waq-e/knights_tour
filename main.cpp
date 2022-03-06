#include <iostream>
#include <array>
#include <iterator>

using std::array;
using std::cout;
using std::endl;

std::array<int, 8> validateMovesFromPos(int posX, int posY, std::array<std::array<int, 8>, 8> &board);
void makeMove(int i, int &x, int &y, array<array<int, 8>, 8>& board);
bool isValidMoveAvailable(array<int, 8> array1);
void knights_tour(array<array<int, 8>, 8> array1);
int pickRandomMoveFromChoices(array<int, 8> array1);

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
	srand(time(0));
	int countValidMoves{0};
	int i{0};
	for ( ; i < listOfMoves.size(); i++) {
		if (listOfMoves[i] == 0) {
			arValidMoveNumbers[countValidMoves] = i;
			countValidMoves++;
		}

	}
//	cout << "L" << arValidMoveNumbers[0] << arValidMoveNumbers[1] << arValidMoveNumbers[2]
//		   << arValidMoveNumbers[3] << arValidMoveNumbers[4] << arValidMoveNumbers[5]
//		   << arValidMoveNumbers[6] << arValidMoveNumbers[7] << "choices#" << countValidMoves << endl;

	auto choiceOfValidMove = 0;
	if (countValidMoves > 1) {
		choiceOfValidMove = rand() % (countValidMoves);
	} else {
		choiceOfValidMove = 0;
	}
//	cout << "choice " << choiceOfValidMove << " " << arValidMoveNumbers[choiceOfValidMove] << endl;

	return arValidMoveNumbers[choiceOfValidMove];
}

bool isValidMoveAvailable(array<int, 8> array1) {
	if (array1[0] == 0) return true;
	if (array1[1] == 0) return true;
	if (array1[2] == 0) return true;
	if (array1[3] == 0) return true;
	if (array1[4] == 0) return true;
	if (array1[5] == 0) return true;
	if (array1[6] == 0) return true;
	if (array1[7] == 0) return true;
	return false;
}

void makeMove(int move, int &x, int &y, array<array<int, 8>, 8>& board) {
	array<int, 8> horizontalMove{2, 1, -1, -2, -2, -1, 1, 2};
	array<int, 8> verticalMove{-1, -2, -2, -1, 1, 2, 2, 1};
	board[x][y] = 1;
	cout << "Making move " << move << ", from " << x << "," << y << "  to  ";
	x += horizontalMove[move];
	y += verticalMove[move];
	cout << x << "," << y << endl;
	board[x][y] = 1;

}


array<int, 8> validateMovesFromPos(int posX, int posY, array<array<int, 8>, 8> &board) {
	array<int, 8> horizontalMove{2, 1, -1, -2, -2, -1, 1, 2};
	array<int, 8> verticalMove{-1, -2, -2, -1, 1, 2, 2, 1};
	array<int, 8> valid{3, 3, 3, 3, 3, 3, 3, 3};
	for (auto i = 0; i < 8; i++) {
//		cout << "\n  checking move #" << i
//			<< " (" << horizontalMove[i] << "," << verticalMove[i] << ")  x:"
//			<< posX << " y:" << posY
//			   << " (" << posX + horizontalMove[i] << "," << posY + verticalMove[i] << ") -- ";
		if ((posX + horizontalMove[i]) >= 0 &&
		    (posX + horizontalMove[i]) <= 7) {
			valid[i] -= 1;
//			cout << "hc";
		}
		if ((posY + verticalMove[i]) >= 0 &&
		    (posY + verticalMove[i]) <= 7) {
			valid[i] -= 1;
//			cout << "vc";
		}
		if (valid[i] == 1) {
			if (board[posX + horizontalMove[i]][posY + verticalMove[i]] == 0) {
				valid[i] -= 1;
//				cout << "oc";
//				cout << "  valid!" << endl;
			}
		}

	}
//	cout << valid[0] << valid[1] << valid[2] << valid[3] << valid[4] << valid[5] << valid[6] << valid[7] << endl;
	return valid;
}

//     0  1  2  3  4  5  6  7
//   -------------------------
//  0|  |  |  |  |  |  |  |  |
//   -------------------------
//  1|  |  |  |  |  |  |  |  |
//   -------------------------
//  2|  |  |  |  |  |  |  |  |
//   -------------------------
//  3|  |  |  |  |  |  |  |  |
//   -------------------------
//  4|  |  |  |  |  |  |  |  |
//   -------------------------
//  5|  |  |  |  |  |  |  |  |
//   -------------------------
//  6|  |  |  |  |  |  |  |  |
//   -------------------------
//  7|  |  |  |  |  |  |  |  |
//   -------------------------
