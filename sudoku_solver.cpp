#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
#include <chrono>

using namespace std;

bool isLegal(int n, int i, int j, vector<vector<int>> &board) {
    int dim = board.size();
    int box_dim = sqrt(dim);

 
    for (int p = 0; p < dim; p++) {
        if (board[i][p] == n) return false;
    }

    for (int q = 0; q < dim; q++) {
        if (board[q][j] == n) return false;
    }


    int startRow = i / box_dim * box_dim;
    int startCol = j / box_dim * box_dim;

    for (int row = startRow; row < startRow + box_dim; row++) {
        for (int col = startCol; col < startCol + box_dim; col++) {
            if (board[row][col] == n) return false;
        }
    }

    return true;
}


bool findVoids(vector<vector<int>> &board, int &row, int &col) {
    int dim = board.size();
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            if (board[r][c] == 0) {
            	row = r;
            	col = c;
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(vector<vector<int>> &board) {
    int row, col;
    if (!findVoids(board, row, col))
        return true;

    for (int num = 1; num <= 16; num++) {
        if (isLegal(num, row, col, board)) {
            board[row][col] = num;
            if (solveSudoku(board))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}


int main(){
	auto start = chrono::high_resolution_clock::now();
	int N = 16;
	ifstream inp("input.txt");

	vector<vector<int>> board(N,vector<int>(N));
	for(int i = 0 ; i<N ; i++){
		for(int j = 0 ; j<N ;j ++){
			inp >> board[i][j];
		}
	}

	if(!solveSudoku(board)){
		cout << "INVALID PROBLEM\n";
		return 0;
	}

	for(int i = 0 ; i<N ; i++){
		for(int j = 0 ; j<N ;j ++){
			cout << board[i][j] << " ";
		}
		cout<< "\n";
	}	

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Time taken : " << duration.count() << " seconds" << endl;

}