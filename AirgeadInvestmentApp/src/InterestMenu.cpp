/*
 * InterestMenu.cpp
 *
 *  Created on: Feb 4, 2021
 *      Author: Michael Jordan
 */

#include "InterestMenu.h"

InterestMenu::InterestMenu() {
	m_reporter = std::make_unique<InterestReporter>(0, 0, 0, 0);
}

//Displays a header for the input menu. Can be adjusted with the members m_DISPLAY_WIDTH and m_FILL_CHAR.
void InterestMenu::displayHeader(std::ostream& t_outputTarget){
	std::string leadingText = " Data Input ";
	int paddingSize = leadingText.size() + ( (m_DISPLAY_WIDTH - leadingText.size() ) / 2);
	t_outputTarget << std::right;
	t_outputTarget << std::setw(m_DISPLAY_WIDTH) << std::setfill(m_FILL_CHAR) << "" << std::endl;
	t_outputTarget << std::setw(paddingSize) << leadingText << std::setw(paddingSize - leadingText.size()) << "" << std::endl;
}

//Ensures the output stream is correctly formatted and displays the current values set by the user.
//Must be called before displaying any reports in order to calculate the interest.
void InterestMenu::displayMenu(std::ostream& t_outputTarget){
	t_outputTarget << std::fixed << std::setprecision(2);
	t_outputTarget << "Initial Investment Amount:  $" << m_reporter->getInitInvest()     << 	   	 std::endl;
	t_outputTarget << "Monthly Deposit:  $"			  << m_reporter->getMonthlyDeposit() << 	 	 std::endl;
	t_outputTarget << "Annual Interest:  "			  << m_reporter->getInterestRate()   << "%"   << std::endl;
	t_outputTarget << "Number of years:  "			  << m_reporter->getNumYears() 	     << 		 std::endl;
	m_reporter->calculateInterest();
}

//Asks for input from the user until a positive real number is obtained.
//Zero is a valid input only if the underlying InterestReporter already has an initial investment.
void InterestMenu::obtainInvestment(std::ostream& t_outputTarget, std::istream& t_inputTarget){
	t_outputTarget << "Initial Investment Amount:  ";
	std::string input;

	while(true){
		try {
			t_inputTarget >> input;
			validateDouble(input, m_reporter->getInitInvest());
			break;
		}
		catch (std::invalid_argument& excpt){
			t_outputTarget << excpt.what() << std::endl;
			t_outputTarget << "Please enter a positive real number." << std::endl;
		}
	}

	//This allows for a default value of the previously entered initial investment.
	double initInvest = std::stod(input);
	if(initInvest > 0.00001){
		m_reporter->setInitInvest(initInvest);
	}
}

//Asks for input from the user until a positive real number is obtained.
//Zero is a valid input only if the underlying InterestReporter already has a monthly deposit.
//Although it's feasible that the user would enter no monthly deposit, this behavior can be
//obtained by displaying the report with no deposits factored in, therefore it is unnecessary
//to allow it as a valid input.
void InterestMenu::obtainDeposit(std::ostream& t_outputTarget, std::istream& t_inputTarget){
	t_outputTarget << "Monthly Deposit:  ";
	std::string input;

	while(true){
		try {
			t_inputTarget >> input;
			validateDouble(input, m_reporter->getMonthlyDeposit());
			break;
		}
		catch (std::invalid_argument& excpt){
			t_outputTarget << excpt.what() << std::endl;
			t_outputTarget << "Please enter a positive real number." << std::endl;
		}
	}

	//This allows for a default value of the previously entered interest rate.
	double monthlyDeposit = std::stod(input);
	if(monthlyDeposit > 0.00001){
		m_reporter->setMonthlyDeposit(monthlyDeposit);
	}
}

//Asks for input from the user until a positive real number is obtained.
//Zero is a valid input only if the underlying InterestReporter already has an interest rate.
void InterestMenu::obtainInterest(std::ostream& t_outputTarget, std::istream& t_inputTarget){
	t_outputTarget << "Annual Interest:  ";
	std::string input;

	while(true){
		try {
			t_inputTarget >> input;
			validateDouble(input, m_reporter->getInterestRate());
			break;
		}
		catch (std::invalid_argument& excpt){
			t_outputTarget << excpt.what() << std::endl;
			t_outputTarget << "Please enter a positive real number." << std::endl;
		}
	}

	//This allows for a default value of the previously entered interest rate.
	double interestRate = std::stod(input);
	if(interestRate > 0.00001){
		m_reporter->setInterestRate(interestRate);
	}
}

//Asks for input from the user until a positive integer is obtained.
//Zero is a valid input only if the underlying InterestReporter already has a number of years set.
void InterestMenu::obtainYears(std::ostream& t_outputTarget, std::istream& t_inputTarget){
	t_outputTarget << "Number of years:  ";
	std::string input;

	while(true){
		try {
			t_inputTarget >> input;
			validateInteger(input, m_reporter->getNumYears());
			break;
		}
		catch (std::invalid_argument& excpt){
			t_outputTarget << excpt.what() << std::endl;
			t_outputTarget << "Please enter a positive integer." << std::endl;
		}
	}

	//This allows for a default value of the previously entered number of years.
	int numYears = std::stoi(input);
	if(numYears > 0){
		m_reporter->setNumYears(numYears);
	}
}

//Displays the yearly report (with deposits factored in) and allows the user to view the monthly breakdown of each year.
void InterestMenu::displayYearlyDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget){
	m_reporter->displayDepositsYearlyReport(t_outputTarget);
	t_outputTarget << "Enter year number to see details or any letter to continue..." << std::endl;
	std::string input;
	while(input != "q"){
		try{
			t_inputTarget >> input;
			validateInteger(input, 0);
			displayMonthlyDepositReport(t_outputTarget, t_inputTarget, std::stoi(input));
		} catch(std::invalid_argument& excpt){
			//No message is necessary here, so we will silently exit the function.
			break;
		} catch(std::out_of_range& except) {
			//User probably entered a year higher than available, possibly by accident. Let them try again.
			t_outputTarget << "That year doesn't exist. Enter number to see details or any letter to continue...";
		}
	}
}

//Displays the yearly report (without deposits factored in) and allows the user to view the monthly breakdown of each year.
void InterestMenu::displayYearlyNoDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget){
	m_reporter->displayNoDepositsYearlyReport(t_outputTarget);
	t_outputTarget << "Enter year number to see details or any letter to continue..." << std::endl;
	std::string input;
	while(input != "q"){
		try{
			t_inputTarget >> input;
			validateInteger(input, 0);
			displayMonthlyNoDepositReport(t_outputTarget, t_inputTarget, std::stoi(input));
		} catch(std::invalid_argument& excpt){
			//No message is necessary here, so we will silently exit the function.
			break;
		} catch(std::out_of_range& except) {
			//User probably entered a year higher than available, possibly by accident. Let them try again.
			t_outputTarget << "That year doesn't exist. Enter number to see details or any letter to continue...";
		}
	}
}

//Displays a monthly report given a certain year, with monthly deposits factored in.
//Note that this function calls the reporter function to display the yearly report again, rather than calling the menu function.
//This is to avoid a loop that harms user experience and keep the menu function clean.
void InterestMenu::displayMonthlyDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget, int t_year){
	m_reporter->displayDepositsMonthlyReport(t_outputTarget, t_year);
	waitForInput(t_outputTarget, t_inputTarget);
	m_reporter->displayDepositsYearlyReport(t_outputTarget);
	t_outputTarget << "Enter year number to see details or any letter to continue..." << std::endl;
}

//Displays a monthly report given a certain year, without monthly deposits factored in.
//Note that this function calls the reporter function to display the yearly report again, rather than calling the menu function.
//This is to avoid a loop that harms user experience and keep the menu function clean.
void InterestMenu::displayMonthlyNoDepositReport(std::ostream& t_outputTarget, std::istream& t_inputTarget, int t_year){
	m_reporter->displayNoDepositsMonthlyReport(t_outputTarget, t_year);
	waitForInput(t_outputTarget, t_inputTarget);
	m_reporter->displayNoDepositsYearlyReport(t_outputTarget);
	t_outputTarget << "Enter year number to see details or any letter to continue..." << std::endl;
}

//Since we want specific input, these functions allow us to select only that input. Relying on the standard
//exceptions thrown by std::stod or std::stoi would require more error checking in the other functions.
void InterestMenu::validateDouble(std::string& t_input, double t_defaultValue){
	if(t_input.find('-') != std::string::npos){
		throw std::invalid_argument("Number seems to be negative.");
	}
	for (unsigned int i = 0; i < t_input.size(); i++) {
		if(!std::isdigit(t_input.at(i)) && t_input.at(i) != '.'){
			throw std::invalid_argument("Input is not a number.");
		}
	}

	if(std::stod(t_input) <= 0.00001 && t_defaultValue <= 0.00001){ //avoid floating point issues by checking for <= 0.00001 instead of == 0
		throw std::invalid_argument("Must enter a value higher than zero.");
	}
}

void InterestMenu::validateInteger(std::string& t_input, int t_defaultValue){
	if(t_input.find('-') != std::string::npos){
		throw std::invalid_argument("Number seems to be negative.");
	}
	else if(t_input.find('.') != std::string::npos){
		throw std::invalid_argument("Number is not an integer.");
	}
	for (unsigned int i = 0; i < t_input.size(); i++) {
		if(!std::isdigit(t_input.at(i)) && t_input.at(i) != '.'){
			throw std::invalid_argument("Input is not a number.");
		}
	}

	if(std::stoi(t_input) == 0 && t_defaultValue == 0){
		throw std::invalid_argument("Must enter a value higher than zero.");
	}
}

//Pauses program execution. Allows the user to read what has been displayed at their own pace, rather than overwhelming them.
void InterestMenu::waitForInput(std::ostream& t_outputTarget, std::istream& t_inputTarget){
	std::string placeholder;
	t_outputTarget << "Enter any key to continue..." << std::endl;
	//Looks awkward, but seems to be the best way to pause until the user inputs something.
	t_inputTarget >> placeholder;
}
