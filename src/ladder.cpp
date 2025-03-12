#include "ladder.h"
#include <algorithm>

using namespace std;

void error(string word1, string word2, string msg){
    cout << " ERROR: " + word1 + " " + word2 + " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int m = str1.size();
    int n = str2.size();
    
    // Create a 2D DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Initialize base cases
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i; // Cost of deleting characters from str1
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j; // Cost of inserting characters into str1
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No cost if characters are the same
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j],   // Deletion
                                    dp[i][j - 1],   // Insertion
                                    dp[i - 1][j - 1]}); // Substitution
            }
        }
    }

    return dp[m][n] <= d;
}



bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
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
    return {"No word ladder found."};
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