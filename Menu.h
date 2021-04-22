#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <memory>
#include <ostream>

/*
Description:
	Prints a string formatted as a Menu.
	Can also obtain, validate, and returns the user's choice.
*/
class Menu {
public:
	// Enum for user input options
	enum choice {
		NONE = 0,
		ITEM_COUNT = 1,
		ITEM_FREQ = 2,
		PRINT_HISTOGRAM = 3,
		EXIT_PROGRAM = 4
	};

	// Constructors
	Menu(); // default constructor
	Menu(Menu&& r_menu) noexcept;
	explicit Menu(std::string* t_menu_text, Menu::choice t_user_choice = NONE)
		: m_menu_text_(t_menu_text), m_user_choice_(t_user_choice) {}
	// Setter/getter for Menu text
	void setMenuText(const std::string& t_menu_text);
	std::string& getMenuText() const { return *m_menu_text_; }
	// Getter/setter for user input
	void setChoice(const Menu::choice t_menu_choice) { m_user_choice_ = t_menu_choice; }
	Menu::choice getChoice() const { return m_user_choice_; }
	// Prints the Menu text
	void print();
	// Prints Menu then obtains and returns user input
	Menu::choice printAndGetInput();
	// Overloaded stream extraction operator for easier printing of menu text
	friend std::ostream& operator<< (std::ostream& os, const Menu& obj);
	// Overloaded stream insertion operator for easy changing of user input
	friend std::istream& operator>> (std::istream& is, Menu& obj);
private:
	std::unique_ptr<std::string> m_menu_text_;
	Menu::choice m_user_choice_;
};

#endif // MENU_H_
