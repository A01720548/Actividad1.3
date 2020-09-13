#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Register // This struct will help us manage the information gathered from the text file
{
    int date; //This int is the sum of our concatenation using the formattedLine Method
    string reg;
};

Register make_Register(int x, string y) { //This function allows us to create a new instance for every line
    Register newReg = {x, y};
    return newReg;
};

void BubbleSort(vector<Register> &vect) {
    /*
    Compares pairs of elements and switches them if the one on the right is larger
    It uses an auxiliary variable to perform said switch
    Complexity: O(n^2)
    */ 
    int aux;
    for (int i = 0; i < vect.size(); i++) {
        for (int j = i+1; j < vect.size(); j++) {
            if (vect[j].date < vect[i].date) {
                aux = vect[i].date;
                vect[i].date = vect[j].date;
                vect[j].date = aux;
            }
        }
    }
}

int BinarySearch(vector<Register> &vect, int x) {
    /*
    Needs an ordered vector to function properly
    Starts by dividing the vector in 2 and checking if the element is equal to the midpoint
    If it is smaller it only checks with the half to the left,
    if it is larger it only checks the half on the right,
    continues halving the vector until only one element is left.
    If it is not equal to that element, it means the variable is not in the vector
    Complexity: O(log2_n)
    */ 
    int mid, low, high, n, retval;
    retval = -1;
    low = 0;
    n = vect.size();
    high = n-1;

    while (low <= high) {
        mid = (low+high)/2;
        if (x == vect[mid].date) {
            retval = mid;
            break;
        } else if (x < vect[mid].date) {
            high = mid -1;
        } else {
            low = mid + 1;
        }
    }
    retval = mid;
    return retval;


}

string convertMonth(string month) { // This function changes the Text Based Months in the file into the corresponding number
	if (month == "Jun") { return "6"; }
	else if (month == "Jul") { return "7"; }
	else if (month == "Aug") { return "8"; }
	else if (month == "Sep") { return "9"; }
	else if (month == "Oct") { return "10"; }
}

int formattedLine(string singleLine) {  // This method returns an int from the concatenation of every part of the dates
    return stoi(convertMonth(singleLine.substr(0, 3)) + singleLine.substr(4, 2) + singleLine.substr(7, 2) + singleLine.substr(10, 2) + singleLine.substr(13, 2));
}



int main()
{
    ifstream file("bitacora.txt", ios::binary);
    vector<Register> contents;
    string singleLine;
    while (getline(file, singleLine))
        contents.push_back(make_Register(formattedLine(singleLine), singleLine.substr(16)));

    cout << contents.size() << " lines in memory" << endl;

    file.close();


    BubbleSort(contents);

    // INPUTS
    string mes, dia, hora, minuto, segundo;
    cout << "Fecha inicial" << endl;

    cout  << "Que mes desea (numero sin 0 adelante)" << endl;
    cin >> mes;

    cout  << "Que dia desea (numero con 0 adelante)" << endl;
    cin >> dia;

    cout  << "Que hora desea (numero con 0 adelante)" << endl;
    cin >> hora;

    cout  << "Que minuto desea (numero con 0 adelante)" << endl;
    cin >> minuto;

    cout  << "Que segundo desea (numero con 0 adelante)" << endl;
    cin >> segundo;

    string mes2, dia2, hora2, minuto2, segundo2;
    cout << "Fecha Final" << endl;
    
    cout  << "Que mes desea (numero sin 0 adelante)" << endl;
    cin >> mes2;

    cout  << "Que dia desea (numero con 0 adelante)" << endl;
    cin >> dia2;

    cout  << "Que hora desea (numero con 0 adelante)" << endl;
    cin >> hora2;

    cout  << "Que minuto desea (numero con 0 adelante)" << endl;
    cin >> minuto2;

    cout  << "Que segundo desea (numero con 0 adelante)" << endl;
    cin >> segundo2;

    int fechaInicio = stoi(mes+dia+hora+minuto+segundo);
    int fechaFinal = stoi(mes2+dia2+hora2+minuto2+segundo2);

    int posicion = BinarySearch(contents,fechaInicio);
    int posicionFinal = BinarySearch(contents,fechaFinal);


    ofstream sorted("result.txt", ios::binary);
        for(int i = posicion; i <= posicionFinal; i++){
            sorted << contents[i].reg << endl; // Here we output the information for all the events in between our max and min dates
        }

    sorted.close();

    return 0;
}