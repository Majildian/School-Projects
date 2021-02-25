/*
 * main.cpp
 *
 *  Created on: Feb 4, 2021
 *      Author: Michael Jordan
 */

#include "InterestMenu.h"
#include <cstdlib>
#include <memory>
#include <iostream>
#include <string>

int main(){
	std::string input;
	auto menu = std::make_unique<InterestMenu>();
	while(input != "q" && input != "Q"){

		menu->displayHeader(std::cout);

		menu->obtainInvestment(std::cout, std::cin);
		menu->obtainDeposit(std::cout, std::cin);
		menu->obtainInterest(std::cout, std::cin);
		menu->obtainYears(std::cout, std::cin);

		menu->waitForInput(std::cout, std::cin);
		menu->displayHeader(std::cout);
		menu->displayMenu(std::cout);
		menu->waitForInput(std::cout, std::cin);

		menu->displayYearlyNoDepositReport(std::cout, std::cin);

		menu->displayYearlyDepositReport(std::cout, std::cin);

		std::cout << "Press q to exit the program, or any other key to continue." << std::endl;
		std::cout << "Enter zero on any values that you don't want to change." << std:: endl;

		std::cin >> input;
	}
}


