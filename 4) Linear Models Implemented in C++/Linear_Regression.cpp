#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;
class Predictive_Modelling {

// Attributes
private:
    fstream FILE_STREAM;                    // File Stream to open csv file
    vector<string> COL_NAMES;               // Data structure to store column names
    float **DATA_FRAME;                     // 2D matrix to store imported data frame
    float **TRAIN, **TEST;                  // Arrays for Train and Test Data
    vector<float> X;                        // Array to store the Independent Variables
    vector<float> Y;                        // Array to store Dependent Variables
    int NUM_ROWS, NUM_COLS;                 // Dimensions for Data Frame

    // Regression Variables
    vector<double> error;                     // Array to store err
    double err;
    double b0 = 0;
    double b1 = 0;
    double alpha = 0.01;
    double e = 2.71828;

public:
    // Constructor
    Predictive_Modelling(string fileLocation) {
        // 1. Read Excel File
        read(fileLocation);

        // 2. Determine the number of rows and columns in file and initialize
        setDimensions();

        // 3. Store data in table
        storeInTable();
    }

    // Methods
    void read(string filename) {
        FILE_STREAM.open(filename, ios::in);
    }

    void setDimensions() {
        string temp;

        NUM_ROWS = 0;
        NUM_COLS = 1;
        // determine Num Cols
        getline(FILE_STREAM, temp);
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == ',')
                NUM_COLS++;
        }

        while (getline(FILE_STREAM, temp)) {
            NUM_ROWS++;
        }
        FILE_STREAM.clear();
        FILE_STREAM.seekg(0);

        // Initializing table, test, and train data
        this->DATA_FRAME = new float *[NUM_ROWS];
        this->TRAIN = new float *[800];
        this->TEST = new float *[NUM_ROWS-800];
        for (int i = 0; i < NUM_ROWS; i++) {
            DATA_FRAME[i] = new float[NUM_COLS];
            if (i <  (NUM_ROWS-800))
                TEST[i] = new float[NUM_COLS];
            if (i < 800)
                TRAIN[i] = new float[NUM_COLS];
        }
    }

    void storeInTable() {
        // 1. Storing Table Headers
        string csvColNames;                         // Variable to store the first line (headings)
        getline(FILE_STREAM, csvColNames);

        // Remove unwanted data from
        csvColNames.erase(remove(csvColNames.begin(), csvColNames.end(), '"'), csvColNames.end());
        csvColNames.erase(remove(csvColNames.begin(), csvColNames.end(), '\\'), csvColNames.end());

        // Loop to remove col names
        string tempString = "";
        for (int i = 0; i < csvColNames.size(); i++) {
            char currChar = csvColNames[i];

            if (currChar != ',')
                tempString.push_back(currChar);

            else {
                if (tempString == "") tempString = "ID";
                COL_NAMES.push_back(tempString);
                tempString = "";
            }
        }

        // 2. Storing Table Data
        string currLine;
        string currValue;
        int row = 0, col = 0;

        for (int i = 0; i < NUM_ROWS; i++) {
            // Get line
            getline(FILE_STREAM, currLine);

            // Sanitize line (Remove extraneous data)
            currLine.erase(remove(currLine.begin(), currLine.end(), '"'), currLine.end());
            currLine.erase(remove(currLine.begin(), currLine.end(), '\\'), currLine.end());

            // Parse line to get values.
            for (int i = 0; i < currLine.size(); i++) {
                if (currLine[i] != ',')
                    currValue.push_back(currLine[i]);

                else {
                    DATA_FRAME[row][col++] = stof(currValue);
                    currValue = "";
                }
            }
            DATA_FRAME[row][col++] = stof(currValue);
            currLine = "";
            currValue = "";
            row++;
            col = 0;
        }
    }

    static bool custom_sort(double a, double b) /* this custom sort function is defined to
                                     sort on basis of min absolute value or error*/
    {
        double a1 = abs(a - 0);
        double b1 = abs(b - 0);
        return a1 < b1;
    }

    void partitionData(int numTestRows) {
        // initialize and Store training data
        for (int i = 0; i < numTestRows; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                TRAIN[i][j] = DATA_FRAME[i][j];
            }
        }

        // initialize and Store test data
        for (int i = 0; i < NUM_ROWS-numTestRows; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                TEST[i][j] = DATA_FRAME[numTestRows + i][j];
            }
        }
    }


    void train() {
        // Data declaration
        // Formula Y = b0 + b1 * x1...
        // x1 = row from training data (in this case, it's sex)
        // alpha == learning rate

        // 1. Set Dependent and Independent  Columns
        for (int i = 0; i < 800; i++) {
            X.push_back(TRAIN[i][3]);
            Y.push_back(TRAIN[i][2]);
        }

        for (int i = 0; i < 800 * 4; i++) {
            int idx = i % 800;
            double p = -(b0 + b1 * X[idx]);
            double pred = 1 / (1 + pow(e, p));
            err = Y[idx] - pred;
            b0 = b0 - alpha * err * pred * (1 - pred) * 1.0;
            b1 = b1 + alpha * err * pred * (1 - pred) * X[idx];
            cout<<"B0="<<b0<<" "<<"B1="<<b1<<" "<<" error="<<err<<endl;// printing values after every step
            error.push_back(err);
        }

        sort(error.begin(), error.end(), custom_sort);//custom sort based on absolute error difference
        cout << "Final Values are: \n" << "B0 = " << b0 << " " << "\nB1 = " << b1 << " " << " \nerror = " << error[0]
             << endl;

        double test1;
        cout << "\nEnter a value to  make prediction on (0 for male, 1 for female):\n>>";
        cin >> test1;
        double pred = b0 + b1 * test1; //make prediction
        cout << "The value predicted by the model= " << pred << endl;
    }
};