#include <iostream>
#include <vector>
#include <cstring>
using namespace std;



class Bank {
    char name[200], address[200], accountType;
    float balance;
    int accountNumber;
    static int totalAccounts;
    static vector<Bank> accounts;



public:

    Bank();
    void createAccount();
    void depositMoney();
    void withdrawMoney();
    void viewAccount() const;
    static void displayMenu();
    static bool isValidAccountType(char type);
    static void displayAllAccounts();
    static int getTotalAccounts();
    void closeAccount();
    void transferMoney(Bank& otherAccount);
    static Bank* findAccount(const char* accountName);
    void calculateInterest();
    void viewTransactionHistory() const;
    void setBalanceLimit(float limit);
};


int Bank::totalAccounts = 0;
vector<Bank> Bank::accounts;

Bank::Bank() {
    balance = 0;
    accountNumber = totalAccounts + 1;
}

void Bank::createAccount() {
    cin.ignore();
    cout << "Please enter your name: ";
    cin.getline(name, 200);
    cout << "Please enter your full address: ";
    cin.getline(address, 200);

    do {
        cout << "What kind of account do you want to open? (S for Savings, C for Checking): ";
        cin >> accountType;
    } while (!isValidAccountType(accountType));

    cout << "Enter the initial deposit amount: ";
    cin >> balance;
    totalAccounts++;

    accounts.push_back(*this);
    cout << "Your account is created successfully. Account Number: " << accountNumber << endl;
}

void Bank::depositMoney() {
    float amount;
    cout << "How much do you want to deposit: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid deposit amount. Please enter a positive value." << endl;
    } else {
        balance += amount;
        cout << "Total amount after deposit: " << balance << endl;
    }
}



void Bank::viewAccount() const {
    cout << "-------------------------------------------" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Type of account: " << (accountType == 'S' || accountType == 's' ? "Savings" : "Checking") << endl;
    cout << "Balance: " << balance << endl;
    cout << "-------------------------------------------" << endl;
}



void Bank::withdrawMoney() {
    float amount;
    cout << "Enter the amount you want to withdraw: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid withdrawal amount. Please enter a positive value." << endl;
    } else if (amount > balance) {
        cout << "Insufficient balance. Cannot withdraw." << endl;
    } else {
        balance -= amount;
        cout << "Amount withdrawn. Remaining balance: " << balance << endl;
    }
}



void Bank::displayMenu() {
    cout << "\n1-Create an account" << endl;
    cout << "2-Deposit money" << endl;
    cout << "3-Withdraw money" << endl;
    cout << "4-View account" << endl;
    cout << "5-Display all accounts" << endl;
    cout << "6-Close an account" << endl;
    cout << "7-Transfer money between accounts" << endl;
    cout << "8-Calculate interest for savings accounts" << endl;
    cout << "9-Search for an account by name" << endl;
    cout << "10-View transaction history" << endl;
    cout << "11-Set balance limit" << endl;
    cout << "12-Exit" << endl;
    cout << "Select the option: "<<endl;
}

bool Bank::isValidAccountType(char type) {
    return (type == 'S' || type == 's' || type == 'C' || type == 'c');
}


void Bank::displayAllAccounts() {
    if (totalAccounts == 0) {
        cout << "No accounts created yet." << endl;
        return;
    }

    cout << "-------------------------------------------" << endl;
    cout << "List of all accounts:" << endl;
    for (const auto& account : accounts) {
        account.viewAccount();
    }
    cout << "-------------------------------------------" << endl;
}

int Bank::getTotalAccounts() {
    return totalAccounts;
}

void Bank::closeAccount() {
    if (balance == 0) {
        name[0] = '\0';
        address[0] = '\0';
        accountType = '\0';
        totalAccounts--;
        cout << "Account closed successfully." << endl;
    } else {
        cout << "Cannot close account. Withdraw all money before closing." << endl;
    }
}

void Bank::transferMoney(Bank& otherAccount) {
    float amount;
    cout << "Enter the amount you want to transfer: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid transfer amount. Please enter a positive value." << endl;
    } else if (amount > balance) {
        cout << "Insufficient balance. Cannot transfer." << endl;
    } else {
        balance -= amount;
        otherAccount.balance += amount;
        cout << "Amount transferred successfully." << endl;
    }
}


Bank* Bank::findAccount(const char* accountName) {
    for (auto& account : accounts) {
        if (strcmp(account.name, accountName) == 0) {
            return &account;
        }
    }
    return nullptr;
}

void Bank::calculateInterest() {
    if (accountType == 'S' || accountType == 's') {
        float interestRate = 0.05;
        float interest = balance * interestRate;
        balance += interest;
        cout << "Interest calculated. Current balance after interest: " << balance << endl;
    } else {
        cout << "Interest calculation is only applicable for savings accounts." << endl;
    }
}

void Bank::viewTransactionHistory() const {
    cout << "Transaction history is not available in this version." << endl;
}

void Bank::setBalanceLimit(float limit) {
    cout << "Setting balance limit is not available in this version." << endl;
}

int main() {
    int choice;
    Bank obj, obj2;
    do {
        Bank::displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                obj.createAccount();
                break;
            case 2:
                obj.depositMoney();
                break;
            case 3:
                obj.withdrawMoney();
                break;
            case 4:
                obj.viewAccount();
                break;
            case 5:
                Bank::displayAllAccounts();
                break;
            case 6:
                obj.closeAccount();
                break;
            case 7:
                obj.transferMoney(obj2);
                break;
            case 8:
                obj.calculateInterest();
                break;
            case 9: {
                cin.ignore();
                char accountName[200];
                cout << "Enter the name of the account you want to search: ";
                cin.getline(accountName, 200);
                Bank* foundAccount = Bank::findAccount(accountName);
                if (foundAccount != nullptr) {
                    foundAccount->viewAccount();
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 10:
                obj.viewTransactionHistory();
                break;
            case 11:
                obj.setBalanceLimit(10000);
                break;
            case 12:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    } while (true);

    return 0;
}
