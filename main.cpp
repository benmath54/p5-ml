#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cassert>
#include <set>
#include <algorithm>
#include <sstream>
#include "csvstream.hpp"
using namespace std;

//This Class will intake data and train on that given data.
//Then using the bag of words model it will be able to intake strings and
//predict the topic of the post
//INVARIANT: if num_posts = 0 all maps are empty
class Classifier{
    private:
    int num_posts;
    int unique_words;
    // labels for num of posts containing label C
    map<string,int> labels;
    // words for the number of posts containing each unique word
    map<string, int> words;
    // posts for the number for posts for label Label_Word.first 
    // containing word Label_Word.second
    map<string,int> posts;

    // EFFECTS: Return a set of unique whitespace delimited words.x
    set<string> uwords(const string &str) {
    istringstream source;
    
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
    }

    public:
    Classifier()
        : num_posts(0), unique_words(0),labels(), words(), posts(){ }

    bool empty() const{
        if(num_posts ==0){
            return true;
        }
        return false;
    }

    int num_unique_words() const{
        return unique_words;
    }

    int total_posts() const{
        return num_posts;
    }

    void train(string post,string, string tag){
        num_posts++;
        set<string> w = uwords(post);

        if(labels.find(tag) == labels.end()){
            labels[tag] = 1;
        }
        else{
            map<string,int>::iterator it1 = labels.find(tag);
            it1->second = it1->second+1;
        }

        set<string>::iterator word = w.begin();

        for(int i = 0; i < w.size(); i++){
            map<string,int>::iterator it1 = words.find(*word);
            if(it1 == words.end()){
               words[*word] = 1; 
               unique_words++;
            }
            else{
                it1->second = it1->second+1;
            }

            string Label_Word = tag + *word;
            map<string,int>::iterator it2 = posts.find(Label_Word);
            if(it2 == posts.end()){
                posts[Label_Word] = 1;
            }
            else{
                it2->second = it2->second +1;
            }
            word++;
        }
    }

    



};

int main(int argc, char *argv[]){
if(argc != 3 || argc != 4){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return -1;
}
if(argc == 4){
    if(argv[3] != "--debug"){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return -1;
    }
}

}
