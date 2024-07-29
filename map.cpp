#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(){
    int N = 9;
    ifstream solution("SATOUT.txt");
    string buff;
    solution >> buff;
    vector<vector<int>> sudoku_ans(N, vector<int>(N));
    for(int i = 0 ; i < N ; i++){
    	for(int j = 0 ; j<N ; j++){
    		for(int m = 1 ; m<=N ; m++){
    			int elm;
    			solution >> elm;
    			if(elm > 0){
    				sudoku_ans[i][j] = m;
    			}
    		}
    	}
    }
	
    ofstream sudoku_answer("sudoku_solution.txt");
    sudoku_answer << "\n\n";
    cout << "\n\n";
    for(int i = 0 ; i<N ; i++){
    	for(int j = 0 ; j<N ; j++){
    		sudoku_answer << sudoku_ans[i][j] <<" ";
    		cout<< sudoku_ans[i][j] << " ";
    	}
    	sudoku_answer << "\n";
    	cout<< "\n";
    }
}
