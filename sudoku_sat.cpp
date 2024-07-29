#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>
#include <string>
#include <stdexcept>

using namespace std;

int solve(const vector<vector<int>>& board) {
    int N = board.size(); // Generalize for any NxN board
    int block_size = sqrt(N);
    int count = 0;

    ofstream outputfile("clauses.txt", ios::trunc);
    if (!outputfile) {
        throw runtime_error("Error opening output file.");
    }

    // Trivial constraints
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0) {
                int linear_position = i * N + j;
                outputfile << (linear_position * N + board[i][j]) << " 0\n";
                count++;
            }
        }
    }

    // Row constraints
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                int a = i * N + j;
                int b = i * N + k;
                for (int m = 1; m <= N; m++) {
                    outputfile << -(a * N + m) << " " << -(b * N + m) << " 0\n";
                    count++;
                }
            }
        }
    }

    // Column constraints
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            for (int k = i + 1; k < N; k++) {
                int a = i * N + j;
                int b = k * N + j;
                for (int m = 1; m <= N; m++) {
                    outputfile << -(a * N + m) << " " << -(b * N + m) << " 0\n";
                    count++;
                }
            }
        }
    }

    // Block constraints
    for (int i = 0; i < N; i += block_size) {
        for (int j = 0; j < N; j += block_size) {
            vector<pair<int, int>> block_csp;
            for (int p = i; p < i + block_size; p++) {
                for (int q = j; q < j + block_size; q++) {
                    block_csp.emplace_back(p, q);
                }
            }
            for (size_t i = 0; i < block_csp.size(); i++) {
                for (size_t j = i + 1; j < block_csp.size(); j++) {
                    int a = block_csp[i].first * N + block_csp[i].second;
                    int b = block_csp[j].first * N + block_csp[j].second;
                    for (int m = 1; m <= N; m++) {
                        outputfile << -(a * N + m) << " " << -(b * N + m) << " 0\n";
                        count++;
                    }
                }
            }
        }
    }


    for(int i = 0 ; i< N ; i++) {
    	for(int j = 0 ; j<N; j++){
    		for(int k = 1 ; k<=N ; k++){
    			int position = i*N + j;
    			outputfile<< position*N + k << " ";
    		}
    		outputfile<<"0\n";
            count++;
    	}
    }


    return count;
}

int main() {
    int N = 9;
    auto start = chrono::high_resolution_clock::now();

    ifstream inputfile("input.txt");
    if (!inputfile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    vector<vector<int>> board(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inputfile >> board[i][j];
            // board[i][j] = 0;
        }
    }
    inputfile.close();

    int num_clauses = solve(board);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Time taken for encoding: " << duration.count() << " seconds" << endl;

    ofstream sat_inp("SATIN.cnf");
    if (!sat_inp) {
        cerr << "Error opening SAT input file." << endl;
        return 1;
    }

    ifstream clause("clauses.txt");
    if (!clause) {
        cerr << "Error opening clauses file." << endl;
        return 1;
    }

    sat_inp << "p cnf " << (N * N * N) << " " << num_clauses << "\n";
    string line;
    while (getline(clause, line)) {
        sat_inp << line << '\n';
    }

    sat_inp.close();
    clause.close();

    return 0;
}
