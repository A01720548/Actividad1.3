#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void ReplaceMonths (vector<string> &vect) {

}

void sort(vector<string> &vect) {

}

int main() {
    ifstream file("bitacora.txt", ios::binary);
    vector<string> contents;
    string singleLine;
    while (getline(file, singleLine))
        contents.push_back(singleLine);

    cout << contents.size() << " lines in memory";

    file.close();

    //ReplaceMonths(contents);
    //sort(contents);


    ofstream sorted("sorted.txt", ios::binary);
    for (vector<string>::iterator it = contents.begin(); it !=contents.end(); it++){
        sorted << *it << endl;
    }

    sorted.close();
    
    return 0;
}