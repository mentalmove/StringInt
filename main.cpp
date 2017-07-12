/* 
 * File:   main.cpp
 * Author: maltepagel
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

#include "StringInt.h"


string int_to_string(int);

string int_to_string(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

int main (int argc, const char * argv[]) {

    char c = '?';

    string welcome = "\t 1 - Faculties\n\t 2 - Squareroot of 2\n\t 3 - Collatz\n\t q - Quit\n";

    cout << welcome;

    while (c != '1' && c != '2' && c != '3' && c != 'q' && c != 'Q') {
        scanf("%s", &c);
        if (c != '1' && c != '2' && c != '3' && c != 'q' && c != 'Q')
            cout << "Once again!" << endl << welcome;
    }

    if (c == '1' || c == '2' || c == '3') {
        StringInt *s_int = new StringInt();

        int i;
        int limit = 50;

        string result = "1";
        string pow;

        int choice = (int) c - 48;

        switch (choice) {
            case 1:
                for (i = 1; i <= limit; i++) {
                    result = s_int->calculate(result, int_to_string(i), "mul");
                    cout << i << "!\t=  " << result << endl;
                }
                break;
            case 2:
                cout << "\tSQRT(2) ≈ 1.";
                for (i = 1; i <= limit; i++) {
                    result = s_int->calculate(result, "10", "mul");
                    result = s_int->calculate(result, "9", "add");
                    while (1) {
                        pow = s_int->calculate(result, result, "mul");
                        if (pow[0] == '1')
                            break;
                        result = s_int->calculate(result, "1", "sub");
                    }
                    cout << result[result.length() - 1];
                }
                break;
            case 3:
                cout << endl << "If x is even: x = x / 2" << endl;
                cout << "If x is odd: x = 3 * x + 1" << endl;

                result = "2602714556700227743";
                string original_result = result;
                int is_below_origin = 0;
                int last_digit;
                i = 0;
                s_int->precision = 0;

                cout << "Every number is possible, but " << result << " gives spectacular results" << endl << endl;
                while (result != "1") {
                    if (!is_below_origin && result.length() <= original_result.length())
                        if (strcmp((char*) result.c_str(), (char*) original_result.c_str()) < 0) {
                            is_below_origin = 1;
                            cout << "\n\tCannot rise anymore!\n" << endl;
                        }

                    if (is_below_origin)
                        cout << "  ";

                    last_digit = (int) result[result.length() - 1];
                    printf("Step %4d:\t", ++i);
                    if (last_digit % 2 == 0) {
                        cout << "(/ 2)\t\t= ";
                        result = s_int->calculate(result, "2", "div");
                    } else {
                        cout << "(* 3 + 1)\t= ";
                        result = s_int->calculate(result, "3", "mul");
                        result = s_int->calculate(result, "1", "add");
                    }
                    cout << result << endl;
                }
        }
    }

    cout << endl << endl << "Goodbye" << endl << endl;

    return 0;
}

