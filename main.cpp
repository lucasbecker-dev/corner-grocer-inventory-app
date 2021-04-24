#include "Menu.h"
#include <Python.h>
#include <Windows.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
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
	Prints a histogram derived from the file parameter
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
	// TODO: implement dis
	return false;
}

int main() {
	//CallProcedure("printsomething");
	//std::cout << callIntFunc("PrintMe", "House") << std::endl;
	//std::cout << callIntFunc("SquareValue", 2);
	bool runningProgram = true;
	while (runningProgram) {
		try {
			CallProcedure("ItemCount"); // TODO: remove test case
			int testFreq = callIntFunc("ItemFreq", "Cranberries"); // TODO: remove test case
			CallProcedure("WriteFreqFile");
			cout << testFreq;
			auto mainMenu = std::make_unique<Menu>();
			int userInput = mainMenu->printAndGetInput();
			runningProgram = chooseProgramBranch(static_cast<Menu::choice>(userInput));
		}
		catch (const std::exception& e) {
			cout << "Error: " << e.what();
		}
	}
	return 0;
}