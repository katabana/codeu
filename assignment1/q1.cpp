bool permutation(string base, string test) {

    if(base.size() != test.size())
        return false; // not permutations for sure

    int letters[256]; //array for ascii chars
    for(int i = 0; i < 256; i++)
        letters[i] = 0;

    for(int i = 0; i < base.size(); i++) {
        letters[base[i]]++;
        letters[test[i]]--;
    }

    for(int i = 0; i < base.size(); i++) {
        if(letters[i] != 0)
            return false;
    }
    return true;
}
