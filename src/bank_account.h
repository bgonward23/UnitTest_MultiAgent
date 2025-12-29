#pragma once
#include <string>
#include <stdexcept>

class BankAccount {
public:
     BankAccount(const std::string& owner, double balance);

     void deposit(double amount);
     void withdraw(double amount);
     void transfer(double amount, BankAccount& target_account);
     double get_balance() const;

private:
     std::string owner;
     double balance;
};
