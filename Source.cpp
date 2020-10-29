#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
//#include <experimental/filesystem>
#include <ctime>
#include <istream>
#include <iterator>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

class htmltoexcel {
public:
	int x = 0;
	ofstream check;
	string input, line;
	fstream myfile;
	vector<vector<string> > myvector;
	vector<string> passed;
	vector<string> failed;
	vector<string> data;
	htmltoexcel(string fn);

private:
	string parse(char* string); //parse //write
	void start(string fileName); //sort
	void chj(string line);
	string removespace(string line);
	void pass();
	void fail();
};

htmltoexcel::htmltoexcel(string fn)
{
	string filename = fn;
	start(fn);
	pass();
	fail();
}

void htmltoexcel:: start(string fileName)
{
	check.open("Check.csv", ios::out);
	myfile.open(fileName.c_str(), ios::in | ios::app);
	if (!myfile)
	{
		cout << "file cannot open!";
	}
	//getline(myfile, input);
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

	for (int i = 0; i < myvector.size(); i++) {
		for (int j = 0; j < myvector[i].size(); j++) {
			check << myvector[i][j] << ",";
		}
		check << "\n";

	}

	cout << "--------------" << endl;
	cout << "\n OUTPUT : CHECK.csv\n";
	//sort();
	check.close();
}

string htmltoexcel:: removespace(string line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	return line;
}

void htmltoexcel:: chj(string line)
{
	char* char_arr;
	int c = 0;
	if ((line.find("<tr>") > line.length()) && (line.find("</tr>") > line.length()) && (line.find("<td>") < line.length()))
	{
		char_arr = &line[0];
		data.push_back(parse(char_arr));
	}
}

/*--------------PARSE----------------------------------*/
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
/*--------------PARSE - END----------------------------------*/

void htmltoexcel::pass()
{
	ofstream passed_file;
	passed_file.open("passed_file.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		passed_file << myvector[0][j] << ",";
	}
	passed_file << "\n";

	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "PASSED") {
			for (int j = 0; j < myvector[i].size(); j++) {
				passed_file << myvector[i][j] << ",";
			}
			passed_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : passed_file.csv\n";
	//sort();
	passed_file.close();
}

void htmltoexcel::fail()
{
	ofstream failed_file;
	failed_file.open("failed_file.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		failed_file << myvector[0][j] << ",";
	}
	failed_file << "\n";

	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "FAILED") {
			for (int j = 0; j < myvector[i].size(); j++) {
				failed_file << myvector[i][j] << ",";
			}
			failed_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : failed_file.csv\n";
	//sort();
	failed_file.close();

}

int main()
{
	int i = 0; //Variable to track whether we are inside the tag
	string fileName = "Results.html";
	htmltoexcel abc(fileName);
	system("Pause");
	return 0;
}

