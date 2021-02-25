/*
 * InterestMenu.h
 *
 *  Created on: Feb 4, 2021
 *      Author: Michael Jordan
 *
 *      This class gathers input and validates it for use in an instance of InterestReporter.
 */

#ifndef AIRGEADINVESTMENTAPP_INTERESTMENU_H_
#define AIRGEADINVESTMENTAPP_INTERESTMENU_H_

#include "InterestReporter.h"
#include <cstdlib>
#include <memory>
#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cctype>

class InterestMenu {
public:
	InterestMenu();
	void displayHeader(std::ostream& t_outputTarget);
	void displayMenu(std::ostream& t_outputTarget);
	void obtainInvestment(std::ostream& t_outputTarget, std::istream& t_inputTarget);
	void obtainDeposit(std::ostream& t_outputTarget, std::istream& t_inputTarget);
	void obtainInterest(std::ostream& t_outputTarget, std::istream& t_inputTarget);
	void obtainYears(std::ostream& t_outputTarget, std::istream& t_inputTarget);
	void displayYearlyDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget);
	void displayYearlyNoDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget);
	void waitForInput(std::ostream& t_outputTarget, std::istream& t_inputTarget);


private:
	const int m_DISPLAY_WIDTH = 40;
	const char m_FILL_CHAR = '*';
	std::unique_ptr<InterestReporter> m_reporter;
	void validateDouble(std::string& t_input, double t_defaultValue);
	void validateInteger(std::string& t_input, int t_defaultValue);
	void displayMonthlyDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget, int t_year);
	void displayMonthlyNoDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget, int t_year);
};

#endif /* AIRGEADINVESTMENTAPP_INTERESTMENU_H_ */
