#include "Menu.h"
#include <Python.h>
#include <Windows.h>
#include <cstdio>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

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
void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
#pragma warning(suppress : 4996)
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
int callIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
#pragma warning(suppress : 4996)
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
#pragma warning(suppress : 4996)
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
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
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
int callIntFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
#pragma warning(suppress : 4996)
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
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
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

/*
Description:
	Prints a histogram derived from the file indicated in the filename parameter
Example:
	printHistogram();
Output:
	Item1 ****
	Item2 ******
	Item3 *****
	and so on...
Return:
	None
*/
void printHistogram() {
	try {
		// create ifstream to read file
		auto ifs = std::ifstream("frequency.dat");
		// temp storage for data read from file
		auto fileData = std::map<std::string, int>();
		auto itemName = std::string();
		int itemCount = 0;
		// save length of longest name for formatting histogram
		int maxNameLength = 0;
		// read while more item names available
		while (ifs >> itemName) {
			// read number of items
			ifs >> itemCount;
			// if itemName exists and itemCount is non-zero
			if (!itemName.empty() && itemCount) {
				// Check for new maxNameLength
				if (itemName.size() > maxNameLength) {
					maxNameLength = static_cast<int>(itemName.length());
				}
				// Add itemName and itemCount to std::map
				fileData.emplace(std::pair<std::string, int>(itemName, itemCount));
			}
			// if end of file reached, break loop
			if (ifs.eof()) { break; }
		}
		// add a buffer space to maxNameLength
		++maxNameLength;

		// Windows-Specific: get console buffer state and save it, will be used to edit output colors
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD savedAttributes;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		savedAttributes = consoleInfo.wAttributes;

		// set console text color to blue
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		cout << "Histogram - Items Purchased Today" << endl;
		cout << "=================================" << endl;
		// restore saved console settings
		SetConsoleTextAttribute(hConsole, savedAttributes);
		// read through saved std::map
		for (const auto& it : fileData) {
			// format output width based on maxNameLength and print itemName
			cout << setw(maxNameLength) << right << it.first << ": ";
			// set output text color to green
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			// print a * for each item in itemCount
			for (int i = 0; i < it.second; ++i) {
				cout << '*';
			}
			// restore save console settings
			SetConsoleTextAttribute(hConsole, savedAttributes);
			cout << endl;
		}
		// close file
		// ifs.close(); // Commented out because std::ifstream closes the file in the destructor, RAII style
	}
	catch (const std::exception& e) {
		cout << "Error: " << e.what() << endl;
	}
}

/*
Description:
	Get string from user and returns number of items available
Example:
	runPythonItemFreq()
Output:
	number of items of user's type in file
Return:
	None
*/
void runPythonItemFreq() {
	// get item to be checked from user input
	cout << "Enter item name (case-sensitive): ";
	// storage for user input
	std::string itemName;
	try {
		// checking for failed input exceptions
		cin.exceptions(std::ios_base::failbit);
		// get user input
		cin >> itemName;
		// call Python function and save resulting int
		const int itemCount = callIntFunc("ItemFreq", itemName);

		// Windows-Specific: get console buffer state and save it, will be used to edit output colors
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD savedAttributes;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		savedAttributes = consoleInfo.wAttributes;

		// set console text color to green
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		// print results
		cout << itemName << " purchased " << itemCount << " time(s) today." << endl;
		// restore saved console settings
		SetConsoleTextAttribute(hConsole, savedAttributes);
	}
	// catching failed input exceptions thrown by std::cin
	catch (const std::ios_base::failure& e) {
		cout << "Error code: " << e.code();
		cout << "Error message: " << e.what();
		cin.clear();
		cin.ignore(512, '\n');
	}
}

/*
Description:
	Runs the appropriate branch of the program and calls the relevant Python function
Example:
	bool continueRunning = chooseProgramBranch(userMenuSelection);
Output:
	Varies depending on Python function called, if any
Return:
	true if program should continue, false if not
*/
bool chooseProgramBranch(const Menu::choice& choice) {
	// check which value user input corresponds to as defined in Menu::choice
	switch (choice) {
	case Menu::choice::NONE:
		// if choice is NONE then user input was not obtained, this is the default value
		throw std::invalid_argument("User menu choice was not obtained.\n");

	case Menu::choice::ITEM_COUNT:
		// run ItemCount function in Python
		CallProcedure("ItemCount");
		break;

	case Menu::choice::ITEM_FREQ:
		// run function which collects user input and runs ItemFreq function in Python
		runPythonItemFreq();
		break;

	case Menu::choice::PRINT_HISTOGRAM:
		// runs function to print histogram of items purchased using file generated by Python function
		printHistogram();
		break;

	case Menu::choice::EXIT_PROGRAM:
		// return false back to main to indicate that program should stop running
		return false;

	default:
		// if this case is reached then the user's input was not one of the menu choices
		throw std::out_of_range("User menu choice does not match any menu options.\n");
	}
	// return true back to main to indicate that program should loop through again
	return true;
}

int main() {
	//CallProcedure("printsomething");
	//std::cout << callIntFunc("PrintMe", "House") << std::endl;
	//std::cout << callIntFunc("SquareValue", 2);

	// instantiate Menu with default constructor
	auto mainMenu = std::make_unique<Menu>();
	// check if program should keep looping
	bool runningProgram = true;
	while (runningProgram) {
		try {
			// print menu, get user input, and check if it's non-zero
			if (Menu::choice userInput = mainMenu->printAndGetInput()) {
				// run chosen program branch and indicate if program should continue looping
				runningProgram = chooseProgramBranch(userInput);
			}
		}
		// general exception catching as a backup because not all exceptions are explicitly caught as they should be
		catch (const std::exception& e) {
			cout << "Error: " << e.what();
		}
	}
	return 0;
}