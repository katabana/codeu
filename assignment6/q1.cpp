#include<iostream>
#include<vector>
#include<map>

using namespace std;


void PrintParking(vector<int> input_sequence) {

    for(int i = 0; i < input_sequence.size(); i++) {
        cout << input_sequence[i] << " ";
    }
    cout<<endl;
}

void SwitchCarWithFreeLot(vector<int> &input_sequence, vector<int> &desired_sequence, map<int, int> &positions_map, int current_id, int free_space_id) {

    int parked_car = desired_sequence[current_id];
    int parked_car_position = positions_map[parked_car];
    input_sequence[current_id] = parked_car;
    input_sequence[parked_car_position] = 0;
    positions_map[0] = parked_car_position;
    positions_map[parked_car] = free_space_id;
}

void PrintMovesSequence(vector<int> input_sequence, vector<int> desired_sequence) {

    PrintParking(input_sequence);
    int right_positions = 0;

    map<int, int> positions_map;    //map for car numbers and its positions
    for(int i = 0; i < input_sequence.size(); i++) {
        positions_map[input_sequence[i]] = i;
        if(input_sequence[i] == desired_sequence[i] && input_sequence[i] != 0)
            right_positions++;
    }

    for(int i = 0; right_positions < input_sequence.size(); i++) {
        int free_space_id = positions_map[0];    //a free parking lot
        int current_id = free_space_id;

        if(input_sequence[current_id] != desired_sequence[current_id]) {
            //switch car with a free parking lot
            SwitchCarWithFreeLot(input_sequence, desired_sequence, positions_map, current_id, free_space_id);
            right_positions++;
            PrintParking(input_sequence);
        }
        else {
            while(input_sequence[current_id] == desired_sequence[current_id]) {
                current_id = (current_id + 1) % input_sequence.size();
            }

            //switch actual with free space
            int parked_car = input_sequence[current_id];
            positions_map[parked_car] = free_space_id;
            positions_map[0] = current_id;
            input_sequence[current_id] = 0;
            input_sequence[free_space_id] = parked_car;
            right_positions++;
            PrintParking(input_sequence);

            //switch car with a free parking lot
            SwitchCarWithFreeLot(input_sequence, desired_sequence, positions_map, current_id, positions_map[0]);
            right_positions++;

            PrintParking(input_sequence);

        }
    }
    return;
}


int main(){

    //no problems
    vector<int> input;
    input.push_back(1);
    input.push_back(2);
    input.push_back(0);
    input.push_back(3);

    vector<int> output;
    output.push_back(3);
    output.push_back(2);
    output.push_back(0);
    output.push_back(1);

    PrintMovesSequence(input, output);
    cout<<endl;

    //0 and three right in the row
    input.push_back(4);

    output.clear();
    output.push_back(2);
    output.push_back(1);
    output.push_back(0);
    output.push_back(3);
    output.push_back(4);

    PrintMovesSequence(input, output);
    cout<<endl;

    //three right on the left from 0
    input.clear();
    input.push_back(2);
    input.push_back(1);
    input.push_back(0);
    input.push_back(3);
    input.push_back(5);
    input.push_back(4);

    output.clear();
    output.push_back(2);
    output.push_back(1);
    output.push_back(0);
    output.push_back(4);
    output.push_back(3);
    output.push_back(5);

    PrintMovesSequence(input, output);
    cout<<endl;


    return 0;
}
