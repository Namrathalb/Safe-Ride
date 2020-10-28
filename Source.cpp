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
using namespace std;

string parse(char* string); //parse //write
void sortit(); //sort
int x = 0;
ofstream check;

void  sortit()
{
	vector<string> s;
	ifstream in("Check.csv");
	if (!in)
		cout << "File not found" << endl;

	for (auto a : s)
	{

	}
	std::sort(s.begin(), s.end(), [](string a, string b) {
		return a > b;
		});
   cout << "sorted:\n";
}

string removespace(string line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	return line;
}

void chj(string line)
{
	char* char_arr;
	string data[6];
	int i = 0;
	int c = 0;
	vector<string> myvector;
	
	if((line.find("<tr>") > line.length()) && (line.find("</tr>") > line.length()) && (line.find("<td>") < line.length()))
	{
		char_arr = &line[0];
		data[i] = parse(char_arr);	
		myvector.push_back(data[i]); i++;
	}
	for (int i = 0; i < myvector.size(); i++) 
	{
		check << myvector[i] << ",";
	} 
}

/*--------------PARSE----------------------------------*/
string parse(char* string)
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


int main()
{	
	int i = 0; //Variable to track whether we are inside the tag
	string fileName = "Results.html";
	string input, line;
	fstream myfile;
	
	check.open("Check.txt", ios::out);
	myfile.open(fileName.c_str(), ios::in | ios::app);	
	if (!myfile)
	{
		cout << "file cannot open!";
	}
	//getline(myfile, input);
	while(line != "</html>")
	{
		line = removespace(line);
		chj(line);
		/*if (arr[1] == "PASSED")
		{

		}
		else if (arr[1] == "FAILED")
		{

		}
		else if (arr[1] == "OTHERS")
		{

		}*/
		getline(myfile, line);		
	}
	
	cout << "--------------" << endl;
	cout << "\n OUTPUT : CHECK.txt\n";
	//sort();
	check.close();	
	system("Pause");
	return 0;
}