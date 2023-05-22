#include <vector>
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
	vector<vector<string>> content;
	vector<string> row;
	string line, word, fname;
	double avg_val = 0;
	int max_val = INT_MIN;
	int min_val = INT_MAX;
	int min_sum_of_wind_humid = INT_MAX;
	double med_val;
	double sum = 0;
	int launchDay;
	string launchDayTemp;
	string launchDayWind;
	string launchDayHum;
	string launchDayPrecip;
	string launchDayLight;
	string launchDayCloud;
	bool launchday = false;

	fname = argv[1];

	fstream file(fname, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file!" << endl;

	ofstream Report("WeatherReport.csv");
	Report << "Parameters/Values,Average,Max,Min,Median,Most appropriate launch day\n";
	


	for (int i = 1; i < content[0].size(); i++) {
		if (stoi(content[1][i]) > 2 && stoi(content[1][i]) < 31 && stoi(content[2][i]) <= 10 &&
			stoi(content[3][i]) < 60 && stoi(content[4][i]) == 0 && content[5][i] == "No" &&
			content[6][i] != "Cumulus" && content[6][i] != "Nimbus")
		{
			launchday = true;
			if (stoi(content[2][i]) + stoi(content[3][i]) < min_sum_of_wind_humid)
			{
				min_sum_of_wind_humid = stoi(content[2][i]) + stoi(content[3][i]);
				 launchDay = stoi(content[0][i]);
				 launchDayTemp = content[1][i];
				 launchDayWind = content[2][i];
				 launchDayHum = content[3][i];
				 launchDayPrecip = content[4][i];
				 launchDayLight = content[5][i];
				 launchDayCloud = content[6][i];
			}
		}

	}
		
	for (int i = 1; i < 5; i++)
	{
		sum = 0;
		max_val = INT_MIN;
		min_val = INT_MAX;

		for (int j = 1; j < content[i].size(); j++)
		{

			double number = stoi(content[i][j]);
			sum += number;
			if (number > max_val) max_val = number;
			if (number < min_val) min_val = number;

		}
		int cont_size = content[i].size()-1;
		
		avg_val = sum / cont_size;
		
		if (cont_size % 2 == 0) {

			double number = stoi(content[i][cont_size / 2]) + stoi(content[i][cont_size / 2 + 1]);
			med_val = number / 2;

		}
		else
			med_val = stoi(content[i][cont_size / 2+1]);
		Report << content[i][0] << "," << avg_val << "," << max_val << "," << min_val << "," << med_val << ",";
		if (launchday == true)
		{
			if (i == 1) Report << launchDayTemp << "\n";
			if (i == 2) Report << launchDayWind << "\n";
			if (i == 3) Report << launchDayHum << "\n";
			if (i == 4) Report << launchDayPrecip << "\n";
		}
		
	}
	if (launchday == true)
	{
		Report << content[5][0] << ",,,,," << launchDayLight << "\n";
		Report << content[6][0] << ",,,,," << launchDayCloud << "\n";
	}
	else 
	{
		Report << "\n";
		Report << content[5][0] << ",,,,,There is no appropriate launch day!\n";
		Report << content[6][0] << ",,,,,\n";
	}

		
		
}
        

        