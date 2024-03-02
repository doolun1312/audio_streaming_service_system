#ifndef _MAINTRACKS_H_
#define _MAINTRACKS_H_
/*
maintracks.h
Author: M00835210
Created: 06/04/2023
Updated: 16\7/04/2023
*/

#include "tracks.h"
#include "hashTable.h"

bool menuverification(std::string x);
int mainmenu(hashTable& hash);
void read(hashTable& hash);
std::string add(std::string file, hashTable& hash);
std::string save(hashTable& hash);
std::string search(hashTable& hash);
std::string del(hashTable& hash);
bool fileselection(hashTable& hash);
bool fileverification(std::string file);
#endif