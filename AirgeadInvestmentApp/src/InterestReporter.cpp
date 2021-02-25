/*
 * InterestReporter.cpp
 *
 *  Created on: Feb 4, 2021
 *      Author: Michael Jordan
 */

#include "InterestReporter.h"

InterestReporter::InterestReporter(int t_numYears, double t_initInvest, double t_interestRate, double t_monthlyDeposit)
	: InterestCalculator(t_numYears, t_initInvest, t_interestRate, t_monthlyDeposit)  {
}

//Since most of the reports have the same format, this is a helper function to format them correctly given a couple parameters.
void InterestReporter::m_displayHeader(std::ostream& t_outputTarget, std::string& t_leadingText, std::string& t_periodicText){
	t_outputTarget << std::right;

	//The following line centers the text.
	t_outputTarget << std::setw(t_leadingText.size() + ( (m_DISPLAY_WIDTH - t_leadingText.size()) ) / 2) << t_leadingText << std::endl;

	t_outputTarget << std::setw(m_DISPLAY_WIDTH)   << std::setfill('=') << "" << std::endl;
	t_outputTarget << std::setw(m_DISPLAY_WIDTH/4) << std::left << std::setfill(' ') << t_periodicText;
	t_outputTarget << std::setw(m_DISPLAY_WIDTH/4) << std::right << t_periodicText + " End Balance";
	t_outputTarget << std::setw(m_DISPLAY_WIDTH/2) << t_periodicText + " End Earned Interest" << std::endl;
	t_outputTarget << std::setw(m_DISPLAY_WIDTH)   << std::setfill('-') << "" << std::endl;
}

//Displays the yearly report with no monthly deposits.
void InterestReporter::displayNoDepositsYearlyReport(std::ostream& t_outputTarget) {
	std::string leadingText = "Balance and Interest without Additional Monthly Deposits";
	std::string periodicText = "Year";

	m_displayHeader(t_outputTarget, leadingText, periodicText);

	for(int i = 1;i <= getNumYears();i++){
		m_displayFormattedNoDepositYear(t_outputTarget, i);
		t_outputTarget << std::endl;
	}
}

//Displays the monthly report for a single year with no monthly deposits.
void InterestReporter::displayNoDepositsMonthlyReport(std::ostream& t_outputTarget, int t_year){
	std::string leadingText = "Balance and Interest without Additional Monthly Deposits";
	std::string periodicText = "Month";

	//Ensure that we are checking for a month that exists.
	getBalanceNoDeposit((t_year - 1) * 12 + 1);

	m_displayHeader(t_outputTarget, leadingText, periodicText);

	for(int i = (t_year - 1) * 12 + 1 ;i <= t_year*12;i++){
		m_displayFormattedNoDepositMonth(t_outputTarget, i);
		t_outputTarget << std::endl;
	}
}

//Displays the yearly report with monthly deposits.
void InterestReporter::displayDepositsYearlyReport(std::ostream& t_outputTarget){
	std::string leadingText = "Balance and Interest with Additional Monthly Deposits";
	std::string periodicText = "Year";

	m_displayHeader(t_outputTarget, leadingText, periodicText);

	for(int i = 1;i <= getNumYears();i++){
		m_displayFormattedDepositYear(t_outputTarget, i);
		t_outputTarget << std::endl;
	}
}

//Displays the monthly report for a single year with monthly deposits.
void InterestReporter::displayDepositsMonthlyReport(std::ostream& t_outputTarget, int t_year){
	std::string leadingText = "Balance and Interest with Additional Monthly Deposits";
	std::string periodicText = "Month";

	//Ensure that we are checking for a month that exists.
	getBalanceDeposit((t_year - 1) * 12 + 1);

	m_displayHeader(t_outputTarget, leadingText, periodicText);

	for(int i = (t_year - 1) * 12 + 1 ;i <= t_year*12;i++){
		m_displayFormattedDepositMonth(t_outputTarget, i);
		t_outputTarget << std::endl;
	}
}

//Helper function to sum up the interest in a year with no deposits, then format and display it along with the balance.
void InterestReporter::m_displayFormattedNoDepositYear(std::ostream& t_outputTarget, int t_targetYear){
	t_outputTarget << std::fixed << std::setprecision(2);

	double yearlyInterest = 0;

	for(int i = (t_targetYear - 1) * 12; i < (t_targetYear) * 12; i++){
		yearlyInterest += getInterestNoDeposit(i);

		//Use this conditional instead of i % 12 to avoid exiting loop immediately
		if( (i + 1) == t_targetYear*12) {
			t_outputTarget << std::setw(m_DISPLAY_WIDTH/3) << std::left << std::setfill(' ') << t_targetYear;
			t_outputTarget << "$" << std::setw(m_DISPLAY_WIDTH/5*2) << getBalanceNoDeposit(t_targetYear*12-1);
			t_outputTarget << "$" << yearlyInterest << std::endl;
		}
	}
}

//Helper function to format and display the interest and balance for a single month of a year with no deposits.
void InterestReporter::m_displayFormattedNoDepositMonth(std::ostream& t_outputTarget, int t_targetMonth){
	t_outputTarget << std::fixed << std::setprecision(2);

	t_outputTarget << std::setw(m_DISPLAY_WIDTH/3) << std::left << std::setfill(' ') << t_targetMonth;
	t_outputTarget << "$" << std::setw(m_DISPLAY_WIDTH/5*2) << getBalanceNoDeposit(t_targetMonth-1);
	t_outputTarget << "$" << getInterestNoDeposit(t_targetMonth-1) << std::endl;
}

//Helper function to sum up the interest in a year with deposits, then format and display it along with the balance.
void InterestReporter::m_displayFormattedDepositYear(std::ostream& t_outputTarget, int t_targetYear){
	t_outputTarget << std::fixed << std::setprecision(2);

	double yearlyInterest = 0;

	for(int i = (t_targetYear - 1) * 12; i < (t_targetYear) * 12; i++){
		yearlyInterest += getInterestDeposit(i);

		//Use this conditional instead of i % 12 to avoid exiting loop immediately
		if( (i + 1) == t_targetYear*12) {
			t_outputTarget << std::setw(m_DISPLAY_WIDTH/3) << std::left << std::setfill(' ') << t_targetYear;
			t_outputTarget << "$" << std::setw(m_DISPLAY_WIDTH/5*2) << getBalanceDeposit(t_targetYear*12-1);
			t_outputTarget << "$" << yearlyInterest << std::endl;
		}
	}
}

//Helper function to format and display the interest and balance for a single month of a year with deposits.
void InterestReporter::m_displayFormattedDepositMonth(std::ostream& t_outputTarget, int t_targetMonth){
	t_outputTarget << std::fixed << std::setprecision(2);

	t_outputTarget << std::setw(m_DISPLAY_WIDTH/3) << std::left << std::setfill(' ') << t_targetMonth;
	t_outputTarget << "$" << std::setw(m_DISPLAY_WIDTH/5*2) << getBalanceDeposit(t_targetMonth-1);
	t_outputTarget << "$" << getInterestDeposit(t_targetMonth-1) << std::endl;
}
