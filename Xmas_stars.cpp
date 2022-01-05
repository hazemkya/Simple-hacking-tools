#include <iostream>
using namespace std;

int main()
{
    int value;
    int select = 0;

    while (select != 2)
    {
        cout << "1- print stars\n";
        cout << "2- exit\n";
        cout << "enter the number: ";
        cin >> select;
        switch (select)
        {
        case 1:
            cout << "insert the number of stars: ";
            cin >> value;
            for (int i = 0; i < value; i++)
            {
                for (int k = i; k < value; k++)
                {
                    printf(" ");
                }
                for (int j = 0; j <= i * 2; j++)
                {

                    printf("*");
                }
                printf("\n");
            }
            break;
        case 2:
            return 0;

        default:
            cout << "Wrong number";
        }
    }

    return 0;
}