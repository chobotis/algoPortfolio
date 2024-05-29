
#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Bank {

    std::string name_;
    double amount_starting_;
    double amount_salary_;
    double amount_left_;

    Bank( const string & name="",
        const double & starting=0.0,
        const double & salary=0.0);
};
