// MARUF_EMRE_KARATAY_20170702008.cpp : This file contains the 'main' function. Program execution begins and ends there.
//MARUF EMRE KARATAY 20170702008
// INPUT FILE NAME SOULD BE input.txt

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

//STL linked list
#include <list>
//to read and write
#include <fstream>

//to remove spaces in input.txt
#include <algorithm>



void readtostring(string &readf) {
	ifstream myfile;
	myfile.open("input.txt");
	if (!myfile) {
		cout << "Unable to open file input.txt";
		exit(-1);   // call system to stop
	}
	getline(myfile, readf);
	if (readf.empty()) {
		cout << "input.txt is empty" << endl;
		exit(-1);
	}
	myfile.close();

	//removes spaces
	readf.erase(remove(readf.begin(), readf.end(), ' '), readf.end());

	//check if first and last element of input file contains + or * for instance  inputfile.txt = "5+5 +" 
	if (readf[0] == '+' || readf[0] == '*' || readf[readf.size()-1] == '+' || readf[readf.size() - 1] == '*' ) {
		cout << endl << "!!!!!!!!!ERROR CHECK YOUR INPUT FILE!!!!!!!!!" << endl;
		exit(-1);
	}


}


void writetofile(list<int> bigint1) {
	ofstream outFile;
	outFile.open("output.txt");
	list<int>::iterator f;

	for (f = bigint1.begin(); f != bigint1.end(); f++) {
		if (!(*f < 10 && *f >= 0)) {
			cout << endl << "!!!!!!!!!ERROR CHECK YOUR INPUT FILE!!!!!!!!!" << endl;
			exit(-1);
		}
	}


	cout << "The result is : ";
	
	for (f = bigint1.begin(); f != bigint1.end(); f++) {
		cout << *f;
		outFile << *f;
	}
	cout << endl << endl << endl  << "The result is saved to output.txt" << endl;
	outFile.close();
}


void freeBigInt(list<int> &bigint1) {
	while (!bigint1.empty()) {
		bigint1.pop_back();
	}
}

//creates a list from readf between a1 and a2 index
void createBigInt(int a1, int a2, string readf, list<int> &bigint1) {
	freeBigInt(bigint1);
	for (a1; a1 <= a2; a1++) {
		int a = readf[a1] - '0';
		bigint1.push_back(a);

		//check if there is not number input like a,b,c,d,e,f etc. 
		if (!(a<10 && a>-1)) {
			cout << endl << "!!!!!!!!!ERROR CHECK YOUR INPUT FILE!!!!!!!!!" << endl;
			exit(-1);
		}

	}

}

//bigint1 = bigint2 and frees bigint2 
void updateBigInt(list<int> &bigint1, list<int> &bigint2) {
	freeBigInt(bigint1);
	while (!bigint2.empty()) {
		bigint1.push_front(bigint2.back());
		bigint2.pop_back();
	}
}


//adds bigint1 and bigint2 and saves the result to bigint1 and frees bigint2
void addBigInt(list<int> &bigint1, list<int> &bigint2) {
	int carry = 0;
	int sum = 0;
	list<int> sumlist;
	list<int>::iterator i;
	list<int>::iterator a;
	i = bigint1.end();
	a = bigint2.end();
	if (!bigint1.empty() && !bigint2.empty()) {
		i--;
		a--;

		while (i != bigint1.begin() && a != bigint2.begin()) {
			sum = *i + *a + carry;
			carry = sum / 10;
			sumlist.push_front(sum % 10);
			i--;
			a--;

		}
		sum = *i + *a + carry;
		carry = sum / 10;
		sumlist.push_front(sum % 10);
		if (i != bigint1.begin()) {
			i--;
			while (i != bigint1.begin()) {
				sum = *i + carry;
				carry = sum / 10;
				sumlist.push_front(sum % 10);
				i--;
			}
			sum = *i + carry;
			carry = sum / 10;
			sumlist.push_front(sum % 10);

		}
		else if (a != bigint2.begin()) {
			a--;
			while (a != bigint2.begin()) {
				sum = *a + carry;
				carry = sum / 10;
				sumlist.push_front(sum % 10);
				a--;
			}
			sum = *a + carry;
			carry = sum / 10;
			sumlist.push_front(sum % 10);

		}
		if (carry != 0) {
			sumlist.push_front(carry);
		}

		freeBigInt(bigint2);

		updateBigInt(bigint1, sumlist);

	}
	else if (bigint1.empty()) {
		updateBigInt(bigint1, bigint2);

	}

}


//multiplies bigint1 and bigint2 and saves the result to bigint1 and frees bigint2
void multiplyBigInt(list<int> &bigint1, list<int> &bigint2) {
	list<int> mult1, mult2;
	int carry = 0;
	int result = 0;
	int controlzeros = 1;
	list<int>::iterator i;
	list<int>::iterator a;

	a = bigint2.end();

	if (!bigint1.empty() && !bigint2.empty()) {
		a--;
		while (a != bigint2.begin()) {
			i = bigint1.end();
			i--;

			while (i != bigint1.begin()) {
				result = *i * *a + carry;
				carry = result / 10;
				mult1.push_front(result % 10);
				i--;
			}
			if (i == bigint1.begin()) {
				result = *i * *a + carry;
				carry = result / 10;
				mult1.push_front(result % 10);
			}
			while (carry != 0) {
				mult1.push_front(carry % 10);
				carry = carry / 10;
			}

			addBigInt(mult2, mult1);


			for (int m = 0; m < controlzeros; m++)
				mult1.push_front(0);

			controlzeros++;
			a--;

		}

		if (a == bigint2.begin()) {
			i = bigint1.end();
			i--;

			while (i != bigint1.begin()) {
				result = *i * *a + carry;
				carry = result / 10;
				mult1.push_front(result % 10);
				i--;
			}
			if (i == bigint1.begin()) {
				result = *i * *a + carry;
				carry = result / 10;
				mult1.push_front(result % 10);

			}
			while (carry != 0) {
				mult1.push_front(carry % 10);
				carry = carry / 10;
			}

			addBigInt(mult2, mult1);
		}

		freeBigInt(bigint2);
		freeBigInt(mult1);

		updateBigInt(bigint1, mult2);

	}
	if (bigint1.empty())
		updateBigInt(bigint1, bigint2);

}


//first the function finds sum of products, adds numbers and sum of products and saves result to bigint1
void findresult(list<int> &bigint1, string &readf) {
	list<int> list1, list2,bigint2;
	int countm = 0;
	bool isstar = false;
	for (int p = 0; readf[p] != '\0'; p++) {
		if (readf[p] == '*')
			countm++;
	}
	int i = -1, a = 0, c = 0;
	for (int p = 0; p < countm; p++) {

		i++;
		for (i; i <= (int)readf.size()  && readf[i] != '*'; i++);
		if (i <= (int)readf.size()) {

   			for (c = i + 2; c != readf.size() && readf[c] != '+' && readf[c] != '*' ; c++);
			createBigInt(i + 1, c - 1, readf, list1);

			for (a = i - 2; a != -1 && readf[a] != '+' && readf[a] != '*' ; a--);
			createBigInt(a + 1, i - 1, readf, list2);


			if (c < (int)readf.size()) {
				if (readf[c] == '*')
					isstar = true;
				else
					isstar = false;
			}
			else
				isstar = false;

			if (!isstar) {
				multiplyBigInt(list1, list2);
				multiplyBigInt(bigint2, list1);
				addBigInt(bigint1, bigint2);
			}
			else {

				multiplyBigInt(bigint2, list2);
				countm++;
			}

		}

	}


	countm = 0;
	for (int p = 0; readf[p] != '\0'; p++) {
		if (readf[p] == '+')
			countm++;
	}

	i = -1, a = 0;
	for (int p = 0; p < countm + 1; p++) {
		i++;
		for (i; i != readf.size() && readf[i] != '+'; i++);
		if (i <= (int)readf.size()) {

			for (a = i - 2; a != -1 && readf[a] != '*' && readf[a] != '+'; a--);
			
			if (a == -1) {
				createBigInt(a + 1, i - 1, readf, list1);
				addBigInt(bigint1, list1);
			}
			else if (readf[a] == '+') {

				createBigInt(a + 1, i - 1, readf, list1);
				addBigInt(bigint1, list1);

			}
			
		}

	} 
	
}


int main()
{
	list<int> bigint1;
	string readf;
	
	readtostring(readf);
	cout << "The input file:" << readf << endl << endl << endl ;

	findresult(bigint1, readf);

	writetofile(bigint1);

	return 0;
}

