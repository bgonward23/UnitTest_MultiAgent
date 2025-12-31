#include "gtest/gtest.h"
#include "bank_account.h"
#include <stdexcept>

// Unit tests for the BankAccount class

// Test fixture for setting up BankAccount objects
class BankAccountTest : public ::testing::Test {
protected:
    BankAccount account1{"Alice", 1000.0};
    BankAccount account2{"Bob", 500.0};
};

// Test constructor initialization
TEST_F(BankAccountTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(account1.get_balance(), 1000.0);
    EXPECT_EQ(account2.get_balance(), 500.0);
}

// Test deposit function
TEST_F(BankAccountTest, DepositValidAmount) {
    account1.deposit(200.0);
    EXPECT_EQ(account1.get_balance(), 1200.0);
}

TEST_F(BankAccountTest, DepositSmallPositiveAmount) {
    account1.deposit(0.01);
    EXPECT_EQ(account1.get_balance(), 1000.01);
}

TEST_F(BankAccountTest, DepositZeroThrowsException) {
    EXPECT_THROW(account1.deposit(0.0), std::invalid_argument);
}

TEST_F(BankAccountTest, DepositNegativeThrowsException) {
    EXPECT_THROW(account1.deposit(-100.0), std::invalid_argument);
}

// Test withdraw function
TEST_F(BankAccountTest, WithdrawValidAmount) {
    account1.withdraw(300.0);
    EXPECT_EQ(account1.get_balance(), 700.0);
}

TEST_F(BankAccountTest, WithdrawSmallPositiveAmount) {
    account1.withdraw(0.01);
    EXPECT_EQ(account1.get_balance(), 999.99);
}

TEST_F(BankAccountTest, WithdrawMoreThanBalanceThrowsException) {
    EXPECT_THROW(account1.withdraw(1500.0), std::runtime_error);
}

TEST_F(BankAccountTest, WithdrawZeroThrowsException) {
    EXPECT_THROW(account1.withdraw(0.0), std::invalid_argument);
}

TEST_F(BankAccountTest, WithdrawNegativeThrowsException) {
    EXPECT_THROW(account1.withdraw(-50.0), std::invalid_argument);
}

// Test get_balance function
TEST_F(BankAccountTest, GetBalanceReturnsCorrectValue) {
    EXPECT_EQ(account1.get_balance(), 1000.0);
    EXPECT_EQ(account2.get_balance(), 500.0);
}

// Test transfer function
TEST_F(BankAccountTest, TransferValidAmount) {
    account1.transfer(200.0, account2);
    EXPECT_EQ(account1.get_balance(), 800.0);
    EXPECT_EQ(account2.get_balance(), 700.0);
}

TEST_F(BankAccountTest, TransferSmallPositiveAmount) {
    account1.transfer(0.01, account2);
    EXPECT_EQ(account1.get_balance(), 999.99);
    EXPECT_EQ(account2.get_balance(), 500.01);
}

TEST_F(BankAccountTest, TransferMoreThanBalanceThrowsException) {
    EXPECT_THROW(account1.transfer(1200.0, account2), std::runtime_error);
}

TEST_F(BankAccountTest, TransferToSameAccountThrowsException) {
    EXPECT_THROW(account1.transfer(100.0, account1), std::invalid_argument);
}

TEST_F(BankAccountTest, TransferZeroThrowsException) {
    EXPECT_THROW(account1.transfer(0.0, account2), std::invalid_argument);
}

TEST_F(BankAccountTest, TransferNegativeThrowsException) {
    EXPECT_THROW(account1.transfer(-100.0, account2), std::invalid_argument);
}

// Test floating-point precision during operations
TEST_F(BankAccountTest, FloatingPointPrecision) {
    account1.deposit(0.1);
    account1.deposit(0.2);
    EXPECT_DOUBLE_EQ(account1.get_balance(), 1000.3); // Ensure no precision loss
}
