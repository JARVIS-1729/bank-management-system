#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BankAccount {
    int accountNumber;
    char name[100];
    float balance;
    struct BankAccount *next;
};

struct BankAccount *head = NULL;
int nextAccountNumber = 1000; // starting account number

void createAccount();
void displayAccounts();
void depositMoney();
void withdrawMoney();
void deleteAccount();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while(1) {
        printf("\n===== Bank Management System =====\n");
        printf("1. Create New Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Delete Account\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: deleteAccount(); break;
            case 6: 
                printf("Exiting... Thanks for using our system!\n");
                exit(0);
            default: 
                printf("Invalid choice. Try again.\n");
        }
    }
}

void createAccount() {
    struct BankAccount *newAccount = (struct BankAccount*)malloc(sizeof(struct BankAccount));
    newAccount->accountNumber = nextAccountNumber++;
    printf("Enter account holder name: ");
    getchar(); // clear input buffer
    fgets(newAccount->name, sizeof(newAccount->name), stdin);
    newAccount->name[strcspn(newAccount->name, "\n")] = 0; // remove newline
    printf("Enter initial deposit: ");
    scanf("%f", &newAccount->balance);
    newAccount->next = head;
    head = newAccount;
    printf("Account created successfully! Account Number: %d\n", newAccount->accountNumber);
}

void displayAccounts() {
    if (head == NULL) {
        printf("No accounts found.\n");
        return;
    }
    struct BankAccount *temp = head;
    while (temp != NULL) {
        printf("\nAccount Number: %d\n", temp->accountNumber);
        printf("Account Holder: %s\n", temp->name);
        printf("Balance: ₹ %.2f\n", temp->balance);
        temp = temp->next;
    }
}

void depositMoney() {
    int accNo;
    float amount;
    printf("Enter account number to deposit into: ");
    scanf("%d", &accNo);
    struct BankAccount *temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            temp->balance += amount;
            printf("Deposit successful! New balance: ₹%.2f\n", temp->balance);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found!\n");
}

void withdrawMoney() {
    int accNo;
    float amount;
    printf("Enter account number to withdraw from: ");
    scanf("%d", &accNo);
    struct BankAccount *temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > temp->balance) {
                printf("Insufficient balance!\n");
            } else {
                temp->balance -= amount;
                printf("Withdrawal successful! New balance: ₹%.2f\n", temp->balance);
            }
            return;
        }
        temp = temp->next;
    }
    printf("Account not found!\n");
}

void deleteAccount() {
    int accNo;
    printf("Enter account number to delete: ");
    scanf("%d", &accNo);
    struct BankAccount *temp = head, *prev = NULL;
    while (temp != NULL) {
        if (temp->accountNumber == accNo) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Account deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Account not found!\n");
}
