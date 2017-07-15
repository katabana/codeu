#include<iostream>
#include<vector>
#include<set>
using namespace std;

void make_rules(vector<char> *connections[256], vector<string> dictionary, set<char> &letters, vector<int> &in_number) {

    //initialize connections
    for(int i = 0; i < 256; i++) {
        connections[i] = NULL;
        in_number[i] = -1;
    }

    if(dictionary.empty())
        return;

    if(dictionary.size() == 1) {
        char word_letter = dictionary.at(0)[0];
        int length = dictionary.at(0).size();
        int letter_id = 0;
        letters.insert(word_letter);

        //if word is made only of one character
        while((letter_id < length - 1) && word_letter == dictionary.at(0)[letter_id]) {
            letter_id++;
        }
        if(letter_id == length - 1) {
            connections[word_letter] = &(*new vector<char>);
            (*connections[(int) word_letter]).push_back(word_letter);
        }

        return;
    }

    //make connections
    for(int word_id = 0; word_id < dictionary.size()-1; word_id++) {
        string word1 = dictionary[word_id];
        string word2 = dictionary[word_id + 1];
        int char_id = 0;
        while(word1[char_id] == word2[char_id])
            char_id++;

        if(connections[word1[char_id]] == NULL) {
            letters.insert(word1[char_id]);
            in_number[word1[char_id]] = 0;
            connections[word1[char_id]] = &(*new vector<char>);
        }
        if(connections[word2[char_id]] == NULL) {
            letters.insert(word2[char_id]);
            in_number[word2[char_id]] = 0;
            connections[word2[char_id]] = &(*new vector<char>);
        }
        //add the directed edge
        (*connections[word1[char_id]]).push_back(word2[char_id]);
        letters.erase(word2[char_id]);
        in_number[word2[char_id]]++;

    }

    return;

}

vector<char> make_alphabet_from_rules(vector<char> *connections[256], set<char> &letters, vector<int> &in_number) {

    int current_id = 0;

    vector<char> alphabet;
    set<char>::iterator current_letter = letters.begin();

    //if dictionary was empty
    if(letters.empty()) {
        cout<<"empty"<<endl;
        return alphabet;
    }

    //while there are still letters to process
    while(!letters.empty()) {

        alphabet.push_back(*current_letter);

        //if dictionary had one word consisting of more than one char
        if(connections[*current_letter] == NULL){
            cout<<"cannot make rules"<<endl;
            return alphabet;
        }

        vector<char> *vector_for_letter = &(*(connections[*current_letter]));

        //look for all connections from letter
        for(int vertex = 0; vertex < (*vector_for_letter).size(); vertex++) {
            char vertex_letter = (*vector_for_letter)[vertex];
            in_number[vertex_letter]--;
            if(in_number[vertex_letter] == 0) {
                letters.insert(vertex_letter);
            }
        }
        //delete letter's connections
        vector<char> *row = &(*(connections[*current_letter]));
        letters.erase(*current_letter);
        (*row).erase((*row).begin(), (*row).end());
        current_letter = letters.begin();

    }

    //if there are still any connections
    for(int i = 0; i < 256; i++){
        if((&(*connections[i]) != NULL) && (*connections[i]).empty() != 1) {
            //if cycle or contradictory rules
            cout<<"cannot make rules"<<endl;
            alphabet.erase(alphabet.begin(), alphabet.end());
            return alphabet;
        }
    }

    //print out alphabet
    for(int i = 0; i < alphabet.size(); i++) {
        cout<<alphabet[i]<<" ";
    }
    cout<<endl;

    return alphabet;

}

vector<char> create_alphabet_from_dictionary(vector<string> dictionary) {

    set<char> letters;
    vector<char> *rules[256];
    vector<int> in_number(256);

    make_rules(rules, dictionary, letters, in_number);

    return make_alphabet_from_rules(rules, letters, in_number);
}

int main() {
    vector<string> dictionary;

    //empty dictionary
    create_alphabet_from_dictionary(dictionary);
    //should be empty

    //unequivocal rules
    dictionary.push_back("bart");
    dictionary.push_back("bas");
    dictionary.push_back("tab");
    dictionary.push_back("tar");
    dictionary.push_back("ab");
    dictionary.push_back("as");
    dictionary.push_back("at");

    create_alphabet_from_dictionary(dictionary);
    //should be b r s t a

    //contradictory rules
    dictionary.push_back("ar");
    create_alphabet_from_dictionary(dictionary);
    //should be wrong

    //only one word in dictionary - one char
    dictionary.clear();
    dictionary.push_back("a");
    create_alphabet_from_dictionary(dictionary);
    //should be a

    //only one word in dictionary - the same chars
    dictionary.clear();
    dictionary.push_back("aaa");
    create_alphabet_from_dictionary(dictionary);
    //should be a


    //only one word in dictionary - different chars
    dictionary.clear();
    dictionary.push_back("aka");
    create_alphabet_from_dictionary(dictionary);
    //should be wrong

    //equivocal rules
    dictionary.push_back("bka");
    create_alphabet_from_dictionary(dictionary);
    //prints out only those letters that can be organised
}
