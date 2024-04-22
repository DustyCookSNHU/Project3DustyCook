/**
 * Dusty Cook
 * CS-210
 * Project 3
 * 04/19/2024
 */

#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

bool quit = false;

struct PurchaseData {
	string itemName;
	int count;
};

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	Py_Initialize();
	pName = PyUnicode_FromString((char*)"python");
	pModule = PyImport_Import(pName); 
	pDict = PyModule_GetDict(pModule); 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();
 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	Py_Initialize();
	pName = PyUnicode_FromString((char*)"python");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();

	delete[] procname;

	return _PyLong_AsInt(presult);
}
vector<PurchaseData> GetFrequencyDataFromFile(string fileName) {
	ifstream inFS;
	vector<PurchaseData> itemPurchaseData;
	PurchaseData currentData;
	string currentLine;

	inFS.open(fileName, ios::in);
	if (!inFS.is_open()) {
		cout << "Could not open file: " << fileName << endl;
		return vector<PurchaseData> {};
	}

	while (!inFS.eof()) {
		getline(inFS, currentLine);

		if (!(currentLine == "")) {
			stringstream ss(currentLine);

			ss >> currentData.itemName;
			ss >> currentData.count;

			itemPurchaseData.push_back(currentData);
		}
	}

	inFS.close();

	return itemPurchaseData;
}
void PrintPurchaseHistogram() {
	vector<PurchaseData> data = GetFrequencyDataFromFile("frequency.dat");

	for (unsigned int i = 0; i < data.size(); ++i) {
		cout << data.at(i).itemName << " ";
		for (unsigned int j = 0; j < data.at(i).count; ++j) {
			cout << "*";
		}
		cout << endl;
	}
}

void ProcessMenuSelection(string selection) {
	cout << endl;

	if (selection == "4") {
		quit = true;
		cout << "Exiting application..." << endl;
		return;
	}

	if (selection == "1") {
		cout << "Showing report of today's sales..." << endl;

		CallProcedure("PrintItemsPurchasedFrequency");
		cout << endl;
		return;
	}

	if (selection == "2") {
		string userInput;

		cout << "Which item would you like to view?:" << endl;
		cin.ignore();
		cin >> userInput;

		cout << userInput << ": " << callIntFunc("PrintItemPurchaseFrequency", userInput) << endl;

		cout << endl;

		return;
	}

	if (selection == "3") {
		cout << "Showing today's sold items in ..." << endl;

		CallProcedure("GeneratePurchaseFrequencyReport");
		PrintPurchaseHistogram();

		cout << endl;
		return;
	}

	cout << "Please enter a valid selection..." << endl << endl;
}

void PrintMenu() {
	cout << "        Corner Grocer Sales History" << endl;
	cout << "*********************************************" << endl;
	cout << "1. Show today's sales report with digital number form" << endl;
	cout << "2. Show today's sales report for a specific item" << endl;
	cout << "3. Show today's sold items in histogram form" << endl;
	cout << "4. Exit Application" << endl;
	cout << "Enter your selection 1-4:" << endl;
}

int main()
{
	string userSelection;

	while (!quit) {
		PrintMenu();
		cin >> userSelection;
		ProcessMenuSelection(userSelection);
	}

	return 0;
}