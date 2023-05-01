#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;


extern "C" {

    // Global Functions
    void parseCSV(ifstream& inputFile);

    void sum(float table [][2], int cols, int rows);
    void mean(float table [][2], int cols, int rows);
    void median(float table [][2], int cols, int rows);
    void range(float table [][2], int cols, int rows);


}




int main() {

    // Variables
    float x

    // 1. Set up File stream to read from boston csv
    ifstream inputFile;
    inputFile.open("Boston.csv",ios::in);
    if (inputFile.is_open()) cout << "File Opened\n\n\n";

    // 1. Determine length of file
    int numLines = 0;       // Number of observations in the csv file
    string line = "";
    while (getline(inputFile, line))
        numLines++;


    // 2. Parse CSV

    // Clear getline
    inputFile.clear();
    inputFile.seekg(0);
    numLines-=1;

    // Read values into matrix
    float  rm_medv [numLines][2];
    float rmTable [numLines],medvTable [numLines];
    string rm = "", medv = "";

    bool firstLine = true;
    int count = 0;
    while (getline(inputFile, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }

        // Retrieve observation and store them in a matrix as well as individual tables
        stringstream inputString (line);
        getline(inputString, rm, ',');
        rm_medv[count][0] = stof (rm);
        rmTable[count] = stof(rm);


        getline(inputString, medv, ',');
        rm_medv[count][1] = stof (medv);
        medvTable[count] = stof(medv);

        count++;
    }


    // 3. Calculations
    sum(rm_medv,numLines,2);
    mean(rm_medv, numLines, 2);
    median(rm_medv, numLines, 2);
    range(rm_medv, numLines, 2);

}


void sum(float table [][2], int cols, int rows) {
    // Determine sum of rm
    float col1 = 0, col2 = 0;
    for (int i= 0; i <cols; i++) {
        col1+= table[i][0];
    }

    for (int i= 0; i <cols; i++) {
        col2+= table[i][1];
    }
    cout << "\nSUM" << "\n--------" <<endl;
    cout << "Sum (rm):   " << col1 <<endl;
    cout << "Sum (medv): " << col2 <<endl;
}

void mean(float table [][2], int cols, int rows) {
    // Determine mean of rm
    float col1 = 0, col2 = 0;
    for (int i= 0; i <cols; i++) {
        col1+= table[i][0];
    }

    float mean_rm =  (col1) / cols;

    for (int i= 0; i <cols; i++) {
        col2+= table[i][1];
    }

    float mean_medv =  (col2) / cols;

    cout << "\nMEAN" << "\n--------" <<endl;
    cout << "Mean (rm):   " << mean_rm <<endl;
    cout << "Mean (medv): " << mean_medv <<endl;
}
void median(float table [][2], int cols, int rows) {
    float rm [cols], medv [cols];
    for (int i = 0; i < cols; i++) {
        rm[i] = table [i][0];
        medv[i] = table[i][1];
    }
    sort(rm, rm + (sizeof (rm) / sizeof (rm[0])));
    sort(medv, medv + (sizeof (medv) / sizeof (medv[0])));


    cout << "\nMEDIAN" << "\n--------" <<endl;
    cout << "Median (rm):   " << (rm[252] + rm[253]) / 2.0 <<endl;
    cout << "Median (medv): " << (medv[252] + medv[253]) / 2.0 <<endl;
}
void range(float table [][2], int cols, int rows) {

    float rm[cols], medv[cols];
    for (int i = 0; i < cols; i++) {
        rm[i] = table[i][0];
        medv[i] = table[i][1];
    }
    sort(rm, rm + (sizeof(rm) / sizeof(rm[0])));
    sort(medv, medv + (sizeof(medv) / sizeof(medv[0])));


    cout << "\nRANGE" << "\n--------" << endl;
    cout << "Range (rm):   " << rm[0] << "   " << rm[505] << endl;
    cout << "Range (medv): " << medv[0] << "   " << medv[505] << endl;
}

void covariance (float table [][2], int cols, int rows) {

}

