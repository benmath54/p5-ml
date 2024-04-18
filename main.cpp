#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cassert>
#include <set>
#include <algorithm>
#include <sstream>
#include <math.h>   
#include <cmath>
#include "csvstream.hpp"
using namespace std;

//This Class will intake data and train on that given data.
//Then using the bag of words model it will be able to intake strings and
//predict the topic of the post
//INVARIANT: if num_posts = 0 all maps are empty
class Classifier{

    using Label_Word = pair<string,string>;
    private:
    int num_posts;
    int unique_words;
    // labels for num of posts containing label C
    map<string,int> labels;
    // words for the number of posts containing each unique word
    map<string, int> words;
    // posts for the number for posts for label Label_Word.first 
    // containing word Label_Word.second
    map<Label_Word,int> posts;

    // EFFECTS: Return a set of unique whitespace delimited words.x
    set<string> uwords(const string &str) {
    istringstream source(str);
    
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

    // Fuction for the training
    //MODIFIES: this
    //REQUIRES: A post class and a post
    //EFFECTS: Creates the maps using training data needed for log fuctions
    void train(string post, string tag){
        //Takes the post adds it num and splits it into unique words
        num_posts++;
        set<string> w = uwords(post);

        // if the label for the post is not in the map adds if
        // if it is then it increments it
        if(labels.find(tag) == labels.end()){
            labels[tag] = 1;
        }
        else{
            map<string,int>::iterator it1 = labels.find(tag);
            it1->second = it1->second+1;
        }

        //creates an iterator to move through the words in the post
        set<string>::iterator word = w.begin();

        //moves through the words
        for(int i = 0; i < w.size(); i++){

            //Checks the words map for the word acts on that
            map<string,int>::iterator it1 = words.find(*word);
            if(it1 == words.end()){
               words[*word] = 1; 
               unique_words++;
            }
            else{
                it1->second = it1->second+1;
            }

            // creates the pair of the post class and word and acts on that
            Label_Word lw;
            lw.first = tag;
            lw.second = *word;
            map<Label_Word,int>::iterator it2 = posts.find(lw);
            if(it2 == posts.end()){
                posts[lw] = 1;
            }
            else{
                it2->second = it2->second +1;
            }
            word++;
        }
    }

    //calculates the log prior
    double log_prior(string tag){
        map<string,int>::iterator it1 = labels.find(tag);
        double num_posts_tag = it1->second;
        double temp = num_posts;

        double x = num_posts_tag/temp;
        x = log(x);
        return x;
    }

    //takes in a tag and words and finds the the correct log formula
    double log_likelihood(string tag, string word){
        Label_Word lw;
        lw.first = tag;
        lw.second = word;
        map<Label_Word,int>::iterator it1 = posts.find(lw);
        map<string,int>::iterator it2 = words.find(word);
        map<string,int>::iterator it3 = labels.find(tag);

        if(it1 != posts.end()){
            double top = it1->second;
            double bottom = it3->second;
            return log(top/bottom);
        }
        else if(it2 != words.end()){
            double top = it2->second;
            double bottom = num_posts;
            return log(top/bottom);
        }
        else{
            double bottom = num_posts;
            return log(1/bottom);
        }
    }

    //simple print functions for the debug command line option
    void label_print(){
        map<string,int>::iterator it1 = labels.begin();
        while(it1 != labels.end()){
            cout <<"  ";
            cout << it1->first << ", ";
            cout << it1->second << " examples, ";
            cout<< "log-prior = " << log_prior(it1->first) << endl;  
            it1++;
        }
    }

    void class_param_print(){
        map<Label_Word,int>::iterator it1 = posts.begin();
        while(it1 != posts.end()){
            cout <<"  ";
            cout << it1->first.first << ":";
            cout << it1->first.second << ", ";
            cout << "count = " << it1->second;
            cout << ", log-likelihood = ";
            cout << log_likelihood(it1->first.first,it1->first.second);
            cout << endl;
            it1++;
        }
    }

    // Fuction that predicts the tag for a post
    //intakes a test post and finds the tag the has the greatest log value
    // returns a pair of the tag and log value
    pair<string,double> prediction(string post){
        set<string> word_set = uwords(post);
        map<string,int>::iterator label_it = labels.begin();
        string label_guess;
        double log_guess;

        // outer while loop moves through the label map 
        // the inner loop moves through the word set
        while(label_it != labels.end()){
            double log_temp = log_prior(label_it->first);
            set<string>::iterator word_it = word_set.begin();

            while(word_it != word_set.end()){
                log_temp = log_temp+log_likelihood(label_it->first,*word_it);
                word_it++;
            }

            if(label_it == labels.begin()){
                log_guess = log_temp;
                label_guess = label_it->first;
            }
            else if(log_temp >  log_guess){
                log_guess = log_temp;
                label_guess = label_it->first;
            }
            label_it++;
        }

        pair<string,double> guess;
        guess.first = label_guess;
        guess.second = log_guess;
        return guess;
    }

};

int main(int argc, char *argv[]){
cout.precision(3);// from spec

//Checks the command line interface is correct
if(argc != 3 && argc != 4){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return -1;
}

if(argc == 4){
    string arg4(argv[3]);
    if(arg4 != "--debug"){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return -1;
    }
}

//intakes training csv and creates needed map and classifier
csvstream traing_data(argv[1]);

map<string,string> row;

Classifier classifier;

if(argc == 4){
cout << "training data:" << endl;        
}


//while loop goes through training data row by row
//for loop takes each row along with its tag and trains classifier
while(traing_data >> row){
    string tag = row["tag"];
    string content = row["content"];
    classifier.train(content,tag);

    if(argc == 4){
        cout <<"  ";
        cout << "label = " << tag << ", ";
        cout <<"content = " << content << endl;
    }
}

// debug outputs
cout << "trained on " << classifier.total_posts() << " examples" << endl;
if(argc == 4){
cout << "vocabulary size = " << classifier.num_unique_words() << endl; 
}
cout << endl;

if(argc == 4){
    cout << "classes:" << endl;
    classifier.label_print();
    cout << "classifier parameters:" << endl;
    classifier.class_param_print();
    cout << endl;
}

cout << "test data:" << endl;
csvstream test_data(argv[2]);

//This loop is the one that intakes the test data and outputs the guesses
int correct_guesses = 0;
int test_posts = 0;
while(test_data >> row){
    test_posts++;
    string correct_tag = row["tag"];
    string content = row["content"];

    pair<string,double> prediction = classifier.prediction(content);
    cout <<"  ";
    cout << "correct = " << correct_tag << ", ";
    cout << "predicted = " << prediction.first << ", ";
    cout << "log-probability score = " << prediction.second << endl;
    cout << "  content = " << content << endl << endl;

    if(prediction.first == correct_tag){
        correct_guesses++;
    }
}
cout << "performance: " << correct_guesses<< " / " << test_posts;
cout << " posts predicted correctly" << endl;

}
