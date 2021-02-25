/*
 * InterestCalculator.cpp
 *
 *  Created on: Feb 4, 2021
 *      Author: Michael Jordan
 */

#include "InterestCalculator.h"

InterestCalculator::InterestCalculator(int t_numYears, double t_initInvest, double t_interestRate, double t_monthlyDeposit) {
	setNumYears(t_numYears);
	setInitInvest(t_initInvest);
	setInterestRate(t_interestRate);
	setMonthlyDeposit(t_monthlyDeposit);
}

double InterestCalculator::m_calculateMonthlyInterest(double t_balance, double t_interest){
	double monthlyInterest = (t_interest / 12.0) * t_balance;
	return monthlyInterest;
}

//Calculates interest for every month, and populates the vectors accordingly.
//Must be called before accessing any balance or interest numbers.
void InterestCalculator::calculateInterest() {
	const int TARGET_MONTH = m_numYears * 12;
	int currMonth = 1;
	double currBalanceNoDeposit;
	double currBalanceWithDeposit;


	//Make sure our vectors are the correct size to hold our calculations.
	m_balancesNoDeposit.resize(m_numYears * 12);
	m_balancesWithDeposit.resize(m_numYears * 12);
	m_interestNoDeposit.resize(m_numYears * 12);
	m_interestWithDeposit.resize(m_numYears * 12);

	//Set up the initial month, as doing so within the loop and avoiding vector access exceptions would be inefficient.
	currBalanceNoDeposit = m_initInvest;
	currBalanceWithDeposit = m_initInvest + m_monthlyDeposit;
	m_interestNoDeposit.at(0) = m_calculateMonthlyInterest(currBalanceNoDeposit, m_interestRate);
	m_balancesNoDeposit.at(0) = currBalanceNoDeposit + m_interestNoDeposit.at(0);
	m_interestWithDeposit.at(0) = m_calculateMonthlyInterest(currBalanceWithDeposit, m_interestRate);
	m_balancesWithDeposit.at(0) = currBalanceWithDeposit + m_interestWithDeposit.at(0);

	//Repeat the above process for each remaining month.
	while(currMonth < TARGET_MONTH){
		currBalanceNoDeposit = m_balancesNoDeposit.at(currMonth-1);
		currBalanceWithDeposit = m_balancesWithDeposit.at(currMonth-1) + m_monthlyDeposit;
		m_interestNoDeposit.at(currMonth) = m_calculateMonthlyInterest(currBalanceNoDeposit, m_interestRate);
		m_balancesNoDeposit.at(currMonth) = currBalanceNoDeposit + m_interestNoDeposit.at(currMonth);
		m_interestWithDeposit.at(currMonth) = m_calculateMonthlyInterest(currBalanceWithDeposit, m_interestRate);
		m_balancesWithDeposit.at(currMonth) = currBalanceWithDeposit + m_interestWithDeposit.at(currMonth);
		currMonth++;
	}

	m_calculated = true;
}



double InterestCalculator::getBalanceNoDeposit(int t_month){
	m_validateMonth(t_month);
	return m_balancesNoDeposit.at(t_month);
}

double InterestCalculator::getBalanceDeposit(int t_month){
	m_validateMonth(t_month);
	return m_balancesWithDeposit.at(t_month);
}

double InterestCalculator::getInterestNoDeposit(int t_month){
	m_validateMonth(t_month);
	return m_interestNoDeposit.at(t_month);
}

double InterestCalculator::getInterestDeposit(int t_month){
	m_validateMonth(t_month);
	return m_interestWithDeposit.at(t_month);
}

void InterestCalculator::m_validateMonth(int t_month){
	//The error messages here assume that the integer has been decreased by one, as it is likely to be
	//an integer entered by a user.
	if(!m_calculated){
		throw std::logic_error("Interest must be calculated first.");
	}
	else if (t_month < 0) {
		throw std::out_of_range("Month must be 1 or higher.");
	}
	else if (t_month >= m_numYears * 12){
		throw std::out_of_range("Month must be less than or equal to " + std::to_string(m_numYears * 12) + ".");
	}
}

double InterestCalculator::getInitInvest() const {
	return m_initInvest;
}
void InterestCalculator::setInitInvest(double t_initInvest) {
	m_initInvest = t_initInvest;
}

//Automatically convert interest rate from a percentage to a decimal, for easy calculations.
double InterestCalculator::getInterestRate() const {
	return m_interestRate * 100.0;
}
void InterestCalculator::setInterestRate(double t_interestRate) {
	m_interestRate = t_interestRate / 100.0;
}

double InterestCalculator::getMonthlyDeposit() const {
	return m_monthlyDeposit;
}
void InterestCalculator::setMonthlyDeposit(double t_monthlyDeposit) {
	m_monthlyDeposit = t_monthlyDeposit;
}

int InterestCalculator::getNumYears() const {
	return m_numYears;
}
void InterestCalculator::setNumYears(int t_numYears) {
	m_numYears = t_numYears;
}

