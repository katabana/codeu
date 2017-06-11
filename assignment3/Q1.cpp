#include <iostream>
#include <vector>
#include <list>
using namespace std;



list<string> searchFromPosition(int rows, int cols, char**board, bool **used, vector<string> dict, int x, int y, string word) {

    list<string> part;

    //unavailable position
    if(board[x][y] == '0' || (used[x-1][y-1] == true))
        return part;

    word = word + board[x][y];
    //present string is not prefix
    if(!dict.isPrefix(word)) {
        return part;
    }

    //mark as used
    used[x-1][y-1] = true;
    if(dict.isWord(word))
        part.insert(part.begin(), word);


    //check neighbours
    list<string> l;
    l = searchFromPosition(rows, cols, board, used, dict, x-1, y-1, word);
    part.merge(l);
    l = searchFromPosition(rows, cols, board, used, dict, x-1, y, word);
    part.merge(l);
    l = searchFromPosition(rows, cols, board, used, dict, x-1, y+1, word);
    part.merge(l);
    l = searchFromPosition(rows, cols, board, used, dict, x, y-1, word);
    part.merge(l);
    l = searchFromPosition(rows, cols, board, used, dict, x, y+1, word);
    part.merge(l);
    l = searchFromPosition(rows, cols, board, used, dict, x+1, y-1, word);
    part.merge(l);
    l = searchFromPosition(rows, cols, board, used, dict, x+1, y, word);
    part.merge(l);
    l = searchFromPosition(rows, cols, board, used, dict, x+1, y+1, word);
    part.merge(l);


    //delete duplicates
    part.unique();
    return part;
}


list<string> wordsSearch(int rows, int cols, char **board, vector<string> dict) {


    list<string> result;

    //create array with borders (for simpler checking bounds)
    char **board_w_borders = new char *[rows+2];
    for(int i = 0; i < rows+2; i++) {
        board_w_borders[i] = new char[cols+2];
    }
    //fill inside
    for(int i = 1; i < rows+1; i++) {
        for(int j = 1; j < cols+1; j++) {
            board_w_borders[i][j] = board[i-1][j-1];
        }
    }
    //fill borders - I assume that words consist only of letters, not numbers
    for(int i = 0; i < rows + 2; i++) {
        board_w_borders[i][0] = '0';
        board_w_borders[i][cols+1] = '0';
    }
    for(int i = 1; i < cols + 1; i++) {
        board_w_borders[0][i] = '0';
        board_w_borders[rows+1][i] = '0';
    }
    //create an array for checking used
    bool **used = new bool *[rows];
    for(int i = 0; i < rows; i++) {
        visited[i] = new bool[cols];
    }
    //initialize with 'false'
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            used[i][j] = false;
        }
    }

    //search from every char in the grid
    for(int i = 1; i < rows+1; i++) {
        for(int j = 1; j < cols+1; j++) {
            if(dict.isPrefix(board_w_borders[i][j]) == 1) {
                list<string> w = searchFromPosition(rows+2, cols+2, board_w_borders, used, dict, i, j, "");
            }
        }

    }

    return result;
}


int main() {

    int const rows = 4;
    int const cols = 5;
    vector<string> dict;
    vector<string>::iterator it;

    //add values to dict
    //(...)

    char **board = new char *[rows];
    for(int i = 0; i < cols; i++) {
        board[i] = new char[cols];
    }

    //fill board with values
    //(...)

    wordsSearch(rows, cols, board, dict);
    return 0;
}
