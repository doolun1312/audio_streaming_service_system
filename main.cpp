/*
main.cpp
Author: M00835210
Created: 06/04/2023
Updated: 16/04/2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include "maintracks.h"
#include "hashTable.h"

/*
    Main function to initialize the hash table and call the mainmenu function
    @param none
    @return none
*/
int main()
{
    hashTable hash(6007);
    mainmenu(hash);
}
