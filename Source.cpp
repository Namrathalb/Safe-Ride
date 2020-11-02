#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <istream>
#include <iterator>
#include <vector>
#include <map> 
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <functional>

using namespace std;
int ci = 0;
/*----------------LOGFILE - START------------------------------*/
inline string getCurrentDateTime() //REURNS THE CURRENT DATE AND TIME TO LOG FILE NAME
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);
    std::string str(buffer);
    return str;
}
string s = "log_" + getCurrentDateTime() + ".txt"; //Log File is created
ofstream file;
template <typename T>
void logfile(int y, string x, T const& h) {
    file << ci << "\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t" << x << "\t\t" << h << "\n"; ci++;
}
/*----------------LOGFILE - END--------------------------------*/

class htmltoexcel {
public:

    int x = 0;
    ofstream check;
    string input, line;
    fstream myfile;
    vector<vector<string>> myvector;
    vector<string> passed;
    vector<string> failed;
    vector<string> data;
    htmltoexcel(string fn);
private:
    string Parsed(char* string);
    void intial(string fileName);
    void Search(string line);
    string rspace(string line);
    void Passed();
    void Failed();
    void Others();
};

/*--------------CONSTRUCTOR - START----------------------------*/
htmltoexcel::htmltoexcel(string fn)
{
    string filename = fn;
    logfile(__LINE__, "constr()", "Calling intial()");
    intial(fn);
    logfile(__LINE__, "constr()", "Calling Passed()");
    Passed();
    logfile(__LINE__, "constr()", "Calling Failed()");
    Failed();
    logfile(__LINE__, "constr()", "Calling Others()");
    Others();
}
/*--------------CONSTRUCTOR- END-------------------------------*/

/*--------------INTIAL - START---------------------------------*/
void htmltoexcel::intial(string fileName)
{
    myfile.open(fileName.c_str(), ios::in | ios::app);
    logfile(__LINE__, "intial()", "Opening Results.html.");
    if (!myfile)
    {
        cout << "file cannot open!";
        logfile(__LINE__, "intial()", "File Cannot open");
    }
    logfile(__LINE__, "intial()", "Reading Results.html");
    while (line != "</html>") {
        line = rspace(line);
        logfile(__LINE__, "intial()", "Calling Check()");
        Search(line);
        logfile(__LINE__, "intial()", "Read Next line");
        getline(myfile, line);
        if (data.size() == 6) {
            myvector.push_back(data);
            data.clear();
        }
    }
}
/*--------------INTIAL - END-----------------------------------*/

/*--------------REMOVE SPACES - START--------------------------*/
string htmltoexcel::rspace(string line)
{
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    return line;
}
/*--------------REMOVE SPACES - END----------------------------*/

/*--------------CHECK TAG - START------------------------------*/
void htmltoexcel::Search(string line)
{
    char* char_arr;
    int c = 0;
    if ((line.find("<tr>") > line.length()) && (line.find("</tr>") > line.length()) && (line.find("<td>") < line.length()))
    {
        logfile(__LINE__, "Search()", "Calling Parse()");
        char_arr = &line[0];
        data.push_back(Parsed(char_arr));
    }
    logfile(__LINE__, "Search()", "Line Parsed.");
}
/*--------------CHECK TAG - END--------------------------------*/

/*--------------PARSE - START----------------------------------*/
string htmltoexcel::Parsed(char* string)
{
    int index = 0, in = 0;
    logfile(__LINE__, "Parsed()", "Removing tags, Extracting Comment");
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '<') {
            in = 1;
            continue;
        }
        else if (string[i] == '>') {
            in = 0;
            continue;
        }
        if (in == 0) {
            string[index] = string[i];
            index++;
        }
    }
    string[index] = '\0';
    return string;
}
/*--------------PARSE - END------------------------------------*/

/*--------------PASSED.csv START-------------------------------*/
void htmltoexcel::Passed()
{
    ofstream passed_file;
    passed_file.open("passed.csv", ios::out);
    logfile(__LINE__, "Passed()", "Creating Passed.csv");
    for (int j = 0; j < myvector[0].size(); j++) {
        passed_file << myvector[0][j] << ",";
    }
    passed_file << "\n";
    //-------------------------------SORT()--------------------------------------------------
    logfile(__LINE__, "Passed()", "Sorting by Date(desc)");
    map<string, vector<string>, greater<string>> mymap;
    string key;
    vector<string> m; // Inserting the elements one by one 
    for (int i = 1; i < myvector.size(); i++) {
        key = myvector[i][0];
        for (int j = 0; j < myvector[i].size(); j++) {
            m = myvector[i];
        }
        mymap.insert(make_pair(key, m));
    }
    //-------------------------------Write into Respective file()----------------------------
    logfile(__LINE__, "Passed()", "Checking PASSED Status");
    map<string, vector<string>> ::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++) {
        vector<string> v1 = it->second;
        if (v1[1] == "PASSED") {
            for (int k = 0; k < v1.size(); k++) {
                passed_file << v1[k] << ",";
            }
            passed_file << endl;
        }
    }
    logfile(__LINE__, "Passed()", "Data Entry Complete");
    cout << "--------------" << endl;
    cout << "\n OUTPUT : passed.csv\n";
    passed_file.close();
    logfile(__LINE__, "Passed()", "Closing Passed.csv");
}
/*--------------PASSED.csv END---------------------------------*/

/*--------------FAILED.csv START-------------------------------*/
void htmltoexcel::Failed()
{
    ofstream failed_file;
    failed_file.open("failed.csv", ios::out);
    logfile(__LINE__, "Failed()", "Creating failed.csv");
    for (int j = 0; j < myvector[0].size(); j++) {
        failed_file << myvector[0][j] << ",";
    }
    failed_file << "\n";
    //-------------------------------SORT()-------------------------------------------------
    logfile(__LINE__, "Failed()", "Sorting by Date(desc)");
    map<string, vector<string>, greater<string>> mymap;
    string key;
    vector<string> m; // Inserting the elements one by one 
    for (int i = 1; i < myvector.size(); i++) {
        key = myvector[i][0];
        for (int j = 0; j < myvector[i].size(); j++) {
            m = myvector[i];
        }
        mymap.insert(make_pair(key, m));
    }
    //-------------------------------Write into Respective file()--------------------------
    logfile(__LINE__, "Failed()", "Checking FAILED Status");
    map<string, vector<string>> ::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++) {
        vector<string> v1 = it->second;
        if (v1[1] == "FAILED") {
            for (int k = 0; k < v1.size(); k++) {
                failed_file << v1[k] << ",";
            }
            failed_file << endl;
        }
    }
    logfile(__LINE__, "Failed()", "Data Entry Complete");
    cout << "--------------" << endl;
    cout << "\n OUTPUT : failed.csv\n";
    failed_file.close();
    logfile(__LINE__, "Failed()", "Closing failed.csv");
}
/*--------------FAILED.csv END---------------------------------*/

/*--------------OTHERS.csv START-------------------------------*/
void htmltoexcel::Others()
{
    ofstream others_file;
    others_file.open("Others.csv", ios::out);
    logfile(__LINE__, "Others()", "Creating others.csv");
    for (int j = 0; j < myvector[0].size(); j++) {
        others_file << myvector[0][j] << ",";
    }
    //-------------------------------SORT()-----------------------------------------------
    logfile(__LINE__, "Others()", "Sorting by Date(desc)");
    map<string, vector<string>, greater<string>> mymap;
    string key;
    vector<string> m; // Inserting the elements one by one 
    for (int i = 1; i < myvector.size(); i++) {
        key = myvector[i][0];
        for (int j = 0; j < myvector[i].size(); j++) {
            m = myvector[i];
        }
        mymap.insert(make_pair(key, m));
    }
    //-------------------------------Write into Respective file()-------------------------
    logfile(__LINE__, "Others()", "Checking Other Status");
    map<string, vector<string>> ::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++) {
        vector<string> v1 = it->second;
        if (v1[1] == "Others") {
            for (int k = 0; k < v1.size(); k++) {
                others_file << v1[k] << ",";
            }
            others_file << endl;
        }
    }
    logfile(__LINE__, "Others()", "Data Entry Complete");
    cout << "--------------" << endl;
    cout << "\n OUTPUT : Others.csv\n";
    others_file.close();
    logfile(__LINE__, "Others()", "Closing Others.csv");
}
/*--------------OTHERS.csv END---------------------------------*/

/*--------------MAIN - START-----------------------------------*/
int main()
{
    string fileName = "Results.html";
    file.open(s, ios::out | ios::app);
    htmltoexcel abc(fileName);
    system("Pause");
    return 0;
}
/*--------------MAIN -END--------------------------------------*/
