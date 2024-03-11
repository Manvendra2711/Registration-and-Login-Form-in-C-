#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class temp
{
    string userName, Email, password;           // Data members to hold user information
    string searchName, searchPass, searchEmail; // Variables used for searching
    fstream file;                               // File stream object for file operations

public:
    void login();         // Method for user login
    void signUP();        // Method for user sign-up
    void forgot();        // Method for password recovery
    void deleteAccount(); // Method for deleting user account
    void resetPassword(); // Method for resetting user password
    void updateDetails(); // Method for updating user details
} obj;

int main()
{
    char choice;
    // Displaying menu options
    cout << "\n1- Login";
    cout << "\n2- Sign-Up";
    cout << "\n3- Forgot Password";
    cout << "\n4- Delete Account";
    cout << "\n5- Reset Password";
    cout << "\n6- Exit";
    cout << "\nEnter Your Choice :: ";
    cin >> choice;

    // Menu choice selection
    switch (choice)
    {
    case '1':
        cin.ignore();
        obj.login();
        break;
    case '2':
        cin.ignore();
        obj.signUP();
        break;
    case '3':
        cin.ignore();
        obj.forgot();
        break;
    case '4':
        cin.ignore();
        obj.deleteAccount();
        break;
    case '5':
        cin.ignore();
        obj.resetPassword();
        break;
    case '6':
        return 0; // Exit the program
    default:
        cout << "Invalid Selection...!";
    }
}

// Method to handle user sign-up
void temp::signUP()
{
    cout << "\nEnter Your User Name :: ";
    getline(cin, userName);
    cout << "Enter Your Email Address :: ";
    getline(cin, Email);
    cout << "Enter Your Password :: ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);             // Opening file in append mode
    file << userName << "*" << Email << "*" << password << endl; // Writing user data to file
    file.close();
}

// Method to handle user login
void temp::login()
{
    cout << "----------LOGIN---------" << endl;
    cout << "Enter Your User Name :: " << endl;
    getline(cin, searchName);
    cout << "Enter Your Password :: " << endl;
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in); // Opening file in read mode
    getline(file, userName, '*');
    getline(file, Email, '*');
    getline(file, password, '\n');
    while (!file.eof())
    {
        if (userName == searchName && password == searchPass)
        {
            // Login successful
            cout << "\nHello! " << userName << " Account Login Successful...!" << endl;
            cout << "\nUsername :: " << userName << endl;
            cout << "\nEmail :: " << Email << endl;
            file.close();
            updateDetails(); // Updating user details
            return;
        }
        getline(file, userName, '*');
        getline(file, Email, '*');
        getline(file, password, '\n');
    }
    file.close();
    cout << "Invalid username or password." << endl;
}

// Method to update user details
void temp::updateDetails()
{
    char choice;
    cout << "\nDo you want to update your email address? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "Enter new Email Address: ";
        cin.ignore();
        getline(cin, Email);
    }

    cout << "\nDo you want to update your password? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "Enter new Password: ";
        cin.ignore();
        getline(cin, password);
    }

    string tempFileName = "tempData.txt";
    string line;

    file.open("loginData.txt", ios::in);
    ofstream tempFile(tempFileName);

    while (getline(file, line))
    {
        string usernameFromFile = line.substr(0, line.find('*'));

        if (usernameFromFile == userName)
        {
            tempFile << userName << "*" << Email << "*" << password << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    remove("loginData.txt");
    rename(tempFileName.c_str(), "loginData.txt");
    cout << "Details updated successfully!" << endl;
}

// Method to handle password recovery
void temp::forgot()
{
    cout << "\nEnter Your UserName :: ";
    getline(cin, searchName);
    cout << "\nEnter Your Email Address :: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    getline(file, userName, '*');
    getline(file, Email, '*');
    getline(file, password, '\n');
    while (!file.eof())
    {
        if (userName == searchName)
        {
            if (Email == searchEmail)
            {
                cout << "\nAccount Found...!" << endl;
                cout << "Your Password :: " << password << endl;
            }
            else
            {
                cout << "Not found...!\n";
            }
        }
        else
        {
            cout << "\nNot found...!\n";
        }
        getline(file, userName, '*');
        getline(file, Email, '*');
        getline(file, password, '\n');
    }
    file.close();
}

// Method to delete user account
void temp::deleteAccount()
{
    string tempFileName = "tempData.txt";
    string line;
    bool deleted = false;

    cout << "Enter Your User Name to Delete Account :: ";
    cin >> searchName;

    file.open("loginData.txt", ios::in);
    ofstream tempFile(tempFileName);

    while (getline(file, line))
    {
        string usernameFromFile = line.substr(0, line.find('*'));

        if (usernameFromFile != searchName)
        {
            tempFile << line << endl;
        }
        else
        {
            deleted = true;
        }
    }

    file.close();
    tempFile.close();

    if (deleted)
    {
        remove("loginData.txt");
        rename(tempFileName.c_str(), "loginData.txt");
        cout << "Account Deleted Successfully!" << endl;
    }
    else
    {
        cout << "Account not found!" << endl;
        remove(tempFileName.c_str());
    }
}

// Method to reset user password
void temp::resetPassword()
{
    string newPass;
    string tempFileName = "tempData.txt";
    string line;
    bool updated = false;

    cout << "Enter Your User Name to Reset Password :: ";
    cin >> searchName;

    cout << "Enter New Password :: ";
    cin.ignore();
    getline(cin, newPass);

    file.open("loginData.txt", ios::in);
    ofstream tempFile(tempFileName);

    while (getline(file, line))
    {
        string usernameFromFile = line.substr(0, line.find('*'));

        if (usernameFromFile == searchName)
        {
            updated = true;
            tempFile << usernameFromFile << "*" << line.substr(line.find('*') + 1, line.rfind('*') - line.find('*') - 1) << "*" << newPass << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    if (updated)
    {
        remove("loginData.txt");
        rename(tempFileName.c_str(), "loginData.txt");
        cout << "Password Reset Successfully!" << endl;
    }
    else
    {
        cout << "Account not found!" << endl;
        remove(tempFileName.c_str());
    }
}
