#include "ladder.h" 
#include <iostream> 
#include <fstream>

using namespace std; 

void error(string word1, string word2, string msg) {
    cout << "ERROR - " << word1 <<  " " << word2 << " " << msg; 
}

bool same_size_comp(const string &str1, const string &str2, int d, size_t strsize) {
    int diffs { 0 };
    for(size_t idx = 0; idx < strsize; ++idx) {
        if(str1[idx] != str2[idx]) {
            ++diffs;
            if(diffs > d) {
                return false; 
            }
        }
    }
    return true; 
}

bool diff_size_comp(const string &str1, const string &str2, int d, size_t size1, size_t size2) {
    int diffs { 0 };
    string short_str; 
    string long_str; 

    if(size1 < size2) {
        short_str = str1; 
        long_str = str2; 
    } else {
        short_str = str2; 
        long_str = str1; 
    } 
    
    int idx1 { 0 }, idx2 { 0 };
    while(idx1 < short_str.size() && idx2 < long_str.size()) {
        if(short_str[idx1] != long_str[idx2]) {
            ++diffs; ++idx2; 
            if(diffs > d)
                return false; 
        } else {
            ++idx1; ++idx2; 
        }
    }

    diffs += long_str.size() - idx2; 
    if(diffs > d) return false; 
    return true; 
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    size_t size1 { str1.size() }, size2 { str2.size() };
    if(str1 == str2)
        return true; 
    
    if(size1 == 0 || size2 == 0)
        return !(max(size1, size2) > d);

    if (abs((int) (size1 - size2)) > d)
        return false; 

    if(size1 == size2)
        return same_size_comp(str1, str2, d, size1);

    return diff_size_comp(str1, str2, d, size1, size2);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);

    vector<string> empty; 
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
    
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (visited.find(word) != visited.end()) {
                continue;
            }
            
            if (is_adjacent(last_word, word)) {
                visited.insert(word);
                
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    error(begin_word, end_word, "no ladder found here");
    return empty;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name); 

    string word; 
    while(in >> word)
        word_list.insert(word);

    in.close(); 
}


void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t idx = 0; idx < ladder.size(); idx++) {
        cout << ladder[idx] << " ";
    }
    cout << endl;
}