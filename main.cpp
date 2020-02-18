#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>

using namespace std;

int dirLayer;
int dirCount;
bool fileCreate;

template <typename T>
std::string to_string ( T Number )
{
     std::ostringstream ss;
     ss << Number;
     return ss.str();
}

int strToInt(string text) {
    int charCode;
    int number = 0;
    
    for (int i = 0; i < text.length(); i++) {
        charCode = (int)text[i];
        
        if (charCode < 48 || charCode > 57) {
            throw 20;
        }
        
        number *= 10;
        number += charCode - 48;
    }
    
    return number;
}

int inputNumber(string additionalText = "") {
    string input;
    int number;
    
    do {
        cout << additionalText << endl;
        cout << "Please insert a number greater than 0: ";
        getline(cin, input);
        
        if (input.length() == 0) {
            cout << "Please insert a number!" << endl << endl << endl;
            
            continue;
        }    
        
        try {
            number = strToInt(input);
        } catch (int e) {
            continue;
        }        
        
        if (number > 0) {
            return number;
        }
    } while (true);
}

void createFile(string path)
{
    string filePath = path + "/README.txt";
    ofstream file (filePath.c_str());
    file << path << endl;
    file.close();
}

int createDirs(string path, int currLevel)
{
    for (int i = 0; i < dirCount; i++) {
        string currPath = path + "/" + to_string(i);
        
        if (mkdir(currPath.c_str()) != 0)
        {
            cout << "error creating " << currPath << endl;
        }
        
        if (currLevel < dirLayer - 1) {
            cout << "Creating dirs for " << currPath << "..." << endl;
            createDirs(currPath, currLevel + 1);
        } else if (fileCreate == true) {
            createFile(currPath);
        }    
    }
}     

int getDirSum()
{
    int sum = 0;
    
    for (int i = dirLayer; i > 0; i--) {
        sum += pow((double)dirCount, (double)i);
    }
    
    return sum;    
}    

int main(int argc, char *argv[])
{
    string consent = "n";
    string input = "";
    
    dirCount = inputNumber("dir count");
    cout << endl;
    dirLayer = inputNumber("dir layer");
    cout << endl;
    cout << "Hint: Creating files will be significantly less faster." << endl;
    cout << "Creating files? (y/n) ";
    cin >> input;
    
    if (input == "y") {
        fileCreate = true;
    } else {
        fileCreate = false;
    }        
    
    cout << endl << endl;
    cout << "Are you sure you want to create the following?" << endl;
    cout << "dir count: " << dirCount << endl;
    cout << "dir layer: " << dirLayer << endl;
    cout << "sum: " << getDirSum() << " directories" << endl;
    cout << "file create: " << fileCreate << endl << endl;
    
    cout << "Please insert your consent(y/n): ";
    cin >> consent;
    
    if (consent == "y") {
        createDirs("./test", 0);
    }    
  
    system("PAUSE");	
    return 0;
}
