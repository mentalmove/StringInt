/* 
 * File:   StringInt.cpp
 * Author: maltepagel
 */

#include "StringInt.h"

string StringInt::add_floating_point(string pseudonumber, int point_position) {

    int len = (int) pseudonumber.length();

    if (point_position <= len)
        pseudonumber.insert(len - point_position, ".");

    if (pseudonumber[0] == '.')
        pseudonumber.insert(0, "0");

    return pseudonumber;
}

string StringInt::convert_int(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

char* StringInt::to_char_pointer(string the_string) {
    return (char*) the_string.c_str();
}

string StringInt::trim_number(string string_to_trim) {

    int i;
    char c;
    string result = "";

    for (i = 0; i < string_to_trim.length(); i++) {
        if (string_to_trim[i] != '0') {
            result.append(string_to_trim, i, (string_to_trim.length() - i));
            break;
        }
    }
    if (result[0] == '.')
        result.insert(0, "0");

    if (strchr(result.c_str(), '.')) {
        i = (int) result.length() - 1;
        c = result[i];
        while (i > 0 && (result[i] == '0' || result[i] == '.')) {
            result[i--] = '\0';
        }
        result.resize(i + 1);
    }

    if (result.empty())
        result = "0";

    return result;
}

void StringInt::set_to_equal_length(string tmp_first, string tmp_second) {

    int i;
    int f_max = (int) tmp_first.length();
    int s_max = (int) tmp_second.length();
    int max = (f_max > s_max) ? f_max : s_max;

    first_neg = 0;
    second_neg = 0;

    first = string(max, '0');
    second = string(max, '0');

    for (i = 0; i < f_max; i++)
        if ((int) tmp_first[i] >= 48 && (int) tmp_first[i] <= 57)
            first[i + max - f_max] = tmp_first[i];
        else
            if (tmp_first[i] == '-')
            first_neg = 1;

    for (i = 0; i < s_max; i++)
        if ((int) tmp_second[i] >= 48 && (int) tmp_second[i] <= 57)
            second[i + max - s_max] = tmp_second[i];
        else
            if (tmp_second[i] == '-')
            second_neg = 1;
}

/*  */

string StringInt::plus(string tmp_first, string tmp_second) {

    int i, last_index, digit;
    string result;
    int overhead = 0;
    int negative = 0;

    set_to_equal_length(tmp_first, tmp_second);

    if (first_neg && second_neg)
        negative = 1;
    else
        if (!first_neg && second_neg)
        return minus(first, second, 0);
    else
        if (first_neg && !second_neg)
        return minus(second, first, 0);

    last_index = (int) first.length() - 1;
    result = string((last_index + 2), '0');
    for (i = last_index; i >= 0; i--) {
        digit = (int) first[i] - 48 + (int) second[i] - 48 + overhead;
        overhead = (digit > 9) ? 1 : 0;
        digit %= 10;
        result[i + 1] = digit + 48;
    }

    if (overhead)
        result[0] = '1';

    result = trim_number(result);

    if (negative) {
        string neg_result = "-";
        neg_result.append(result);
        return neg_result;
    }

    return result;
}

string StringInt::minus(string tmp_first, string tmp_second, int negative) {

    set_to_equal_length(tmp_first, tmp_second);

    if (second_neg)
        return plus(first, second);
    else
        if (first_neg) {
        string zero = "0";
        return minus(zero, plus(first, second), 0);
    }

    if (strcmp(to_char_pointer(first), to_char_pointer(second)) < 0)
        return minus(second, first, (1 - negative));

    int i, last_index, digit;
    string result;
    int overhead = 0;

    last_index = (int) first.length() - 1;
    result = string((last_index + 2), '0');
    for (i = last_index; i >= 0; i--) {
        digit = ((int) first[i] - 48) - ((int) second[i] - 48 + overhead);
        overhead = (digit < 0) ? 1 : 0;
        if (overhead)
            digit += 10;
        result[i + 1] = digit + 48;
    }
    result = trim_number(result);

    if (negative) {
        string neg_result = "-";
        neg_result.append(result);
        return neg_result;
    }

    return result;
}

string StringInt::multiplicate(string tmp_first, string tmp_second) {

    int i, j, k, digit, zeros;
    int overhead = 0;
    int negative = 0;
    string zero_string, digit_string;
    string result = "0";

    set_to_equal_length(tmp_first, tmp_second);

    if (first_neg != second_neg)
        negative = 1;

    string multiplicator = trim_number(first);
    string multiplicand = trim_number(second);

    for (i = ((int) multiplicand.length() - 1); i >= 0; i--) {
        for (j = ((int) multiplicator.length() - 1); j >= 0; j--) {
            zero_string = "";
            digit = ((int) multiplicand[i] - 48) * ((int) multiplicator[j] - 48) + overhead;
            overhead = (int) (digit / 10);
            if (j)
                digit %= 10;
            else
                overhead = 0;
            zeros = ((int) multiplicand.length() - 1 - i) + ((int) multiplicator.length() - 1 - j);
            for (k = 0; k < zeros; k++)
                zero_string.append("0");
            digit_string = convert_int(digit);
            digit_string.append(zero_string);
            result = plus(result, digit_string);
        }
    }

    if (negative) {
        string neg_result = "-";
        neg_result.append(result);
        return neg_result;
    }

    return result;
}

string StringInt::pre_divide(string tmp_first, string tmp_second, int precision_to_use) {

    int i;
    int negative = 0;

    set_to_equal_length(tmp_first, tmp_second);

    if (first_neg != second_neg)
        negative = 1;

    string dividend = trim_number(first);
    string divisor = trim_number(second);

    if (dividend == divisor)
        return post_divide("1", precision_to_use, negative);

    if (precision_to_use) {
        string decimal = "1";
        for (i = 0; i < precision_to_use; i++)
            decimal.append("0");
        dividend = multiplicate(dividend, decimal);
    }

    for (i = 0; i < 8; i++)
        mul_divisors[i] = "";

    return divide(dividend, divisor, "0", precision_to_use, negative);
}

string StringInt::divide(string dividend, string divisor, string result, int precision_to_use, int negative) {

    if (dividend.length() < divisor.length() || (dividend.length() == divisor.length() && strcmp(to_char_pointer(dividend), to_char_pointer(divisor)) < 0))
        return post_divide(result, precision_to_use, negative);

    int i, small_dividend, small_divisor, starting_point;
    int overhead = 0;
    string tmp_result, tmp_divisor;
    string zeros_to_add = "";


    string dividend_head(dividend, 0, divisor.length());
    if (strcmp(to_char_pointer(dividend_head), to_char_pointer(divisor)) < 0) {
        overhead = 1;
        dividend_head += dividend[divisor.length()];
    }

    small_divisor = (int) divisor[0] - 48;
    if (!overhead)
        small_dividend = (int) dividend[0] - 48;
    else
        small_dividend = (int) dividend[1] - 48 + (10 * ((int) dividend[0] - 48));

    for (i = overhead; i < (dividend.length() - divisor.length()); i++)
        zeros_to_add.append("0");

    starting_point = (int) (small_dividend / small_divisor);

    for (i = starting_point; i >= 2; i--) {
        if (mul_divisors[i - 2] == "")
            mul_divisors[i - 2] = multiplicate(divisor, convert_int(i));
        tmp_result = convert_int(i) + zeros_to_add;
        tmp_divisor = mul_divisors[i - 2] + zeros_to_add;

        if (tmp_divisor.length() <= dividend.length() && strcmp(to_char_pointer(tmp_divisor), to_char_pointer(dividend)) <= 0)
            break;
    }
    if (i < 2) {
        tmp_result = "1" + zeros_to_add;
        tmp_divisor = divisor + zeros_to_add;
    }

    return divide(minus(dividend, tmp_divisor, 0), divisor, plus(result, tmp_result), precision_to_use, negative);
}

string StringInt::post_divide(string result, int precision_to_use, int negative) {

    if (precision_to_use)
        result = add_floating_point(result, precision_to_use);

    result = trim_number(result);

    if (negative) {
        string neg_result = "-";
        neg_result.append(result);
        return neg_result;
    }

    return result;
}

/*  */


string StringInt::calculate(char* tmp_first, char* tmp_second, char operation) {

    first = "";
    second = "";
    first_neg = 0;
    second_neg = 0;

    switch (operation) {
        case '+':
            return plus(tmp_first, tmp_second);
            break;
        case '-':
            return minus(tmp_first, tmp_second, 0);
            break;
        case '*':
            return multiplicate(tmp_first, tmp_second);
            break;
        case '/':
            return pre_divide(tmp_first, tmp_second, precision);
            break;
    }

    return "???";
}

string StringInt::calculate(string tmp_first, string tmp_second, string operation) {

    first = "";
    second = "";
    first_neg = 0;
    second_neg = 0;

    char c = operation[0];

    switch (c) {
        case 'a':
            return plus(tmp_first, tmp_second);
            break;
        case 's':
            return minus(tmp_first, tmp_second, 0);
            break;
        case 'm':
            return multiplicate(tmp_first, tmp_second);
            break;
        case 'd':
            return pre_divide(tmp_first, tmp_second, precision);
            break;
    }

    return "0";
}

StringInt::StringInt() {
    precision = 2;
}
