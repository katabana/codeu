#include <iostream>
#include <vector>
#include <set>

using namespace std;
//iterating two times - first to copy the board
//not sure of its correctness
//probably something is missing but I do not know yet

struct Point {
    int x;
    int y;
    char val;
    int set_no;
};

//returns the set whom point belongs to
int findSet(struct Point point) {
    return point.set_no;
}

void unionSets(set<int> &sets, int set_to_erase, int set_to_stay) {

    sets.erase(set_to_erase);
    return;
}

int count_islands(vector <vector<char> > board) {

    int height = board.size();
    int width = board[0].size();
    int set_no = 0;
    set<int> sets; //for storing sets' numbers

    //initialize board with guards
    struct Point template_point;
    template_point.x = template_point.y = -1;
    template_point.val = 'F';
    template_point.set_no = -1;

    vector< vector<struct Point> > board_with_guards(height+1, vector<struct Point>(width+1, template_point));
    for(int i = 1; i < height + 1; i++){
        for(int j = 1; j < width + 1; j++){
            struct Point point;
            point.x = i - 1;
            point.y = j - 1;
            point.val = board[i-1][j-1];
            board_with_guards[i][j] = point;
        }
    }

    //set numbers on board are just for joining
    //their main point is to add to set sets and know which one to delete

    for(int i = 1; i < height + 1; i++){
        for(int j = 1; j < width + 1; j++) {
            if(board_with_guards[i][j].val == 'F')
                continue;
            else {
                board_with_guards[i][j].set_no = ++set_no;
                sets.insert(set_no);

                //join with upper neighbour if 'T'
                struct Point up = board_with_guards[i-1][j];
                if(up.val == 'T') {
                    int upperset_no = findSet(up);
                    unionSets(sets, set_no, upperset_no);
                    board_with_guards[i][j].set_no = upperset_no;
                }

                //join with left neighbour if 'T'
                struct Point left = board_with_guards[i][j-1];
                if(left.val == 'T' && up.val != 'T') {
                    int leftset_no = findSet(left);
                    unionSets(sets, board_with_guards[i][j].set_no, leftset_no);
                    board_with_guards[i][j].set_no = leftset_no;
                }
                if(left.val == 'T' && up.val == 'T') {
                    int upperset_no = findSet(up);
                    int leftset_no = board_with_guards[i][j-1].set_no;
                    if(leftset_no != upperset_no)
                        unionSets(sets, leftset_no, upperset_no);
                    board_with_guards[i][j-1].set_no = upperset_no;
                }
            }
        }
    }

    return sets.size();
}


int main() {

    //result 0
    vector< vector<char> > boardF(4, vector<char>(5, 'F'));
    cout << count_islands(boardF) <<endl;

    //result 1
    vector< vector<char> > board0(4, vector<char>(5, 'T'));
    cout<< count_islands(board0)<<endl;

    vector< vector<char> > board(4, vector<char>(5, 'F'));
    board[0][1] = board[1][0] = board[1][1] = board[2][2] = board[3][2] = 'T';
    board[0][3] = board[1][3] = board[0][4] = board[1][4] = 'T';
    board[0][2] = 'T';

    cout<<count_islands(board)<<endl; //result 2

    vector< vector<char> > board1(4, vector<char>(5, 'F'));
    board1[0][1] = board1[1][0] = board1[1][1] = board1[2][2] = board1[3][2] = 'T';
    board1[0][3] = board1[1][3] = board1[0][4] = board1[1][4] = 'T';
    cout<<count_islands(board1)<<endl; //result 3


    vector< vector<char> > board2(4, vector<char>(5, 'F'));
    board2[0][1] = board2[1][0] = board2[1][1] = board2[2][2] = board2[3][2] = 'T';
    board2[0][3] = board2[1][3] = board2[0][4] = board2[1][4] = 'T';
    board2[2][0] = board2[3][0] = board2[3][1] = 'T';
    cout<<count_islands(board2)<<endl; //result 2




    return 0;
}
