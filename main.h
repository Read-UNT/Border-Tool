#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

/*
======================================================================================================================================
Function    : Printing
Parameters  : Vector of strings - list of countries, int - width of the longest country name, and vector of ints - all degrees
Return      : N/a
Description : Prints the list of countries and their corresponding degree.
======================================================================================================================================
*/
void printing(vector<string> countryList, int printWidth, vector<int> degrees)
{
    cout << "\nDegree\n";
    for(unsigned i = 0; i < countryList.size(); i++)
    {
        cout << setw(printWidth);
        cout << countryList[i] << ": " << degrees[i] << "\n";
    }

    return;
}

/*
======================================================================================================================================
Function    : Degree Average
Parameters  : Vector of all countries' degrees
Return      : N/a
Description : Prints out the average of the degree list of all countries including the ocean.
======================================================================================================================================
*/
void average(vector<int> degrees)
{
    int average = 0;
    cout << "\nAverage Degree: ";
    for(unsigned i = 0; i < degrees.size(); i++)
    {
        average += degrees[i];
    }
    average = round(average/degrees.size());
    cout << average << "\n";

    return;
}

/*
======================================================================================================================================
Function    : Color Creation
Parameters  : Empty vector of strings
Return      : Filled vector of strings
Description : This is where the colors used in the map are declared.
======================================================================================================================================
*/
vector<string> colorCreation(vector<string> colorList)
{
    colorList.push_back("Red");
    colorList.push_back("Green");
    colorList.push_back("Cyan");
    colorList.push_back("Magenta");
    colorList.push_back("Lightgray");

    return colorList;
}

/*
======================================================================================================================================
Function    : Clean String
Parameters  : String 
Return      : Vector of cleaned strings
Description : Takes input from one string, and only returns alphabetical characters in the form of a vector.
======================================================================================================================================
*/
vector<string> cleanString(string raw)
{
    vector<string> output;
    stringstream input;
    input.str(raw);
    string temp;

    while(getline(input, temp, ','))
    {
        output.push_back(temp);
    }

    return output;
}

/*
======================================================================================================================================
Function    : Clean Number
Parameters  : String 
Return      : Vector of cleaned integers
Description : Takes input from one string, and only returns numerical characters in the form of a vector.
======================================================================================================================================
*/
vector<int> cleanNum(string raw)
{
    vector<int> output;
    stringstream input;
    input.str(raw);
    string temp;

    while(getline(input, temp, ','))
    {
        output.push_back(stoi(temp));
    }

    return output;
}

/*
======================================================================================================================================
Function    : Color Map
Parameters  : Vector of a vector of strings 
Return      : Full color map vector of vector of strings
Description : Assigns a color to each country in the list, so that they do not touch another country with the same color.
======================================================================================================================================
*/

vector<int> colorMap(vector<string> countryList, vector<vector <int> > AM, vector<int> degrees, vector<string> CL, vector<vector<string> > AL)
{
    //AM = adjacency matrix
    //CL = color list
    //AL = adjacency list
    //Creation and print of list
    int printWidth = 0;
    cout << "\nAdjacency List\n";
    for(unsigned i = 0; i < countryList.size(); i++)
    {
        for(unsigned j = 0; j < AM[i].size(); j++)
        {
            if(AM[i][j] == 1)
            {
                string temporarycountryName;
                temporarycountryName = countryList[j];
                temporarycountryName += ":";
                AL[i].push_back(temporarycountryName);
                degrees[i]++;
            }
        }
    }

    //Assigning the first and forced color for Ocean
    for(unsigned i = 0; i < countryList.size(); i++)
    {
        if(countryList[i] == "Ocean")
        {
            countryList[i] += ":Blue";
        }
        for(unsigned j = 0; j < AL.size(); j++)
        {
            for(unsigned k = 0; k < AL[j].size(); k++)
            {
                if(AL[j][k] == "Ocean:")
                {
                    AL[j][k] += "Blue";
                }
            }
        }
    }

    int colorMatch = 0;
    //For all countries
    for(unsigned i = 0; i < countryList.size(); i++)
    {
        if(countryList[i] != "Ocean:Blue")
        {
            //Checking all colors
            for(unsigned j = 0; j < CL.size(); j++)
            {
                colorMatch = 0;
                //Checking colors of all adjacent countries
                for(unsigned k = 0; k < AL[i].size(); k++)
                {
                    if((AL[i][k].find(CL[j]) != string::npos))
                    {
                        colorMatch++;
                    }
                }

                //After checking colors of all adjacent countries
                if(colorMatch == 0)
                {
                    countryList[i] += ":";
                    for(unsigned k = 0; k < AL.size(); k++)
                    {
                        for(unsigned l = 0; l < AL[k].size(); l++)
                        {
                            if(AL[k][l] == countryList[i])
                            {
                                AL[k][l] += CL[j];
                            }
                        }
                    }
                    countryList[i] += CL[j];
                    break;
                }

                if(colorMatch > 0 && j == CL.size() - 1)
                {
                    cout << "\nCountries touch too many times, not enough colors.\n";
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    //Final printing
    for(unsigned i = 0; i < countryList.size(); i++)
    { 
        if(countryList[i].size() > printWidth)
        {
            printWidth = countryList[i].size();
        }
    }
    for(unsigned i = 0; i < AL.size(); i++)
    {
        //Color picking
        if(countryList[i].find("Red") != string::npos)
        {
            cout << "\033[1;31m" << setw(printWidth) << countryList[i];
        }
        else if(countryList[i].find("Green") != string::npos)
        {
            cout << "\033[1;32m" << setw(printWidth) << countryList[i];
        }
        else if(countryList[i].find("Cyan") != string::npos)
        {
            cout << "\033[1;36m" << setw(printWidth) << countryList[i];
        }
        else if(countryList[i].find("Magenta") != string::npos)
        {
            cout << "\033[1;35m" << setw(printWidth) << countryList[i];
        }
        else if(countryList[i].find("Lightgray") != string::npos)
        {
            cout << "\033[1;37m" << setw(printWidth) << countryList[i];
        }
        else if(countryList[i].find("Blue") != string::npos)
        {
            cout << "\033[1;34m" << setw(printWidth) << countryList[i];
        }
        cout << "\033[0m - ";
        for(unsigned j = 0; j < AL[i].size(); j++)
        {
            //Color picking
            if(AL[i][j].find("Red") != string::npos)
            {
                cout << "\033[1;31m" << AL[i][j] << " ";
            }
            else if(AL[i][j].find("Green") != string::npos)
            {
                cout << "\033[1;32m" << AL[i][j] << " ";
            }
            else if(AL[i][j].find("Cyan") != string::npos)
            {
                cout << "\033[1;36m" << AL[i][j] << " ";
            }
            else if(AL[i][j].find("Magenta") != string::npos)
            {
                cout << "\033[1;35m" << AL[i][j] << " ";
            }
            else if(AL[i][j].find("Lightgray") != string::npos)
            {
                cout << "\033[1;37m" << AL[i][j] << " ";
            }
            else if(AL[i][j].find("Blue") != string::npos)
            {
                cout << "\033[1;34m" << AL[i][j] << " ";
            }
            cout << "\033[0m";
        }
        cout << "\n";
    }

    return degrees;
}