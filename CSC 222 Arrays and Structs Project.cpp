// CSC 222 Arrays and Structs Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Benjamin Hertzler
// Arrays and Structs Programming Projects
// Program 2: Marathon Runners with Structs

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

// Structs

// Struct to store the attributes of a marathon runner.
// Precondition: DAYS must be an initialized int.
// Postcondition:   name is the name of the runner.
//                      miles[] is an array of length DAYS to store the miles run each day.
//                      total is the sum of all values in miles[].
//                      average is the mean of all values in miles[].
//
struct runnerType
{
    string name = "NAME";
    double miles[DAYS] = { 0 };
    double total = 0;
    double average = 0;
};

// Functions

// Function to extract runner data from the file.
// Preconditions:   string fileName receives the name of the file to be opened.
//                          runnerType runners[] is an empty array of length max_size.
// Postconditions:  runners[] will be populated with runner data.
//                          returns the number of runner names in the file.
//
int getData(string fileName, runnerType runners[], int max_size);

// Function to calculate totals and averages for the runner data.
// Precondition:    runners is an array of runnerType structs of length runner_count.
// Postcondition:   for each object in runners[], the total and average values will be updated.
//
void analyzeData(runnerType runners[], int runner_count);

// Function to generate an output file.
// Precondition: fileName is the name of a file.
//                      runners[] is an array of runnerType structs of length runner_count
// Postcondition: Generates a file containing a table displaying the following columns:
//                      runnerName milesDay1 milesDay2 milesDay3 milesDay4 milesDay5 milesDay6 milesDay7 totalMiles averageMiles
//
void writeFile(string fileName, runnerType runners[], int runner_count);

// Function to calculate a summation of an array of doubles.
// Precondition: nums[] is an array of doubles of length count.
// Postcondition: returns the sum of all values in nums.
//
double sum(double nums[], int count);


int main()
{   
    // Variables
    runnerType runners[MAX_RUNNERS];
    int runner_count;

    // Algorithm
    runner_count = getData(IN_FILE_NAME, runners, MAX_RUNNERS);
    analyzeData(runners, runner_count);

    writeFile(OUT_FILE_NAME, runners, runner_count);
}

int getData(string fileName, runnerType runners[], int max_size)
{
    ifstream f(fileName);

    if (!f.is_open())
    {
        cerr << "Error: Failed to open file." << endl;
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (f >> runners[i].name)
    {
        for (int j = 0; j < DAYS; j++)
            f >> runners[i].miles[j];
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

void analyzeData(runnerType runners[], int runner_count)
{
    for (int i = 0; i < runner_count; i++)
    {
        runners[i].total = sum(runners[i].miles, DAYS);
        runners[i].average = runners[i].total / DAYS;
    }
}

double sum(double nums[], int count)
{
    double total = 0;
    for (int i = 0; i < count; i++)
        total += nums[i];
    return total;
}

void writeFile(string fileName, runnerType runners[], int runner_count)
{
    ofstream f(fileName);
    f << setw(12) << left << "Runner Name";
    for (int i = 0; i < DAYS; i++)
        f << right << setw(6) << "Day " << i + 1;
    f << setw(7) << "Total" << setw(9)<< "Average" << endl << fixed;
    for (int i = 0; i < runner_count; i++)
    {
        f << setw(12) << left << runners[i].name << right << setprecision(0);
        for (int j = 0; j < DAYS; j++)
            f << setw(7) << runners[i].miles[j];
        f << setw(7) << runners[i].total << setw(9) << setprecision(1) << runners[i].average << endl;
    }
}
