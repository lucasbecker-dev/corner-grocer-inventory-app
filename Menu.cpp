#include "Menu.h"

#include <string>
#include <exception>
#include <memory>
#include <iostream>

/*
Description:
	Default constructor
Example:
	Menu* new_menu = new Menu();
*/
Menu::Menu() {
	// create unique_ptr to string containing menu text
	auto tempStringPtr = std::make_unique<std::string>(
		"\nCorner Grocer Item-Tracker Menu"
		"\n==============================="
		"\n   (1) List items purchased today"
		"\n   (2) Check specific item frequency"
		"\n   (3) Print histogram of items purchased today"
		"\n   (4) Exit program"
		"\nChoice: ");
	// transfer ownership of menu text string pointer to m_menu_text_
	m_menu_text_ = std::move(tempStringPtr);
	// initialize value type m_user_choice_ with no fancy tricks
	m_user_choice_ = Menu::choice::NONE;

	// at the end of this scope tempStringPtr deletes itself, so we don't have to
}

/*
Description:
	Move constructor
Example:
	myMenu = std::move(otherMenu)
*/
Menu::Menu(Menu&& r_menu) noexcept {
	m_menu_text_ = std::move(r_menu.m_menu_text_);
	m_user_choice_ = std::exchange(m_user_choice_, r_menu.getChoice());
}

/*
Description:
	Sets new Menu text for this instance of Menu
Example:
	myMenu.setMenuText("This is the new Menu text.");
Return:
	None
*/
void Menu::setMenuText(const std::string& t_menu_text) {
	// Take ownership of string as new Menu text
	try {
		auto tempPtr = std::make_unique<std::string>(t_menu_text);
		m_menu_text_ = std::move(tempPtr);
	}
	catch (const std::exception& e) { // TODO: find potential exceptions to explicitly catch
		std::cout << "Error: " << e.what();
	}
}

/*
Description:
	Prints the Menu's text without gathering user input
Example:
	Menu.print();
Output:
	Contents of m_menu_text_ (see default constructor)
Return:
	None
*/
void Menu::print() {
	std::cout << *m_menu_text_ << std::endl;
}

/*
Description:
	Prints the Menu's text and then gather's user input
Example:
	Menu::choice user_input = Menu.print_and_get_input();
Output:
	Contents of m_menu_text_ (see default constructor)
Return:
	User's input cast to the Menu::choice enum
*/
Menu::choice Menu::printAndGetInput() {
	// print text
	this->print();
	int user_input = 0;
	// set cin failbit to trip if needed
	std::cin.exceptions(std::iostream::failbit);
	// obtain and validate user input, throw exceptions as needed
	try {
		std::cin >> user_input;
		if (user_input < 1 || user_input > 4) {
			throw std::out_of_range("Choice must be one of the Menu options.");
		}
	}
	catch (const std::out_of_range& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	// cast input to Menu::choice and return
	return static_cast<Menu::choice>(user_input);
}

/*
Description:
	Overloaded stream extraction operator for easy printing of menu text
Example:
	std::cout << MyMenu;
Output:
	Contents of m_menu_text_ (see default constructor)
Return:
	calling output stream
*/
std::ostream& operator<<(std::ostream& os, const Menu& obj) {
	return os << obj.m_menu_text_;
}

/*
Description:
	Overloaded stream insertion operator for easy changing of user input
Example:
	std::cin >> MyMenu;
Output:
	None (only error messages if exceptions caught)
Return:
	calling input stream
*/
std::istream& operator>>(std::istream& is, Menu& obj) {
	// Obtain and validate user input:
	try {
		int temp;
		is >> temp;
		if (temp < 1 || temp > 4) {
			throw std::out_of_range("User input must be 1-4.");
		}
		obj.m_user_choice_ = static_cast<Menu::choice>(temp);
	}
	catch (const std::out_of_range& e) {
		std::cout << "Error: " << e.what();
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what();
	}
	// Return to calling stream insertion
	return is;
}