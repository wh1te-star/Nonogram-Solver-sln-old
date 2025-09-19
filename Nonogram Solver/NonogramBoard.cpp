#include <vector>

class NonogramBoard {
private:
	int rows;
	int columns;
	std::vector<std::vector<CellState>> board;

public:
	NonogramBoard(int rows, int cols);
	~NonogramBoard();

	NonogramBoard fillLine(int row, int column, Line line);
};