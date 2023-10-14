#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Contact {
    long ph;
    string name, add, email, due, dtd; // dtd = Due Taking Date.
};

Contact list;

ofstream fp, ft;
ifstream fin;

int i, n, ch, l, found;
string query, name;

int main() {
    main:

    // ... code for displaying main menu, taking user's choice, and performing actions based on that choice ...

    system("cls"); /* ************Main menu ***********************  */
    cout << "\n\t **** Welcome to Customer Details Management System ****";
    cout << "\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List all Contacts\n\t\t[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[0] Exit\n\t\t=================\n\t\t";
    cout << "Enter the choice:";
    cin >> ch;

    switch (ch) {
        case 0:
            cout << "\n\n\t\tAre you sure you want to exit?";
            break;

        /* *********************Add new contacts************  */
        case 1:
            system("cls");
            fp.open("contact.dat", ios::app);

            for (;;) {
                cin.ignore();
                cout << "To exit enter blank space in the name input\nName (Use identical)\t:";
                getline(cin, list.name);

                if (list.name.empty())
                    break;

                cout << "Phone\t\t\t:";
                cin >> list.ph;

                cin.ignore();
                cout << "Address\t\t\t:";
                getline(cin, list.add);

                cout << "Email-Address\t\t:";
                getline(cin, list.email);

                cout << "Amount of due\t\t:";
                getline(cin, list.due);

                cout << "Due taking date\t\t:";
                getline(cin, list.dtd);

                cout << "\n";
                fp.write(reinterpret_cast<char*>(&list), sizeof(list));
            }

            fp.close();
            break;

        /* *********************list of contacts*************************  */
        case 2:
            system("cls");
            cout << "\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n\nName\t\tPhone No\t    Address\t\tE-mail ad.\n=================================================================\n\n";

            for (char c = 'a'; c <= 'z'; c++) {
                fin.open("contact.dat");
                found = 0;

                while (fin.read(reinterpret_cast<char*>(&list), sizeof(list))) {
                    if (tolower(list.name[0]) == c) {
                        cout << "\nName\t\t: " << list.name << "\nPhone\t\t: " << list.ph << "\nAddress\t\t: " << list.add << "\nEmail\t\t: " << list.email << "\nAmount of due\t: " << list.due << "\nDue taking date\t: " << list.dtd << "\n";
                        found++;
                    }
                }

                fin.close();

                if (found != 0) {
                    cout << "=========================================================== [" << char(toupper(c)) << "]-(" << found << ")\n\n";
                    cin.get();
                }
            }
            break;

        /* *******************search contacts**********************  */
        case 3:
            system("cls");

            do {
                found = 0;
                cout << "\n\n\t..::CONTACT SEARCH\n\t===========================\n\t..::Name of contact to search: ";
                cin.ignore();
                getline(cin, query);
                l = query.length();
                fin.open("contact.dat");
                system("cls");
                cout << "\n\n..::Search result for '" << query << "' \n===================================================\n";

                while (fin.read(reinterpret_cast<char*>(&list), sizeof(list))) {
                    if (list.name.find(query) != string::npos) {
                        cout << "\n..::Name\t\t: " << list.name << "\n..::Phone\t\t: " << list.ph << "\n..::Address\t\t: " << list.add << "\n..::Email\t\t: " << list.email << "\n..::Amount of due\t: " << list.due << "\n..::Due taking date\t: " << list.dtd << "\n";
                        found++;

                        if (found % 4 == 0) {
                            cout << "..::Press Enter to continue...";
                            cin.get();
                        }
                    }
                }

                if (found == 0)
                    cout << "\n..::No match found!";
                else
                    cout << "\n..::" << found << " match(s) found!";

                fin.close();
                cout << "\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t";
                cin >> ch;
            } while (ch == 1);

            break;

        /* *********************edit contacts************************/
        case 4:
            system("cls");
            fin.open("contact.dat");
            ft.open("temp.dat", ios::out);

            cin.ignore();
            cout << "..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:";
            getline(cin, name);

            while (fin.read(reinterpret_cast<char*>(&list), sizeof(list))) {
                if (name != list.name)
                    ft.write(reinterpret_cast<char*>(&list), sizeof(list));
            }

            cout << "\n\n..::Editing '" << name << "'\n\n";
            cout << "..::Name(Use identical)\t:";
            getline(cin, list.name);
            cout << "..::Phone\t\t:";
            cin >> list.ph;
            cin.ignore();
            cout << "..::Address\t\t:";
            getline(cin, list.add);
            cout << "..::Email-Address\t:";
            getline(cin, list.email);
            cout << "..::Amount of due\t:";
            getline(cin, list.due);
            cout << "..::Due taking date\t:";
            getline(cin, list.dtd);
            cout << "\n";

            ft.write(reinterpret_cast<char*>(&list), sizeof(list));
            fin.close();
            ft.close();
            remove("contact.dat");
            rename("temp.dat", "contact.dat");
            break;

        /* ********************delete contacts**********************/
        case 5:
            system("cls");
            cin.ignore();
            cout << "\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete:";
            getline(cin, name);

            fin.open("contact.dat");
            ft.open("temp.dat", ios::out);

            while (fin.read(reinterpret_cast<char*>(&list), sizeof(list))) {
                if (name != list.name)
                    ft.write(reinterpret_cast<char*>(&list), sizeof(list));
            }

            fin.close();
            ft.close();
            remove("contact.dat");
            rename("temp.dat", "contact.dat");
            break;

        default:
            cout << "Invalid choice";
            break;
    }

    cout << "\n\n\n..::Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n";
    cin >> ch;

    switch (ch) {
        case 1:
            goto main; // Jump back to the main label to display the main menu again
        case 0:
            break;  // Exit the program
        default:
            cout << "Invalid choice";
            break;
    }

    return 0;
}
