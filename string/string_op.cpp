#include "../include/help.h"


int main()
{
    string str = "cat";
    cout << "apple" + "boy" + str; // illegal!
    cout << "apple" + str; // legal!
    return 0;
}