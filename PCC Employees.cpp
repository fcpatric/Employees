#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "Employees.h"

int main()
{
    char input = '!';

    Employees e;
    int emID = 0;

    while(input != 'Q')
    {
        cout << "(I)nsert" << endl;
        cout << "(R)emove" << endl;
        cout << "(P)rint" << endl;
        cout << "(S)earch" << endl;
        cout << "(C)ount" << endl;
        cout << "(Q)uit" << endl;
        cout << endl;

        cout << "[IRPSCQ]> ";
        cin >> input;

        switch(input)
        {
            case 'I':
                {
                    string emName = "";

                    cout << "Enter the employee's ID to be inserted: ";
                    cin >> emID;

                    cin.ignore();
                    cout << "Enter the employee's name to be inserted: ";
                    getline(cin, emName);

                    e.insert(emID, emName);

                    break;
                }

            case 'R':
                {
                    cout << "Enter the employee's ID to be remove: ";
                    cin >> emID;

                    e.remove(emID);

                    break;
                }

            case 'P':
                {
                    e.print();
                    break;
                }

            case 'S':
                {
                    cout << "Enter the employee's ID to be searched: ";
                    cin >> emID;

                    if( e.search(emID) )
                        cout << "Employee is found.";
                    else
                        cout << "Employee is not found.";

                    cout << endl;

                    break;
                }

            case 'C':
                {
                    cout << "Employee count: " << e.count() << endl;
                    break;
                }

            case 'Q':
                {
                    cout << "Terminating the program..." << endl;
                    e.~Employees();
                    exit(0);

                    break;
                }

            default:
                {
                    cout << "Enter a valid character. Try again.";
                    break;
                }
        }

        cout << endl;
    }

    return 0;
}
