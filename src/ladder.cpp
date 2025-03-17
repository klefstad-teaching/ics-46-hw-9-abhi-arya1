#include "ladder.h" 
#include <iostream> 
#include <fstream>

using namespace std; 

void error(string word1, string word2, string msg) {
    cout << "ERROR - " << word1 <<  " " << word2 << " " << msg; 
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if(str1 == str2) {
        return true; 
    }

    if (abs((int) (str1.size() - str2.size())) > d) {
        return false; 
    }

    int min_size = min(str1.size(), str2.size());
    int diffs { 0 };
    for(int idx = 0; idx < min_size; ++idx) {
        if(str1[idx] != str2[idx]) {
            ++diffs;
            if(diffs > d) {
                return false; 
            }
        }
    }

    return true; 
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
    
    error(begin_word, end_word, "No word ladder exists between these words.");
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
    for (int idx = 0; idx < ladder.size(); idx++) {
        cout << ladder[idx] <<  " ";
    }
}