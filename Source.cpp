#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <filesystem>
#include <ctime>
#include <istream>
#include <iterator>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <functional>
using namespace std;

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
	string parse(char* string); 
	void intial(string fileName); 
	void chj(string line);
	string removespace(string line);
	void pass();
	void fail();
	void others();
};

/*--------------CONSTRUCTOR - START----------------------------*/
htmltoexcel::htmltoexcel(string fn)
{
	string filename = fn;
	intial(fn);
	pass();
	fail();
	others();
}
/*--------------CONSTRUCTOR- END-------------------------------*/

/*--------------INTIAL - START---------------------------------*/
void htmltoexcel::intial(string fileName)
{
	myfile.open(fileName.c_str(), ios::in | ios::app);
	if (!myfile)
	{
		cout << "file cannot open!";
	}

	while (line != "</html>")
	{
		line = removespace(line);
		chj(line);
		getline(myfile, line);

		if (data.size() == 6) {
			myvector.push_back(data);
			data.clear();
		}
	}
}
/*--------------INTIAL - END-----------------------------------*/

/*--------------REMOVE SPACES - START--------------------------*/
string htmltoexcel::removespace(string line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	return line;
}
/*--------------REMOVE SPACES - END----------------------------*/

/*--------------CHECK TAG - START------------------------------*/
void htmltoexcel::chj(string line)
{
	char* char_arr;
	int c = 0;
	if ((line.find("<tr>") > line.length()) && (line.find("</tr>") > line.length()) && (line.find("<td>") < line.length()))
	{
		char_arr = &line[0];
		data.push_back(parse(char_arr));
	}
}
/*--------------CHECK TAG - END--------------------------------*/

/*--------------PARSE - START----------------------------------*/
string htmltoexcel::parse(char* string)
{
	int index = 0, in = 0;
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == '<')
		{
			in = 1;
			continue;
		}
		else if (string[i] == '>')
		{
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
void htmltoexcel::pass()
{
	ofstream passed_file;
	passed_file.open("passed.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		passed_file << myvector[0][j] << ",";
	}
	passed_file << "\n";

	sort(myvector[0].begin(), myvector[0].end(), greater <>());

	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "PASSED") {
			for (int j = 0; j < myvector[i].size(); j++) {
				passed_file << myvector[i][j] << ",";
			}
			passed_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : passed.csv\n";
	//sort();
	passed_file.close();
}
/*--------------PASSED.csv END---------------------------------*/

/*--------------FAILED.csv START-------------------------------*/
void htmltoexcel::fail()
{
	ofstream failed_file;
	failed_file.open("failed.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		failed_file << myvector[0][j] << ",";
	}
	failed_file << "\n";

	sort(myvector[0].begin(), myvector[0].end(), less<string>());

	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "FAILED") {
			for (int j = 0; j < myvector[i].size(); j++) {
				failed_file << myvector[i][j] << ",";
			}
			failed_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : failed.csv\n";
	//sort();
	failed_file.close();
}
/*--------------FAILED.csv END---------------------------------*/

/*--------------OTHERS.csv START-------------------------------*/
void htmltoexcel::others()
{
	ofstream others_file;
	others_file.open("Others.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		others_file << myvector[0][j] << ",";
	}
	others_file << "\n";

	sort(myvector[0].begin(), myvector[0].end(), greater <string>());

	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "OTHERS") {
			for (int j = 0; j < myvector[i].size(); j++) {
				others_file << myvector[i][j] << ",";
			}
			others_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : Others.csv\n";
	//sort();
	others_file.close();
}
/*--------------OTHERS.csv END---------------------------------*/

/*--------------MAIN - START-----------------------------------*/
int main()
{
	string fileName = "Results.html";
	htmltoexcel abc(fileName);
	system("Pause");
	return 0;
}
/*--------------MAIN -END--------------------------------------*/
