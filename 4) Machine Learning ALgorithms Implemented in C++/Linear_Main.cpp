#include "Predictive_Modelling.cpp"

int main() {

    // This class loads the titanic data and stores it in a matrix
    Predictive_Modelling titanic("C:\\Users\\Manny\\Box\\University\\Sem 5 (Spring 2023)\\CS 4375\\Assignments\\4) Regression in C++\\titanic_project.csv");

    // 2. Specify Test data range, The rest is stored in the train
    titanic.partitionData(800);

    // 3. Train data using logistic
    titanic.train();

    return 0;

}
