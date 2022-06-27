#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
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
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
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
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void mainMenu() {
	cout << "*****    Make a Selection    *****" << endl;
	cout << "1: List All Items and Quantities" << endl;
	cout << "2: Specific Item Count" << endl;
	cout << "3: Create Histogram" << endl;
	cout << "4: Exit" << endl;
	cout << endl;
}

void listAll() {
	CallProcedure("printAll");
}

void searchAndCountItem() {
	string item = "";
	cout << "What would you like to search for?" << endl;
	cin >> item;
	cout << endl;
	cout << item << ": " << callIntFunc("countSpecific", item) << endl;
	cout << endl;
}

void histogram() {
	CallProcedure("writeFreqFile");
	ifstream file;
	string item;
	string count;
	file.open("frequency.dat");
	getline(file, item, ' ');
	while (!file.fail()) {
		string stars = "";
		getline(file, count);
		for (int i = 0; i < stoi(count); i++) {
			stars += "*";
		}
		if (!file.fail()) {
			cout << left << setw(15) << setfill(' ') << item << right << stars << endl;
			//cout << stars << endl;
		}
		getline(file, item, ' ');
	}
	cout << endl;
	file.close();
}

void run() {
	boolean run = true;
	while (run) {
		string choice;
		mainMenu();
		cin >> choice;
		cout << endl;
		if (choice.length() > 1) {
			choice = '0';
		}
		switch (choice.at(0)) {
			case '1':
				listAll();
				break;
			case '2':
				searchAndCountItem();
				break;
			case '3':
				histogram();
				break;
			case '4':
				cout << "Goodbye." << endl;
				run = false;
				break;
			default:
				cout << "Invalid input. Enter 1, 2, 3, or 4." << endl;
				break;
		}
	}
}

int main()
{
	run();
	return 0;
}

