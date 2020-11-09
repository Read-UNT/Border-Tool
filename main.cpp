/*
===============================================================================================================

Name               : main.cpp
Authors            : Read L. Ballew Jr, Paris H. W. Estes, & Thien-An D. Vu
Lecture Section    : CSCE 2110.001
Date               : December 5th, 2018
Description        : The purpose of this program is to color a map where each country is a unique color 
                     compared to its neighbors.

===============================================================================================================
*/

#include "main.h"

using namespace std;

int main()
{
    string inputFileName; //Prompting user for file name
    cout << "Please enter the name of the file: ";
    getline(cin, inputFileName);

    //Opeining input file stream
    fstream fin;
    fin.open(inputFileName);
    //Error Checking
    if(fin.fail())
    {
        cout << "Failed to open file -> " << inputFileName << endl; 
        cout << "EXIT_FAILURE" << endl;
        exit(EXIT_FAILURE);
    }

    //Declaring variables
    string rawString; //raw input
    vector<string> refCountries, colors; //refined country list of names, list of colors
    //Create color list
    colors = colorCreation(colors);
    //Vectors used for color mapping
    vector<vector <int> > adjacencyMatrix;
    vector<vector <string> > adjacencyList;
    int count = 0;

    //Reading file
    while(!fin.eof())
    {
        if(count == 0)
        {
            getline(fin, rawString);
            refCountries = cleanString(rawString);
        }
        for(unsigned i = 0; i < refCountries.size(); i++)
        {
            vector<int> veryTempVec;
            adjacencyMatrix.push_back(veryTempVec);
        }
        for(unsigned i = 0; i < refCountries.size(); i++)
        {
            getline(fin, rawString);
            vector<int> tempNumVec = cleanNum(rawString);
            for(unsigned j = 0; j < tempNumVec.size(); j++)
            {
                adjacencyMatrix[i].push_back(tempNumVec[j]);
            }
        }

        count++;
    }
    fin.close();

    //Printing, creating degree, and creating adjancency list
    int largestCountryNameSize = 0;
    vector<int> degree;
    for(unsigned i = 0; i < refCountries.size(); i++)
    {
        vector<string> veryTempString;
        adjacencyList.push_back(veryTempString);
    }
    for(unsigned i = 0; i < refCountries.size(); i++)
    {
        int veryTempInt = 0;
        degree.push_back(veryTempInt);
    }
    for(unsigned i = 0; i < refCountries.size(); i++)
    { 
        if(refCountries[i].size() > largestCountryNameSize)
        {
            largestCountryNameSize = refCountries[i].size();
        }
    }

    //Colors map, returns degree of each country
    degree = colorMap(refCountries, adjacencyMatrix, degree, colors, adjacencyList);
    //Prints list of countries and their degree
    printing(refCountries, largestCountryNameSize, degree);
    //Averages the degrees and prints the final average
    average(degree);
    return 0;
}