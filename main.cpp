#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Register
{
    int date;
    string reg;
};
Register make_Register(int x, string y) {
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

    return retval;


}

void JoinHelper(vector<Register> &vect, int start, int mid, int end) {
    /*
    Compares halves of elements and switches them if the one on the right is larger
    It uses an auxiliary vector to perform said switch
    */ 
    int i,j,k;
    i = start;
    k = start;
    j = mid + 1;
    vector<Register> aux(end);

    while(i <=mid && j<=end) {
        if (vect[i].date <=vect[j].date) {
            aux[k].date = vect[i].date;
            k++;
            i++;
        } else {
            aux[k].date = vect[j].date;
            k++;
            j++;
        }
    }
    while (i <= mid) {
        aux[k].date = vect[i].date;
        k++;
        i++;
    }
    while (j <= end) {
        aux[k].date = vect[j].date;
        k++;
        j++;
    }
    for (int x = start; x < k; x++) {
        vect[x].date = aux[x].date;
    }
}

void MergeSort (vector<Register> &vect, int start, int end) {
    /*
    Starts by dividing into halves and calling itself along with the join helper function
    Finishes the recursion until no more halves can be sliced
    Complexity: O(nlogn)
    */ 
    if (start < end) {
        int mid = (start + end)/2;
        MergeSort(vect,start,mid);
        MergeSort(vect,mid+1, end);
        JoinHelper(vect,start,mid,end);
    }
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
        contents.push_back(make_Register(formattedLine(singleLine), singleLine.substr(16)));

    cout << contents.size() << " lines in memory" << endl;

    file.close();


    //MergeSort(contents,0,contents.size());
    BubbleSort(contents);

    string mes, dia, hora, minuto, segundo;
    cout  << "Que mes desea" << endl;
    cin >> mes;

    cout  << "Que dia desea" << endl;
    cin >> dia;

    cout  << "Que hora desea" << endl;
    cin >> hora;

    cout  << "Que minuto desea" << endl;
    cin >> minuto;

    cout  << "Que segundo desea" << endl;
    cin >> segundo;

    int fechaInicio = stoi(mes+dia+hora+minuto+segundo);

    int posicion = BinarySearch(contents,fechaInicio);

    cout << contents[posicion].date << "       " << contents[posicion].reg;


    

    // ofstream sorted("sorted.txt", ios::binary);
    //     for (vector<Register>::iterator it = contents.begin(); it != contents.end(); it++)
    //     {
    //         sorted << *it << endl;
    //     }

    //     sorted.close();

    return 0;
}