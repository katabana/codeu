bool permutation(string base, string test) {

    if(base.size() != test.size())
        return false; // not permutations for sure

    vector<int> letters(256, 0); //array for ascii chars

    for(int i = 0; i < base.size(); i++) {
        letters[tolower(base[i])]++;
        letters[tolower(test[i])]--;
    }

    for(int i = 0; i < base.size(); i++) {
        if(letters[i] != 0)
            return false;
    }
    return true;
}
