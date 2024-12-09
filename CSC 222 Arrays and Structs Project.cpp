// CSC 222 Arrays and Structs Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Benjamin Hertzler
// Arrays and Structs Programming Projects
// Program 1: Marathon Runners with Parallel Arrays

// Program Description: This program gathers daily distance data for a group of runners from a file and analyzes it.
// Required User Input: None.
// Program Output: A file (runnerData.txt) containing a chart with columns for the name of each runner, miles run each day, weekly total, and daily average.
// Supplied Constants: Input File name (runners.txt), Output File name (runnerData.txt).

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Macro Constants

#define IN_FILE_NAME "runners.txt"
#define OUT_FILE_NAME "runnerData.txt"
#define MAX_RUNNERS 99
#define DAYS 7

// Functions

// Function to extract runner data from the file.
// Preconditions:   string fileName receives the name of the file to be opened.
//                          int max_size is the maximum number of lines in the file.
// Postconditions:  names[] will be populated with the names of runners.
//                          data[][] will be populated with the number of miles run each day.
//
int getData(string fileName, string names[], double data[][DAYS], int max_size);

// Function to calculate totals and averages for the runner data.
// Precondition:    data[][] is a two dimensional array of length len and width DAYS containing numeric data.
// Postcondition:   for each row of data, analysis[][] will be populated with the row total in the first column and average in the second.
//
void analyzeData(double analysis[][2], double data[][DAYS], int len);

// Function to generate an output file.
// Precondition: fileName is the name of a file.
//                      names[] is an array of length runner_count containing names.
//                      distances[][] is a 2D array of length runner_count and width DAYS containing runner data.
//                      analysis[][2] is a 2D array of length runner_count and width 2 containing totals and averages.
// Postcondition: Generates a file containing a table displaying the following columns:
//                      runnerName milesDay1 milesDay2 milesDay3 milesDay4 milesDay5 milesDay6 milesDay7 totalMiles averageMiles
//
void writeFile(string fileName, string names[], double distances[][DAYS], double analysis[][2], int runner_count);

// Function to calculate a summation of an array of doubles.
// Precondition: nums[] is an array of doubles of length count.
// Postcondition: returns the sum of all values in nums.
//
double sum(double nums[], int count);


int main()
{   
    // Variables
    string runners[MAX_RUNNERS];
    double distances[MAX_RUNNERS][DAYS], results[MAX_RUNNERS][2];
    int runner_count;

    // Algorithm
    runner_count = getData(IN_FILE_NAME, runners, distances, MAX_RUNNERS);
    analyzeData(results, distances, runner_count);

    writeFile(OUT_FILE_NAME, runners, distances, results, runner_count);
}

int getData(string fileName, string names[], double data[][DAYS], int max_size)
{
    ifstream f(fileName);

    if (!f.is_open())
    {
        cerr << "Error: Failed to open file." << endl;
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (f >> names[i])
    {
        for (int j = 0; j < DAYS; j++)
            f >> data[i][j];
        i++;
        if (i == max_size)
        {
            cerr << "Error: Overflow." << endl;
            break;
        }
    }

    f.close();
    return i;
}

void analyzeData(double analysis[][2], double data[][DAYS], int len)
{
    double total, average;
    for (int i = 0; i < len; i++)
    {
        total = sum(data[i], DAYS);
        average = total / DAYS;
        analysis[i][0] = total;
        analysis[i][1] = average;
    }
}

double sum(double nums[], int count)
{
    double total = 0;
    for (int i = 0; i < count; i++)
        total += nums[i];
    return total;
}

void writeFile(string fileName, string names[], double distances[][DAYS], double analysis[][2], int runner_count)
{
    ofstream f(fileName);
    f << setw(12) << left << "Runner Name";
    for (int i = 0; i < DAYS; i++)
        f << right << setw(6) << "Day " << i + 1;
    f << setw(7) << "Total" << setw(9)<< "Average" << endl << fixed;
    for (int i = 0; i < runner_count; i++)
    {
        f << setw(12) << left << names[i] << right << setprecision(0);
        for (int j = 0; j < DAYS; j++)
            f << setw(7) << distances[i][j];
        f << setw(7) << analysis[i][0] << setw(9) << setprecision(1) << analysis[i][1] << endl;
    }
}
