#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "csvstream.hpp"

using namespace std;

struct TraningPost {
    string label;
    string content;
};

vector<TraningPost> trainingPosts;
map<string, int> class_counts;
map<string, map<string, int>> word_counts;
set<string> vocabulary;
size_t example_count;

set<string> unique_words(const string& str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

void load_training_data(const string& file_name, bool verbose) {
    csvstream csvTrain(file_name);
    map<string, string> row;
    if (verbose) cout << "training data:" << endl;

    while (csvTrain >> row) {
        string tag = row["tag"];
        string content = row["content"];
        if (verbose) {
            cout << "  label = " << tag << ", content = " << content << endl;
        }
        trainingPosts.push_back({ tag, content });
        class_counts[tag]++;

        istringstream iss(content);
        string word;
        set<string> seen;
        while (iss >> word) {
            if (seen.insert(word).second) {
                vocabulary.insert(word);
                word_counts[tag][word]++;
            }
        }
    }
    example_count = trainingPosts.size();
}

void print_training_summary() {
    cout << "vocabulary size = " << vocabulary.size() << endl << endl;

    cout << "classes:" << endl;
    vector<string> classes;
    for (auto& p : class_counts) {
        classes.push_back(p.first);
    }
    sort(classes.begin(), classes.end());

    for (auto& c : classes) {
        double log_prior = log(double(class_counts[c]) / example_count);
        cout << "  " << c << ", " << class_counts[c]
            << " examples, log-prior = " << log_prior << endl;
    }

    cout << "classifier parameters:" << endl;
    for (auto& c : classes) {
        vector<string> words;
        for (auto& p : word_counts[c]) {
            words.push_back(p.first);
        }
        sort(words.begin(), words.end());

        for (auto& w : words) {
            int count = word_counts[c][w];
            double prob = double(count) / class_counts[c];
            double log_likelihood = log(prob);
            cout << "  " << c << ":" << w << ", count = " << count
                << ", log-likelihood = " << log_likelihood << endl;
        }
    }
    cout << endl;
}

double compute_score(const set<string>& test_words, const string& cls) {
    double score = log(max(double(class_counts[cls]) / example_count, 1e-10));

    for (auto& w : test_words) {
        if (word_counts[cls].find(w) != word_counts[cls].end()) {
            score += log(max(double(word_counts[cls][w]) / class_counts[cls], 1e-10));
        }
        else if (vocabulary.find(w) != vocabulary.end()) {
            int word_occurrences_in_training = 0;
            for (auto& post : word_counts) {
                if (post.second.find(w) != post.second.end()) {
                    word_occurrences_in_training += post.second[w];
                }
            }
            score += log(
                max(double(word_occurrences_in_training) / example_count, 1e-10));
        }
        else {
            score += log(max(1.0 / example_count, 1e-10));
        }
    }

    return score;
}

void classify_test_data(const string& test_filename) {
    int correct_predictions = 0;
    int total_tests = 0;
    cout << "test data:" << endl;
    csvstream csvTest(test_filename);
    map<string, string> row;

    while (csvTest >> row) {
        string actual_label = row["tag"];
        string content = row["content"];

        istringstream iss(content);
        set<string> test_words;
        string word;
        while (iss >> word) {
            test_words.insert(word);
        }

        string best_label;
        double best_score = -INFINITY;

        for (auto& p : class_counts) {
            string cls = p.first;
            double score = compute_score(test_words, cls);

            if (score > best_score) {
                best_score = score;
                best_label = cls;
            }
        }

        total_tests++;
        if (best_label == actual_label) {
            correct_predictions++;
        }

        cout << "  correct = " << actual_label
            << ", predicted = " << best_label
            << ", log-probability score = " << best_score << endl;
        cout << "  content = " << content << endl << endl;
    }

    cout << "performance: " << correct_predictions
        << " / " << total_tests << " posts predicted correctly" << endl;
}


int main(int argc, char* argv[]) {
    cout.precision(3);
    if (argc != 2 && argc != 3) {
        cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
        return 1;
    }

    load_training_data(argv[1], argc == 2);
    cout << "trained on " << example_count << " examples" << endl;

    if (argc == 2) {
        print_training_summary();
    }
    else if (argc == 3) {
        classify_test_data(argv[2]);
    }

    return 0;
}
