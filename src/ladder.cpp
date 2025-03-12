#include "ladder.h"
#include <algorithm>

using namespace std;

void error(string word1, string word2, string msg){
    cout << " ERROR: " + word1 + " " + word2 + " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if(str1 == str2) return false;
    if (abs((int)str1.size() - (int)str2.size()) > 1) 
        return false;
    
    // If same length, check for exactly one difference
    if (str1.size() == str2.size()) {
        int diff = 0;
        for (size_t i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                diff++;
                if (diff > 1) return false;
            }
        }
        return diff == 1;
    }
    
    // If lengths differ by 1, check for insertion/deletion
    const string& shorter = (str1.size() < str2.size()) ? str1 : str2;
    const string& longer = (str1.size() < str2.size()) ? str2 : str1;
    
    size_t i = 0, j = 0;
    bool found_diff = false;
    
    while (i < shorter.size() && j < longer.size()) {
        if (shorter[i] != longer[j]) {
            if (found_diff) return false;
            found_diff = true;
            j++; // Skip the character in longer string
        } else {
            i++;
            j++;
        }
    }
    
    return true;
}



bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if(begin_word == end_word) return {};
    queue<vector<string>> ladder_queue;
    vector<string> first_word;
    first_word.push_back(begin_word);
    ladder_queue.push(first_word);
    set<string> visited;
    visited.insert(begin_word);
    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string lastword = ladder[ladder.size()-1];
        for(auto word: word_list){
            if(is_adjacent(lastword, word) && visited.find(word) == visited.end()){
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if(word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}


void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    string word;
    while(in >> word)
        word_list.insert(word);
}


void print_word_ladder(const vector<string>& ladder){
    if(ladder.size() > 1){
        cout << "Word ladder found: ";
        for(auto word: ladder)
            cout << word << " ";
        cout << endl;
    }else{
        cout <<  "No word ladder found." << endl;
    }
    
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}