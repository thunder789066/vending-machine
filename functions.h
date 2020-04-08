#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;

void menu();

double get_price(int item);

void display_stock();

void decrement_item(int stock_item);

void calculate_money(double price, int item);
