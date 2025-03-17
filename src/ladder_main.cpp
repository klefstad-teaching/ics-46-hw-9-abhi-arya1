#include "ladder.h" 
#include <iostream> 
#include <fstream>

using namespace std; 


#define ladder_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    ladder_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    ladder_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    ladder_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    ladder_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    ladder_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    ladder_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}


int main() {
    verify_word_ladder();
    return 0;
}