/*
 * InterestReporter.h
 *
 *  Created on: Feb 4, 2021
 *      Author: Michael Jordan
 *
 *      This class extends InterestCalculator to allow for outputting formatted reports
 *      to a given ostream.
 */

#ifndef AIRGEADINVESTMENTAPP_INTERESTREPORTER_H_
#define AIRGEADINVESTMENTAPP_INTERESTREPORTER_H_

#include "InterestCalculator.h"
#include <cstdlib>
#include <ios>
#include <iostream>
#include <iomanip>
#include <string>


class InterestReporter : public InterestCalculator {
public:
	InterestReporter(int t_numYears, double t_initInvest, double t_interestRate, double t_monthlyDeposit = 0);

	void displayNoDepositsYearlyReport(std::ostream& t_outputTarget);
	void displayNoDepositsMonthlyReport(std::ostream& t_outputTarget, int t_year);
	void displayDepositsYearlyReport(std::ostream& t_outputTarget);
	void displayDepositsMonthlyReport(std::ostream& t_outputTarget, int t_year);


private:
	const int m_DISPLAY_WIDTH = 80;
	void m_displayFormattedNoDepositYear(std::ostream& t_outputTarget, int t_targetYear);
	void m_displayFormattedNoDepositMonth(std::ostream& t_outputTarget, int t_targetMonth);
	void m_displayFormattedDepositYear(std::ostream& t_outputTarget, int t_targetYear);
	void m_displayFormattedDepositMonth(std::ostream& t_outputTarget, int t_targetMonth);
	void m_displayHeader(std::ostream& t_outputTarget, std::string& t_leadingText, std::string& t_periodicText);
};

#endif /* AIRGEADINVESTMENTAPP_INTERESTREPORTER_H_ */
