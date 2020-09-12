#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Register
{
    int date;
    string reg;

    Register(int date,string reg) {
        this->date = date;
        this->reg = reg;
    }
};

Register make_Register(int x, string y) {
    Register newReg = {x, y};
    return newReg;
}

void sort(vector<string> &vect)
{
}

string convertMonth(string month) { 
	if (month == "Jun") { return "6"; }
	else if (month == "Jul") { return "7"; }
	else if (month == "Aug") { return "8"; }
	else if (month == "Sep") { return "9"; }
	else if (month == "Oct") { return "10"; }
}

int formattedLine(string singleLine) {
    return stoi(convertMonth(singleLine.substr(0, 3)) + singleLine.substr(4, 2) + singleLine.substr(7, 2) + singleLine.substr(10, 2) + singleLine.substr(13, 2));
}



int main()
{
    ifstream file("bitacora.txt", ios::binary);
    vector<Register> contents;
    string singleLine;
    while (getline(file, singleLine))
    {
        contents.push_back(make_Register(formattedLine(singleLine), singleLine.substr(16)));    }

    cout << contents.size() << " lines in memory";

    file.close();

    cout << contents[0].date << "****" << contents[0].reg << endl;

    //ReplaceMonths(contents);
    //sort(contents);

            
    /*        
    ofstream sorted("sorted.txt", ios::binary);
        for (vector<string>::iterator it = contents.begin(); it != contents.end(); it++)
        {
            sorted << *it << endl;
        }

        sorted.close();
*/
        return 0;
}