#include <iostream>
#include <vector>
#include <array>

using namespace std;

void DisplayCellsRow(const vector<bool>& cells);
vector<bool> ProcessCells(const vector<bool>& cells, const array<bool, 8>& rule);

int main()
{
	int cellsPerRow = 50;
	int iterations = 40;
	srand((unsigned int)time(nullptr));

	vector<bool> cells(cellsPerRow, false);
	//cells[cellsPerRow / 2] = true;

	for (int i = 0; i < 5; i++)
	{
		cells[rand() % (cells.size() - 1)] = true;
	}

	system("Color 0A");

	// rules
	array<bool, 8> rule30 = {0, 0, 0, 1, 1, 1, 1, 0};
	array<bool, 8> rule90 = {0, 1, 0, 1, 1, 0, 1, 0};
	array<bool, 8> rule110 = {0, 1, 1, 0, 1, 1, 1, 0};
	array<bool, 8> rule184 = {1, 0, 1, 1, 1, 0, 0, 0};

	// display iterations
	for (int i = 0; i < iterations; i++)
	{
		DisplayCellsRow(cells);
		cells = ProcessCells(cells, rule184);
	}
}

void DisplayCellsRow(const vector<bool>& cells)
{
	for (auto cell : cells)
	{
		if (cell)
		{
			cout << "X ";
		}
		else
		{
			cout << "- ";
		}
	}
	cout << "\n";
}

vector<bool> ProcessCells(const vector<bool>& cells, const array<bool, 8>& rule)
{
	vector<bool> processed(cells.size());

	for (int i = 0; i < processed.size(); i++)
	{
		bool states[3];
		states[0] = cells[(i - 1) % cells.size()];
		states[1] = cells[i];
		states[2] = cells[(i + 1) % cells.size()];

		bool state = false;

		if (states[0] && states[1] && states[2]) state = rule[0];
		else if (states[0] && states[1] && !states[2]) state = rule[1];
		else if (states[0] && !states[1] && states[2]) state = rule[2];
		else if (states[0] && !states[1] && !states[2]) state = rule[3];
		else if (!states[0] && states[1] && states[2]) state = rule[4];
		else if (!states[0] && states[1] && !states[2]) state = rule[5];
		else if (!states[0] && !states[1] && states[2]) state = rule[6];
		else if (!states[0] && !states[1] && !states[2]) state = rule[7];

		processed[i] = state;
	}

	return processed;
}