#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>

// Function to print the border for the CLI
void printBorder() {
    std::cout << "******************************\n";
    std::cout << "*   CLI Calculator v1.0     *\n";
    std::cout << "******************************\n";
}

// Function to log the calculation history to a file
void logHistory(const std::string& history) {
    std::ofstream historyFile;
    historyFile.open("history.txt", std::ios::app); // Open for appending
    if (historyFile.is_open()) {
        historyFile << history << std::endl;
        historyFile.close();
    } else {
        std::cerr << "Unable to open history file for writing.\n";
    }
}

// Function to perform the calculation
double calculate(double num1, double num2, char op, bool& success) {
    double result = 0;
    success = true;

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                std::cerr << "Error: Division by zero!\n";
                success = false;
            } else {
                result = num1 / num2;
            }
            break;
        default:
            std::cerr << "Error: Invalid operator!\n";
            success = false;
            break;
    }

    return result;
}

int main() {
    double num1, num2, result;
    char op;
    std::string expression;
    bool success;

    // Main loop for calculator
    while (true) {
        printBorder();

        std::cout << "Enter calculation (or type 'exit' to quit): ";
        std::getline(std::cin, expression);

        if (expression == "exit") {
            break;
        }

        // Parse the input expression
        std::stringstream ss(expression);
        ss >> num1 >> op >> num2;

        if (ss.fail()) {
            std::cerr << "Error: Invalid input format. Use 'number operator number'.\n";
            continue;
        }

        // Perform the calculation
        result = calculate(num1, num2, op, success);

        if (success) {
            std::cout << "Result: " << result << "\n";

            // Log the calculation history
            std::string history = std::to_string(num1) + " " + op + " " + std::to_string(num2) + " = " + std::to_string(result);
            logHistory(history);
        }
    }

    return 0;
}
