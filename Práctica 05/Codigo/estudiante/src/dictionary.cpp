/**
 * @file dictionary.cpp
 * @brief Implementación del TDA Dictionary.
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#include "dictionary.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ostream& operator<<(ostream& os, const Dictionary& dic){
    for (Dictionary::iterator it = dic.begin(); it != dic.end(); ++it){
        os << *it << endl;
    }
    return os;
}

istream& operator>>(istream& is, Dictionary& dic) {
    dic.clear();
    string wrd;
    while (is >> wrd)
        dic.insert(wrd);

    return is;
}

Dictionary::Dictionary() {}

Dictionary::Dictionary(const Dictionary &othr) {
    this->words = othr.words;
}

bool Dictionary::exists(const string &s) const {return (bool)words.count(s);}

bool Dictionary::insert(const string &s) {
    pair<set<string>::iterator, bool> ret = words.insert(s);
    return ret.second;
}

bool Dictionary::erase(const std::string &s) {
    return (bool) this->words.erase(s);
}

void Dictionary::clear() {this->words.clear();}

bool Dictionary::empty() const {return this->words.empty();}

unsigned int Dictionary::size() const {return this->words.size();}

vector<string> Dictionary::wordsOfLength(int length) const {
    vector<string> v_ret;
	for (Dictionary::iterator it = this->begin(); it != this->end(); ++it)
        if ((*it).length() == length) v_ret.push_back(*it);

    return v_ret;
}

int count_ocurrences(char c, const string& word, size_t pos) {
    int cont = 0;
    size_t s = word.find(c,pos);
    if (s != string::npos) {
        cont++;
        cont += count_ocurrences(c,word,s+1);
    }
    return cont;
}

int Dictionary::getOcurrences(char c) const {
    int cont = 0;
    for (Dictionary::iterator it = this->begin(); it != this->end(); ++it)
        cont += count_ocurrences(c,*it);

    return cont;
}

void Dictionary::anade(const Dictionary &dic) {
    for (Dictionary::iterator it = dic.begin(); it != dic.end(); ++it)
        this->insert(*it);

}


Dictionary::Dictionary(const string & file_name){
	LoadDictionary(file_name);
}


void Dictionary::LoadDictionary(const std::string &file_name) {
	ifstream is;
	is.open(file_name);
	if (!is.is_open()) {
		cerr << "Error opening the file " << file_name;
		exit(1);
	}
	is >> *this;
}
