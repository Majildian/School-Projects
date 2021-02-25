/*
 * InterestCalculator.h
 *
 *  Created on: Feb 4, 2021
 *      Author: Michael Jordan
 */

#ifndef AIRGEADINVESTMENTAPP_INTERESTCALCULATOR_H_
#define AIRGEADINVESTMENTAPP_INTERESTCALCULATOR_H_

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <string>

class InterestCalculator {
public:
	//t_interestRate should be entered as a percentage.
	InterestCalculator(int t_numYears, double t_initInvest, double t_interestRate, double t_monthlyDeposit = 0);

	void calculateInterest();

	//These functions will return the balance or interest for a certain month.
	//Valid input is any int below the number of years * 12, and zero or higher.
	//Do not call these until after calculateInterest() has been called.
	double getBalanceNoDeposit(int t_month);
	double getBalanceDeposit(int t_month);
	double getInterestNoDeposit(int t_month);
	double getInterestDeposit(int t_month);

	double getInitInvest() const;
	void setInitInvest(double t_initInvest);
	double getInterestRate() const;
	void setInterestRate(double t_interestRate);
	double getMonthlyDeposit() const;
	void setMonthlyDeposit(double t_monthlyDeposit);
	int getNumYears() const;
	void setNumYears(int t_numYears);

private:
	bool m_calculated = false;
	int m_numYears;
	double m_initInvest;
	double m_interestRate;
	double m_monthlyDeposit;
	std::vector<double> m_balancesNoDeposit;
	std::vector<double> m_balancesWithDeposit;
	std::vector<double> m_interestNoDeposit;
	std::vector<double> m_interestWithDeposit;

	void m_validateMonth(int t_month);
	double m_calculateMonthlyInterest(double t_balance, double t_interest);

};

#endif /* AIRGEADINVESTMENTAPP_INTERESTCALCULATOR_H_ */
