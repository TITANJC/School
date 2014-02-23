//FILE : Process Home Construction Data.cpp
//PROG : Joesph Olliff
//PURP : To read and process data from a file

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
using namespace std;

//Function prototypes here
string transType(char trans) //translate Item Codes
{
	string translation = "";
	switch (toupper(trans))
	{
		case 'M':
			translation = "MATLS";
			break;

		case 'L':
			translation = "LABOR";
			break;

		case 'I':
			translation = "INSPC";
			break;

		case 'C':
			translation = "CONTR";
			break;

		case 'E':
			translation = "ELECT";
			break;

		default:
			translation = "ERROR";
			break;
	}

	return translation;
}

double laborCalc(int hours, double charge) //Calculate hourly rate
{
	double result = 0.0;
	
	result = charge / static_cast<double>(hours);
	return result;
}

void dispSing(string name, string code, string type, double hour, double charge, int entry)
{
	cout.imbue(locale(""));

	hour *= 100;
	charge *= 100;

	cout << "\n\n" << setprecision(2) << fixed;
	cout << setw(2) << "#" << setw(14) << "CONTR CODE" << setw(14) << "ITEM NAME" << setw(10) << "TYPE" << setw(14) << "COST/HOUR" << setw(14) << "ITEM COST" << endl;
	cout << setw(2) << entry << setw(14) << code << setw(14) << name << setw(10) << type << setw(14);
	if (static_cast<int>(hour) > 0) { cout << put_money(hour) << setw(14) << put_money(charge) << endl << endl; }
	else { cout << " " << setw(14) << showbase << put_money(charge) << endl << endl; }
	system("pause");
}

void dispFull(string name[], string code[], string type[], double hour[], double charge[], int entry)
{
	int count = 0;
	int count2 = entry;
	cout.imbue(locale(""));
	entry = 0;

	cout << "\n\n" << setprecision(2) << fixed;
	cout << setw(2) << "#" << setw(14) << "CONTR CODE" << setw(14) << "ITEM NAME" << setw(10) << "TYPE" << setw(14) << "COST/HOUR" << setw(14) << "ITEM COST" << endl;
	for (count = 0; count < count2; count++)
	{
		entry++;
		hour[count] *= 100;
		charge[count] *= 100;
		cout << setw(2) << entry << setw(14) << code[count] << setw(14) << name[count] << setw(10) << type[count] << setw(14);
		if (static_cast<int>(hour[count]) > 0) { cout << put_money(hour[count]) << setw(14) << put_money(charge[count]) << endl; }
		else { cout << " " << setw(14) << showbase << put_money(charge[count]) << endl; }
	}
	cout << endl;
	system("pause");
}

int main()
{
	//Input file stream object to read the data file
	ifstream homedataIn;

	//Variables for the incoming fields
	string itemName, itemCode;
	char itemType;
	int hours, day;
	double charge;

	//Entry Storage Variables
	string name[100], code[100], type[100];
	double hourRate[100], totalCharge[100];
	int days[100];
	double greatChar = 0.0;
	
	//Tools
	int count = 0;
	int entryCount = 0;

	//Initialize Arrays
	for (count = 0; count < 100; count++)
	{
		name[count] = "";
		code[count] = "";
		type[count] = "";
		hourRate[count] = 0.0;
		totalCharge[count] = 0.0;
		days[count] = 0;
	}
	

	//Open the data file
	homedataIn.open("homefees.dat");
	if (homedataIn.is_open())
	{
		//Headers would be good to display here


		//Begin the central record-processing while loop
		count = 0;
		while (!homedataIn.eof())
		{
			//Read the next record (bottom of while loop)
			homedataIn >> itemName
				>> itemCode
				>> itemType
				>> hours
				>> charge
				>> day;
			name[count] = itemName;
			code[count] = itemCode;
			type[count] = transType(itemType);
			if (hours > 0)
			{
				hourRate[count] = laborCalc(hours, charge);
			}
			totalCharge[count] = charge;
			days[count] = day;
			entryCount++;

			dispSing(name[count], code[count], type[count], hourRate[count], totalCharge[count], entryCount);
			system("cls");
			count++;
		}//END OF RECORD PROCESSING WHILE LOOP

		//Close the data file since we are done with it
		homedataIn.close();

		dispFull(name, code, type, hourRate, totalCharge, entryCount);
		system("cls");
		//Display all totals next
		cout << "\n\nEnd of test run.\n";

	}//END IF FILE OPENED

	else  //File did not open
		cout << "The sales file did not open!\n";

	system("pause");
	return 0;
}//END MAIN