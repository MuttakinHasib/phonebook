#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_CONTACTS = 100;

class Contact
{
public:
    string name;
    string phoneNumber;

    void display()
    {
        cout << "Name: " << name << "\nPhone Number: " << phoneNumber << endl;
    }
};

class PhoneBook
{
private:
    Contact contacts[MAX_CONTACTS];
    int contactCount = 0;

public:
    void addContact(const string &name, const string &phoneNumber)
    {
        if (contactCount < MAX_CONTACTS)
        {
            contacts[contactCount].name = name;
            contacts[contactCount].phoneNumber = phoneNumber;
            contactCount++;
            saveContactsToFile();
            cout << "Contact added successfully." << endl;
        }
        else
        {
            cout << "Phonebook is full. Cannot add more contacts." << endl;
        }
    }

    Contact *findContactByPhoneNumber(const string &phoneNumber)
    {
        for (int i = 0; i < contactCount; ++i)
        {
            if (contacts[i].phoneNumber == phoneNumber)
            {
                return &contacts[i];
            }
        }
        return nullptr;
    }

    void deleteContact(const string &phoneNumber)
    {
        for (int i = 0; i < contactCount; ++i)
        {
            if (contacts[i].phoneNumber == phoneNumber)
            {
                for (int j = i; j < contactCount - 1; ++j)
                {
                    contacts[j] = contacts[j + 1];
                }
                contactCount--;
                saveContactsToFile();
                cout << "Contact deleted successfully." << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void displayAllContacts()
    {
        for (int i = 0; i < contactCount; ++i)
        {
            contacts[i].display();
            cout << "--------------------------" << endl;
        }
    }

    void loadContactsFromFile()
    {
        ifstream file("contacts.txt");
        if (file.is_open())
        {
            while (!file.eof())
            {
                string name, phoneNumber;
                file >> name >> phoneNumber;
                if (!name.empty() && !phoneNumber.empty())
                {
                    addContact(name, phoneNumber);
                }
            }
            file.close();
        }
    }

    void saveContactsToFile()
    {
        ofstream file("contacts.txt");
        if (file.is_open())
        {
            for (int i = 0; i < contactCount; ++i)
            {
                file << contacts[i].name << " " << contacts[i].phoneNumber << endl;
            }
            file.close();
        }
    }
};

int main()
{
    PhoneBook phonebook;
    phonebook.loadContactsFromFile();

    while (true)
    {
        cout << "Phonebook Menu:\n"
             << "1. Add Contact\n"
             << "2. Find Contact by Phone Number\n"
             << "3. Delete Contact\n"
             << "4. Display All Contacts\n"
             << "5. Exit\n"
             << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, phoneNumber;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Phone Number: ";
            cin >> phoneNumber;
            phonebook.addContact(name, phoneNumber);
            break;
        }
        case 2:
        {
            string phoneNumber;
            cout << "Enter Phone Number: ";
            cin >> phoneNumber;
            Contact *contact = phonebook.findContactByPhoneNumber(phoneNumber);
            if (contact)
            {
                contact->display();
            }
            else
            {
                cout << "Contact not found." << endl;
            }
            break;
        }
        case 3:
        {
            string phoneNumber;
            cout << "Enter Phone Number: ";
            cin >> phoneNumber;
            phonebook.deleteContact(phoneNumber);
            break;
        }
        case 4:
            phonebook.displayAllContacts();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}