/*
CMPT 128
Sameer Hossain
Start date: Oct. 30, 2018
Last edited: Nov. 16 2018
Code to sort coins into their respective categories by reading input files,
put them in rolls/containers and replace rolls/containers after they're full,
do the same for bent & misc. coins except put them in containers which are also replaced once full
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
/*
void ignoringdata(char c, istream& inFile)
{
	c = inFile.peek();

	while (c == ' ' || c == '   ')
	{
		c = inFile.get();
		c = inFile.peek();
	}
}
*/
int main()
{
	//Declare & initialize variables, constants
	//chars, files, strings, etc...																					
	ifstream inFile;
	ofstream outFile;
	char c = ' ';
	char fdIn[1024] = { '\0' };
	char fdOut[1024] = { '\0' };

	//Integers needed for counting
	/*int kys = 0; //extra counters incase I need it
	int oof = 0;
	int nyan = 0;
	*/
	int numlines = 0;

	int nickels = 0;
	int Nrolls = 0;

	int dimes = 0;
	int Drolls = 0;

	int quarters = 0;
	int Qrolls = 0;

	int loonies = 0;
	int Lrolls = 0;

	int toonies = 0;
	int Trolls = 0;

	int other = 0;
	int otter = 0;
	int Ocontain = 0;

	int bent = 0;
	int Bcontain = 0;

	//Input file text, data peices, will be read and set to these as variables
	double weight = 0.0;
	double diameter = 0.0;
	double Wgrams = 0.0;
	double Dmilli = 0.0;
	double otherWeight = 0.0;
	double otterWeight = 0.0;
	double bentweight = 0.0;
	double noweight = 0.0;
	double anotherweight = 0.0;

	//Limits for the ranges for each coin, weight and diameter limits of each coin type, rolls and containers
	const double BENTWEIGHTLIM = 100;
	const double OTHERWEIGHTLIM = 200;
	const double MINWEIGHT = 1;
	const double MAXWEIGHT = 255;
	const double MINDIAMETER = 1;
	const double MAXDIAMETER = 255;

	const double MAXNIXKWEIGHT = 4.3;
	const double MINNICKWEIGHT = 3.6;
	const double MAXNICKDIAMETER = 21.8;
	const double MINNICKDIAMETER = 20.2;
	const double NICKROLLLIM = 40;

	const double MAXDIMEWEIGHT = 2.2;
	const double MINDIMEWEIGHT = 1.3;
	const double MAXDIMEDIAMETER = 18.7;
	const double MINDIMEDIAMETER = 17.3;
	const double DIMEROLLLIM = 50;

	const double MAXQUARTWEIGHT = 4.8;
	const double MINQUARTWEIGHT = 4.0;
	const double MAXQUARTDIAMETER = 24.6;
	const double MINQUARTDIAMETER = 22.8;
	const double QUARTROLLLIM = 40;

	const double MAXLOONWEIGHT = 7.5;
	const double MINLOONWEIGHT = 6.5;
	const double MAXLOONDIAMETER = 27.0;
	const double MINLOONDIAMETER = 25.0;
	const double LOONROLLLIM = 25;

	const double MAXTOONWEIGHT = 7.85;
	const double MINTOONWEIGHT = 6.75;
	const double MAXTOONDIAMETER = 29.1;
	const double MINTOONDIAMETER = 26.9;
	const double TOONROLLLIM = 25;

	//Strings... speaks for itself, to read the words in the text, like "NoMatch" & "bent", and used in conditions
	string blank;
	string junk;
	string match;

	//String constants
	const string UNUSABLE = "bent";
	const string NOTBENT = "usuable";
	const string BOTHMATCH = "BothMatch";
	const string ONEMATCH = "OneMatch";
	const string NOMATCH = "NoMatch";

	//setting precision beforehand just to make things easier
	cout << fixed << setprecision(2);
	outFile << fixed << setprecision(2);



	//3 tries to get input and output file names correct each
	do
	{
		for (int i = 0; i > 3; i++)
		{
			cerr << "ERROR: You exceeded maximum number of tries allowed\n";
			cerr << "while entering the input file name\n";
			return 1;
		}
		cout << "Type the name of the input file containing sensor readings:\n";
		cin >> fdIn;
		inFile.open(fdIn);
		if (inFile.fail())
		{
			cerr << "ERROR: File " << fdIn << " could not be opened for input\n";
		}
	} while (inFile.fail());

	do
	{
		for (int i = 0; i > 3; i++)
		{
			cerr << "ERROR: You exceeded maximum number of tries allowed\n";
			cerr << "while entering the output file name\n";
			return 2;
		}
		cout << "Type the name of the output file which will hold the simulation results:\n";
		cin >> fdOut;
		outFile.open(fdOut);
		if (outFile.fail())
		{
			cerr << "ERROR: File " << fdOut << " could not be opened for output\n";
		}
	} while (inFile.fail());

	//Error messages for each individual lines, 11 a) to j)														
	if (!(inFile >> numlines))
	{
		if (inFile.eof())
		{
			cerr << "ERROR: Input data file is empty\n";
			return 3;
		}
		else
		{
			cerr << "ERROR: First piece of data in the file is not an integer\n";
			return 4;
		}
	}
	if (numlines < 1 || numlines > 5000)
	{
		cerr << "ERROR: The number of sensor readings is out of range\n";
		return 5;
	}


	for (int i = 0; i < numlines; i++)
	{
		if (!(inFile >> weight))
		{
			if (inFile.eof())
			{
				cerr << "ERROR: No more data\n";
				cerr << "Simulation completed early before line " << i + 1 << " of input\n";
				break;
			}
			else
			{
				cerr << "ERROR: Weight sensor value read on line " << i + 1 << " is not an integer\n";
				cerr << "Simulation terminated early: Please correct your data file\n";
				break;
			}
		}
		//																													

		//ignoringdata(c, inFile);
								 //																																																					
		c = inFile.peek();

		while (c == ' ' || c == ' ')
		{
			c = inFile.get();
			c = inFile.peek();
		}
		if (c == '\n')
		{
			cerr << "ERROR: Weight sensor measurement only\n";
			cerr << "Ignoring line " << i + 1 << " of the input file\n";
			continue;
		}
		if (!(inFile >> diameter))
		{
			cerr << "ERROR: Diameter sensor value read on line " << i + 1 << " is not an integer\n";
			cerr << "Simulation terminated early: Please correct your data file\n";
			break;
		}

		//ignoringdata(c, inFile);
		c = inFile.peek();

		while (c == ' ' || c == ' ')
		{
			c = inFile.get();
			c = inFile.peek();
		}
		if (c == '\n')
		{
			cerr << "ERROR: Weight and diameter sensor measurements only\n";
			cerr << "Ignoring line " << i + 1 << " of the input file\n";
			continue;
		}

		inFile >> junk;
		if (junk != "usable" && junk != "bent")
		{
			cerr << "ERROR: Result of test to determine if coin is bent at line " << i + 1 << " is invalid\n";
			cerr << "Ignoring this line of data\n";
			inFile.ignore(1024, '\n');
			continue;
		}

		//ignoringdata(c, inFile);
		c = inFile.peek();

		while (c == ' ' || c == ' ')
		{
			c = inFile.get();
			c = inFile.peek();
		}
		if (c == '\n')
		{
			cerr << "ERROR: Weight and diameter sensor measurements and bent string only\n";
			cerr << "Ignoring line " << i + 1 << " of the input file\n";
			continue;
		}

		inFile >> match;
		if (match != BOTHMATCH && match != ONEMATCH && match != NOMATCH)
		{
			cerr << "ERROR: image processing result at line " << i + 1 << " is invalid\n";
			cerr << "Ignoring this line of data\n";
			continue;
		}

		//ignoringdata(c, inFile);
		c = inFile.peek();

		while (c == ' ' || c == ' ')
		{
			c = inFile.get();
			c = inFile.peek();
		}
		if (c != '\n')
		{
			cerr << "ERROR: Extra data at line " << i + 1 << ".  Ignoring extra data\n";
			inFile.ignore(1024, '\n');
		}

		//Converting integer to weight or diameter in grams or millimeters
		Wgrams = 2 * weight * 5 / 255;
		Dmilli = 10 + diameter / 8.5;

		//Placing bent coins in containers & taking their total weight
		if (junk == UNUSABLE)
		{
			bent++;

			noweight += Wgrams;
			bentweight += Wgrams;

			cout << "The Coin Sorter has sent this coin to the bent coin container\n";
			outFile << "The Coin Sorter has sent this coin to the bent coin container\n";

			if (bentweight > BENTWEIGHTLIM)
			{

				cout << "The bent coin container has been replaced\n"
					<< "The bent coin container has been replaced\n"
					<< "The coin in the new bent coin container weighs " << Wgrams << " grams\n";

				outFile << "This coin does not fit in the bent coin container\n"
					<< "The bent coin container has been replaced\n"
					<< "The coin in the new bent coin container weighs " << Wgrams << " grams\n";

				bentweight = Wgrams;
				bent = 0;
			}
			else
			{
				cout << "The coins in the bent coin container now weigh  " << setw(5) << bentweight << " grams\n";

				outFile << "The coins in the bent coin container now weigh  " << setw(5) << bentweight << " grams\n";
			}
			continue;
		}

		//Checking if the sensor readings are out of range
		if (weight < MINWEIGHT || weight > MAXWEIGHT || diameter < MINDIAMETER || diameter > MAXDIAMETER)
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << i + 1 << " in the input file\n";
			continue;
		}

		//Taking each coin, counting them, placing them in rolls & counting the rolls by checking if they're intheir specified range 
		//and checking if both sides of the coin match																																			(>'o')>						<('w'<)
		else if ((Wgrams <= MAXNIXKWEIGHT && Wgrams >= MINNICKWEIGHT) && (Dmilli <= MAXNICKDIAMETER && Dmilli >= MINNICKDIAMETER) && (match == BOTHMATCH))

		{
			nickels++;

			cout << "The Coin Sorter has sent one coin to the nickels wrapper\n";
			outFile << "The Coin Sorter has sent one coin to the nickels wrapper\n";

			if (nickels >= NICKROLLLIM)
			{
				Nrolls++;
				nickels = 0;

				cout << "The nickel wrapper is now full\n"
					<< "The nickel wrapper has now been replaced\n";


				outFile << "The nickel wrapper is now full\n"
					<< "The nickel wrapper has now been replaced\n";

			}
			else
			{
				cout << "There are now " << nickels << " coins in the nickels wrapper\n";

				outFile << "There are now " << nickels << " coins in the nickels wrapper\n";
			}
			continue;

		}
		else if ((Wgrams <= MAXDIMEWEIGHT && Wgrams >= MINDIMEWEIGHT) && (Dmilli <= MAXDIMEDIAMETER && Dmilli >= MINDIMEDIAMETER) && (match == BOTHMATCH))

		{
			dimes++;

			cout << "The Coin Sorter has sent one coin to the dimes wrapper\n";
			outFile << "The Coin Sorter has sent one coin to the dimes wrapper\n";

			if (dimes >= DIMEROLLLIM)
			{
				Drolls++;
				dimes = 0;

				cout << "The dime wrapper is now full\n"
					<< "The dime wrapper has now been replaced\n";

				outFile << "The dime wrapper is now full\n"
					<< "The dime wrapper has now been replaced\n";

			}
			else
			{
				cout << "There are now " << dimes << " coins in the dimes wrapper\n";

				outFile << "There are now " << dimes << " coins in the dimes wrapper\n";
			}
			continue;

		}
		else if ((Wgrams <= MAXQUARTWEIGHT && Wgrams >= MINQUARTWEIGHT) && (Dmilli <= MAXQUARTDIAMETER && Dmilli >= MINQUARTDIAMETER) && (match == BOTHMATCH))

		{
			quarters++;

			cout << "The Coin Sorter has sent one coin to the quarters wrapper\n";
			outFile << "The Coin Sorter has sent one coin to the quarters wrapper\n";

			if (quarters >= QUARTROLLLIM)
			{
				Qrolls++;
				quarters = 0;

				cout << "The quarter wrapper is now full\n"
					<< "The quarter wrapper has now been replaced\n";

				outFile << "The quarter wrapper is now full\n"
					<< "The quarter wrapper has now been replaced\n";
			}
			else
			{
				cout << "There are now " << quarters << " coins in the quarters wrapper\n";

				outFile << "There are now " << quarters << " coins in the quarters wrapper\n";
			}
			continue;

		}
		else if ((Wgrams <= MAXLOONWEIGHT && Wgrams >= MINLOONWEIGHT) && (Dmilli <= MAXLOONDIAMETER && Dmilli >= MINLOONDIAMETER) && (match == BOTHMATCH))

		{
			loonies++;

			cout << "The Coin Sorter has sent one coin to the loonies wrapper\n";
			outFile << "The Coin Sorter has sent one coin to the loonies wrapper\n";

			if (loonies >= LOONROLLLIM)
			{
				Lrolls++;
				loonies = 0;

				cout << "The loonie wrapper is now full\n"
					<< "The loonie wrapper has now been replaced\n";

				outFile << "The loonie wrapper is now full\n"
					<< "The loonie wrapper has now been replaced\n";
			}
			else
			{
				cout << "There are now " << loonies << " coins in the loonies wrapper\n";

				outFile << "There are now " << loonies << " coins in the loonies wrapper\n";
			}
			continue;

		}
		else if ((Wgrams <= MAXTOONWEIGHT && Wgrams >= MINTOONWEIGHT) && (Dmilli <= MAXTOONDIAMETER && Dmilli >= MINTOONDIAMETER) && (match == BOTHMATCH))

		{
			toonies++;

			cout << "The Coin Sorter has sent one coin to the toonies wrapper\n";
			outFile << "The Coin Sorter has sent one coin to the toonies wrapper\n";

			if (toonies >= TOONROLLLIM)
			{
				Trolls++;
				toonies = 0;

				cout << "The toonie wrapper is now full\n"
					<< "The toonie wrapper has now been replaced\n";

				outFile << "The toonie wrapper is now full\n"
					<< "The toonie wrapper has now been replaced\n";
			}
			else
			{
				cout << "There are now " << toonies << " coins in the toonies wrapper\n";

				outFile << "There are now " << toonies << " coins in the toonies wrapper\n";
			}
			continue;

		}
		else //Other counter for coins outside of
		{
			other++;
			otter++;
			otherWeight += Wgrams;
			otterWeight += Wgrams;

			cout << "The Coin Sorter has sent this coin to the other coin container\n";
			outFile << "The Coin Sorter has sent this coin to the other coin container\n";

			if (otherWeight > OTHERWEIGHTLIM)
			{
				Ocontain++;
				otter = 1;
				otherWeight = Wgrams;

				cout << "The coins in the other coin container now weigh " << setw(6) << otherWeight << " grams\n";

				outFile << "The coins in the other coin container now weigh " << setw(6) << otherWeight << " grams\n";
			}
			else
			{
				cout << "The coins in the other coin container now weigh " << setw(6) << otherWeight << " grams\n";

				outFile << "The coins in the other coin container now weigh " << setw(6) << otherWeight << " grams\n";
			}
			continue;
		}

	}
	/*
	SUMMARY OF ALL DATA goes here
																																																													__		  __
																																																													  \_("/)_/
	*/
	cout << endl << endl << endl << fixed << setprecision(0) << "SUMMARY\n"
		<< "The Coin Sorter made " << setw(3) << Nrolls << " rolls of nickels.\n"
		<< "    There are " << setw(2) << nickels << " nickels in the partially full roll.\n"

		<< "The Coin Sorter made " << setw(3) << Drolls << " rolls of dimes.\n"
		<< "    There are " << setw(2) << dimes << " dimes in the partially full roll.\n"

		<< "The Coin Sorter made " << setw(3) << Qrolls << " rolls of quarters.\n"
		<< "    There are " << setw(2) << quarters << " quarters in the partially full roll.\n"

		<< "The Coin Sorter made " << setw(3) << Lrolls << " rolls of loonies.\n"
		<< "    There are " << setw(2) << loonies << " loonies in the partially full roll.\n"

		<< "The Coin Sorter made " << setw(3) << Trolls << " rolls of toonies.\n"
		<< "    There are " << setw(2) << toonies << " toonies in the partially full roll.\n"

		<< "The Coin Sorter processed " << setw(5) << other << " other coins.\n"
		<< "    The other coins completely filled " << setw(3) << Ocontain << " containers\n"
		<< "    There were " << setw(2) << otter << " other coins in the partially full container\n"
		<< setprecision(3) << "    The total weight of the other coins was " << setw(9) << otterWeight << " grams\n"

		<< setprecision(4) << "The Coin Sorter processed " << setw(11) << noweight << " g of bent coins\n";


	 outFile << endl << fixed << setprecision(0) << "SUMMARY\n"
		 << "The Coin Sorter made " << setw(3) << Nrolls << " rolls of nickels.\n"
		 << "    There are " << setw(2) << nickels << " nickels in the partially full roll.\n"

		 << "The Coin Sorter made " << setw(3) << Drolls << " rolls of dimes.\n"
		 << "    There are " << setw(2) << dimes << " dimes in the partially full roll.\n"

		 << "The Coin Sorter made " << setw(3) << Qrolls << " rolls of quarters.\n"
		 << "    There are " << setw(2) << quarters << " quarters in the partially full roll.\n"

		 << "The Coin Sorter made " << setw(3) << Lrolls << " rolls of loonies.\n"
		 << "    There are " << setw(2) << loonies << " loonies in the partially full roll.\n"

		 << "The Coin Sorter made " << setw(3) << Trolls << " rolls of toonies.\n"
		 << "    There are " << setw(2) << toonies << " toonies in the partially full roll.\n"

		 << "The Coin Sorter processed " << setw(5) << other << " other coins.\n"
		 << "    The other coins completely filled " << setw(3) << Ocontain << " containers\n"
		 << "    There were " << setw(2) << otter << " other coins in the partially full container\n"
		 << setprecision(3) << "    The total weight of the other coins was " << setw(9) << otterWeight << " grams\n"

		 << setprecision(4) << "The Coin Sorter processed " << setw(11) << noweight << " g of bent coins\n";

	inFile.close();
	outFile.close();

	return 0;
}
