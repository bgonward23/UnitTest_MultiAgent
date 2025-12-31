#include "bank_account.h"
#include <gtest/gtest.h>

TEST(BankAccountTest, ConstructorInitialBalance) {
    BankAccount acc("Alice", 100.0);
    EXPECT_DOUBLE_EQ(acc.get_balance(), 100.0);
}

TEST(BankAccountTest, DepositPositiveIncreasesBalance) {
    BankAccount acc("Bob", 50.0);
    acc.deposit(25.5);
    EXPECT_DOUBLE_EQ(acc.get_balance(), 75.5);
}

TEST(BankAccountTest, DepositZeroOrNegativeThrows) {
    BankAccount acc("Carol", 10.0);
    EXPECT_THROW(acc.deposit(0.0), std::invalid_argument);
    EXPECT_THROW(acc.deposit(-5.0), std::invalid_argument);
}

TEST(BankAccountTest, WithdrawPositiveDecreasesBalance) {
    BankAccount acc("Dave", 80.0);
    acc.withdraw(30.0);
    EXPECT_DOUBLE_EQ(acc.get_balance(), 50.0);
}

TEST(BankAccountTest, WithdrawZeroOrNegativeThrows) {
    BankAccount acc("Eve", 40.0);
    EXPECT_THROW(acc.withdraw(0.0), std::invalid_argument);
    EXPECT_THROW(acc.withdraw(-1.0), std::invalid_argument);
}

TEST(BankAccountTest, WithdrawInsufficientFundsThrowsAndBalanceUnchanged) {
    BankAccount acc("Frank", 20.0);
    EXPECT_THROW(acc.withdraw(25.0), std::runtime_error);
    EXPECT_DOUBLE_EQ(acc.get_balance(), 20.0);
}

TEST(BankAccountTest, TransferMovesFundsBetweenAccounts) {
    BankAccount a("Gina", 100.0);
    BankAccount b("Hank", 30.0);
    a.transfer(40.0, b);
    EXPECT_DOUBLE_EQ(a.get_balance(), 60.0);
    EXPECT_DOUBLE_EQ(b.get_balance(), 70.0);
}

TEST(BankAccountTest, TransferInsufficientFundsThrowsAndBalancesUnchanged) {
    BankAccount a("Ivy", 15.0);
    BankAccount b("Jack", 5.0);
    EXPECT_THROW(a.transfer(20.0, b), std::runtime_error);
    EXPECT_DOUBLE_EQ(a.get_balance(), 15.0);
    EXPECT_DOUBLE_EQ(b.get_balance(), 5.0);
}

TEST(BankAccountTest, TransferToSelfThrowsAndBalanceUnchanged) {
    BankAccount a("Kurt", 60.0);
    EXPECT_THROW(a.transfer(10.0, a), std::invalid_argument);
    EXPECT_DOUBLE_EQ(a.get_balance(), 60.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
