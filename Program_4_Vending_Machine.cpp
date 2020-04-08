
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include "functions.h"
using namespace std;

vector<string> display{ "Funyuns", "Lays", "Sun Chips", "Doritos", "M&M's", "Skittles", "Hershey's", "Kit Kat", "Bubblegum" };
vector<int> item_stock{			 3,		3,			3,			3,		3,			3,			3,			3,			3 };
int snack_count = 27;

void display_stock() {
	int stock_num = 1;

	for (int i = 0; i < display.size(); ++i) {
		cout << "(" << stock_num << ")\t" << display[i] << " ----- " << item_stock.at(i) << " left" << endl;
		stock_num++;
	}
}

double get_price(int item) {
	// initialize prices, match item=price, return price

	double chips = 0.75;		// funyuns, lays, sun_chips, doritos
	double small_candy = 1.25;	// mnms, kitkat
	double big_candy = 1.50;	// skittles, hersheys
	double gum = 0.50;			// bubblegum

	if (item == 1 || item == 2 || item == 3 || item == 4) {
		return chips;
	}
	else if (item == 5 || item == 8) {
		return small_candy;
	}
	else if (item == 6 || item == 7) {
		return big_candy;
	}
	else if (item == 9) {
		return gum;
	}
}

void calculate_money(double price, int item) {
	try {
		float total_money = 0.0, user_money = 0.0;
		bool check = true;

		for (int i = 0; i < display.size(); ++i) {
			if (item - 1 == i) {
				cout << "\n\t" << display[i] << " --------- $" << price << endl;
			}
		}

		while (check) {
			cout << "\nHow much money do you have for this snack? >>> ";
			cin >> user_money;
			total_money += user_money;	// adds amount user inputed & adds to total sum of money

			if (cin.fail()) {
				cin.clear(); // user input cleared
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nBad Input. Try again.\n" << endl;
				continue;
			}

			if (user_money <= 0 && total_money < price) {
				cout << "\nYou ran out of money. Have a good day." << endl;
				exit(0);
			}
			else if (total_money < price) {
				cout << "\nOh no! You don't have enough money. You have put in $" << total_money << endl;
				continue;
			}
			else if (total_money >= price) {
				// they have enough money -> dispense item, display change
				decrement_item(item);
				cout << "\nYour item has been dispensed.\nYour change is $" << (total_money - price) << endl;
				check = false;
			}
		}
	}
	catch (runtime_error& excpt) {
		cout << excpt.what() << endl;
	}
}

void decrement_item(int stock_item) {
	for (int i = 0; i < item_stock.size(); ++i) {
		if (stock_item - 1 == i && item_stock[i] <= 0) {
			cout << "\nThis item is not available." << endl;
			break;
		}
		else if (stock_item - 1 == i) {
			item_stock[i] -= 1;
		}
	}
	snack_count--;
}

void menu() {
	bool check = true;
	int option = 0;
	double price = 0.0;

	cout << "Welcome to the SnackPack Vending Machine" << endl;
	while (check) {

		try {
			// ask user for item OR to quit
			cout << "\nPlease select an item:\n";
			display_stock();
			cout << "(10)\tQuit" << endl << "Selection >>> ";
			cin >> option;

			if (cin.fail()) {
				cin.clear(); // user input cleared
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nThat option is not available.\n" << endl;
				continue;
			}

			if (option <= 0) {
				cin.clear(); // user input cleared
				throw runtime_error("\nOption cannot be less than 1.\n");
			}
			else if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6 || option == 7 || option == 8 || option == 9) {
				if (item_stock[option - 1] <= 0) {
					cout << "\nThis item is not available." << endl;
				}
				else {
					calculate_money(get_price(option), option);
				}
			}
			else if (option == 10) {
				check = false;
			}

			if (snack_count == 0) {
				cout << "\nThere are no more items available. Have a good day." << endl;
				check = false;
			}
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
		}
	}
}

int main() {
	menu();
}
