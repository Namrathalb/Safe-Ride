#include <iostream>
#include <fstream>
#include <windows.h>
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
#include <string>
//#include <filesystem>

using namespace std;
int ci = 0, z = 0;

/*----------------LOGFILE - START------------------------------*/
inline string getCurrentDateTime() //RETURNS THE CURRENT DATE AND TIME TO LOG FILE NAME
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
string s = "log_" + getCurrentDateTime() + ".log"; //Log File is created
ofstream file;
template <typename T>
void logfile(int y, string x, T const& h) {
    file << ci << "\t\t\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t\t" << x << "\t\t\t\t" << h << "\n"; ci++;
}
template <typename T>
void logfile(int y, string x, T const& h, int w) {
    file << ci << "\t\t\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t\t" << x << "\t\t\t\t" << h << w << "\n"; ci++;
}
template <typename T>
void logfile(int y, string x, T const& h, string q) {
    file << ci << "\t\t\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t\t" << x << "\t\t\t\t" << h << q << "\n"; ci++;
}
/*----------------LOGFILE - END--------------------------------*/

class htmltoexcel {
public:
    string line;
    fstream myfile;
    vector<vector<string>> myvector;
    vector<string> passed;
    vector<string> failed;
    vector<string> data;
    htmltoexcel(string fn);
private:
    string Parsed(string string, int z);
    string Checks(char* string);
    void intial(string fileName);
    void Search(string line);
    void Splits();
};

/*--------------CONSTRUCTOR - START----------------------------*/
htmltoexcel::htmltoexcel(string fn)
{
    string filename = fn;
    logfile(__LINE__, "constr()", "Calling: intial()");
    intial(fn);
    logfile(__LINE__, "constr()", "Calling: Splits()");
    Splits();
}
/*--------------CONSTRUCTOR- END-------------------------------*/

/*--------------INTIAL - START---------------------------------*/
void htmltoexcel::intial(string fileName)
{
    myfile.open(fileName.c_str(), ios::in | ios::app);
    logfile(__LINE__, "intial()", "Opening: Results.html.");
    if (!myfile)
    {
        cout << "file cannot open!";
        logfile(__LINE__, "intial()", "File Cannot open");
    }
    logfile(__LINE__, "intial()", "Parsing: Started");
    while (line != "</html>") {
        Search(line);
        getline(myfile, line);
        if (data.size() == 6) {
            myvector.push_back(data);
            data.clear();
            z = 0;
        }
    }
    logfile(__LINE__, "intial()", "Parsing: Ended");
}
/*--------------INTIAL - END-----------------------------------*/

/*--------------SEARCH <td></td> - START-----------------------*/
void htmltoexcel::Search(string line)
{
    int c = 0;
    if ((line.find("<tr>") > line.length()) && (line.find("</tr>") > line.length()) && (line.find("<td>") < line.length())) {
        z++;
        data.push_back(Parsed(line, z));
    }
}
/*--------------SEARCH <td></td> - END-------------------------*/

/*--------------CHECKS - START---------------------------------*/
string htmltoexcel::Checks(char* string)
{
    int index = 0, in = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '<') {
            in = 1;
            continue;
        }
        else if (string[i] == '>') {
            in = 0;
            continue;
        }
        if (in == 0 && string[i] != ' ') {
            string[index] = string[i];
            index++;
        }
    }
    string[index] = '\0';
    return string;
}
/*--------------CHECKS - START---------------------------------*/

/*--------------PARSED - START---------------------------------*/
string htmltoexcel::Parsed(string str, int z)
{
    string r;
    logfile(__LINE__, "Checks()", "Tags parsed:", str);
    if (z == 5) {
        char* char_arr = &str[0];
        r = Checks(char_arr);
    }
    else {
        int x = str.find("<td>");
        int y = str.find("</td>");
        r = str.substr((x + 4), (y - 8));
    }
    logfile(__LINE__, "Checks()", "Extracted: ", r);
    return r;
}
/*--------------PARSED - END-----------------------------------*/

/*--------------Sort & Write into .csv File - START------------*/
void htmltoexcel::Splits()
{
    ofstream passed_file;
    passed_file.open("passed.csv", ios::out);
    logfile(__LINE__, "Splits()", "Creating Passed.csv");

    ofstream failed_file;
    failed_file.open("failed.csv", ios::out);
    logfile(__LINE__, "Splits()", "Creating failed.csv");

    ofstream others_file;
    others_file.open("Others.csv", ios::out);
    logfile(__LINE__, "Splits()", "Creating others.csv");

    for (int j = 0; j < myvector[0].size(); j++) {
        passed_file << myvector[0][j] << ",";
        failed_file << myvector[0][j] << ",";
        others_file << myvector[0][j] << ",";
    }
    passed_file << "\n";
    failed_file << "\n";
    others_file << "\n";
    //----------------------SORT()------------------------------
    logfile(__LINE__, "Splits()", "Sorting by Date(desc)");
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
    //--------------Write into Respective file()----------------
    logfile(__LINE__, "Splits()", "Checking PASSED, FAILED, ABORT status");
    map<string, vector<string>> ::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++) {
        vector<string> v1 = it->second;
        //=====================Passed=======================
        if (v1[1] == "PASSED") {
            for (int k = 0; k < v1.size(); k++) {
                if (k == (v1.size() - 1)) {
                    string t = v1[k];
                    string fg = "\"" + v1[k] + "\"";
                    passed_file << fg << ",";
                }
                else {
                    passed_file << v1[k] << ",";/* code */
                }
            }
            passed_file << endl;
        }
        //======================Failed======================
        if (v1[1] == "FAILED") {
            for (int k = 0; k < v1.size(); k++) {
                if (k == (v1.size() - 1)) {
                    string t = v1[k];
                    string s = "\""; string u = """";
                    size_t pos = 0;
                    while ((pos = t.find(s, pos)) != std::string::npos) {
                        t.replace(pos, s.length(), u);
                        pos += u.length();
                    }
                    string fg = "\"" + t + "\"";
                    failed_file << fg << ",";
                }
                else {
                    failed_file << v1[k] << ",";/* code */
                }
            }
            failed_file << endl;
        }
        //======================Others======================
        if (v1[1] == "ABORTED") {
            for (int k = 0; k < v1.size(); k++) {
                if (k == (v1.size() - 1)) {
                    string t = v1[k];
                    string fg = "\"" + v1[k] + "\"";
                    others_file << fg << ",";
                }
                else {
                    others_file << v1[k] << ",";/* code */
                }
            }
            others_file << endl;
        }
    }
    logfile(__LINE__, "Splits()", "PASSED Data Entry Complete");
    cout << "--------------" << endl;
    cout << "\n OUTPUT : passed.csv\n";
    passed_file.close();
    logfile(__LINE__, "Splits()", "Closing Passed.csv");

    logfile(__LINE__, "Splits()", "FAILED Data Entry Complete");
    cout << "--------------" << endl;
    cout << "\n OUTPUT : failed.csv\n";
    failed_file.close();
    logfile(__LINE__, "Splits()", "Closing failed.csv");

    logfile(__LINE__, "Splits()", "ABORT Data Entry Complete");
    cout << "--------------" << endl;
    cout << "\n OUTPUT : Others.csv\n";
    others_file.close();
    logfile(__LINE__, "Splits()", "Closing Others.csv");
}
/*--------------Sort & Write into .csv File - END--------------*/

/*--------------MAIN - START-----------------------------------*/
int main()
{
    string fileName = "Results.html";
    string dst;
    cout << "Enter the File path: ";
    getline(cin, dst);
    string path = dst+"\\" + fileName;
    cout << path <<"\n";
    file.open(s, ios::out | ios::app);
    file << "Index" << "\t\t\t" << "TIMESTAMP" << "\t\t\t\t" << "Linenumber" << "\t\t\t" << "Function Name" << "\t\t\t" << "User value" << "\n"; ci++;
    htmltoexcel abc(path.c_str());
    system("Pause");
    return 0;
}
/*--------------MAIN -END--------------------------------------*/
