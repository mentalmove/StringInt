/* 
 * File:   StringInt.h
 * Author: maltepagel
 */

#ifndef STRINGINT_H
#define	STRINGINT_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class StringInt {
public:
    StringInt();

    int precision;

    string calculate(char*, char*, char operation);
    string calculate(string, string, string);
private:
    string plus(string, string);
    string minus(string, string, int);
    string multiplicate(string, string);
    string divide(string, string, string, int, int);
    string pre_divide(string, string, int);
    string post_divide(string, int, int);

    string first, second;
    string mul_divisors[8];
    int first_neg, second_neg;

    void set_to_equal_length(string, string);
    string trim_number(string);
    char* to_char_pointer(string);
    string convert_int(int);
    string add_floating_point(string, int);
};

#endif	/* STRINGINT_H */
