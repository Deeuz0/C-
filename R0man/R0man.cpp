#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>

using namespace std;

// Function to convert Roman numeral to Arabic numbber
double romanToInt(string roman) {
    double total = 0;
    double prevValue = 0;



    for (int i = roman.length() - 1; i >= 0; i--) {
        double value;
        char numeral = toupper(roman[i]);

        if (numeral == 'I') value = 1;
        else if (numeral == 'V') value = 5;
        else if (numeral == 'X') value = 10;
        else if (numeral == 'L') value = 50;
        else if (numeral == 'C') value = 100;
        else if (numeral == 'M') value = 1000;
        else if (numeral == 'S') value = 0.5;
        else if (numeral == '.') value = 1.0 / 12;
        else continue;  // Skip invalid characters

        if (value >= prevValue) {
            total += value;
        }
        else {
            total -= value;
        }
        prevValue = value;
    }
    return total;
}

// Function to convert Arabic number to Roman numeral
string intToRoman(double num) {
    string result = "";

    int integerPart = static_cast<int>(num);
    double fractionalPart = num - integerPart;

    // Convert inrteger part
    while (integerPart >= 1000) {
        result += "M";
        integerPart -= 1000;
    }
    if (integerPart >= 900) {
        result += "CM";
        integerPart -= 900;
    }
    if (integerPart >= 500) {
        result += "I)";
        integerPart -= 500;
    }
    if (integerPart >= 400) {
        result += "CD";
        integerPart -= 400;
    }
    while (integerPart >= 100) {
        result += "C";
        integerPart -= 100;
    }
    if (integerPart >= 90) {
        result += "XC";
        integerPart -= 90;
    }
    if (integerPart >= 50) {
        result += "L";
        integerPart -= 50;
    }
    if (integerPart >= 40) {
        result += "XL";
        integerPart -= 40;
    }
    while (integerPart >= 10) {
        result += "X";
        integerPart -= 10;
    }
    if (integerPart >= 9) {
        result += "IX";
        integerPart -= 9;
    }
    if (integerPart >= 5) {
        result += "V";
        integerPart -= 5;
    }
    if (integerPart >= 4) {
        result += "IV";
        integerPart -= 4;
    }
    while (integerPart >= 1) {
        result += "I";
        integerPart -= 1;
    }

    // Convert fractional part
    if (fractionalPart >= 0.5) {
        result += "S";
        fractionalPart -= 0.5;
    }
    while (fractionalPart >= 1.0 / 12) {
        result += ".";
        fractionalPart -= 1.0 / 12;
    }

    return result;
}

// Functio to check if the input is a Roman numeral
bool isRoman(string input) {
    for (int i = 0; i < input.length(); i++) {
        char c = toupper(input[i]);
        if (c != 'I' && c != 'V' && c != 'X' && c != 'L' &&
            c != 'C' && c != 'D' && c != 'M' && c != ')' &&
            c != 'S' && c != '.') {
            return false;
        }
    }
    return true;
}

// Function to convert numbers with vinculum notation
double vinculumToInt(string roman) {
    double total = 0;
    string temp = "";
    for (int i = 0; i < roman.length(); i++) {
        char c = roman[i];
        if (c == '-' || c == '_') {
            total += romanToInt(temp) * 1000;
            temp = "";
        }
        else {
            temp += c;
        }
    }
    total += romanToInt(temp);
    return total;
}

// Function to convert numbers to vinculum notationn
string intToVinculum(double num) {
    string result = "";
    int integerPart = static_cast<int>(num);
    double fractionalPart = num - integerPart;

    // vinculum notqtion
    if (integerPart >= 1000) {
        int thousands = integerPart / 1000;
        integerPart %= 1000;
        result += intToRoman(thousands) + "-";
    }

    // Convert remaining integer part
    result += intToRoman(integerPart);

    // Convert fractional part
    if (fractionalPart >= 0.5) {
        result += "S";
        fractionalPart -= 0.5;
    }
    while (fractionalPart >= 1.0 / 12) {
        result += ".";
        fractionalPart -= 1.0 / 12;
    }

    return result;
}

// Function to handle input without validation
double interpretInput(string input) {
    if (isRoman(input)) {
        if (input.find('-') != string::npos || input.find('_') != string::npos) {
            return vinculumToInt(input);
        }
        else {
            return romanToInt(input);
        }
    }
    else {
        return stod(input);
    }
}

int main() {
    string input;
    cout << "Enter a Roman or Arabic number: ";
    while (cin >> input) {
        if (input == "quit") {
            break;
        }

        if (isRoman(input)) {
            cout << "Converted to Arabic: " << interpretInput(input) << endl;
        }
        else {
            try {
                double num = stod(input);
                if (input.find('.') != string::npos) {
                    cout << "Converted to Roman: " << intToRoman(num) << endl;
                }
                else {
                    cout << "Converted to Roman: " << intToVinculum(num) << endl;
                }
            }
            catch (invalid_argument&) {
                cout << "" << endl;
            }
        }

        cout << "Enter a Roman or Arabic number: ";
    }
    return 0;
}
