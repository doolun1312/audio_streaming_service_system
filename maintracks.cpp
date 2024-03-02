/*
maintracks.cpp
Author: M00835210
Created: 06/04/2023
Updated: 20/04/2023
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include "maintracks.h"
#include "hashTable.h"

/*
    Displays the elements in the hash table
    @param hash hash to read from and write to initialized when running the program
    @return the index, key and description for each pair of the hash table
*/
void read(hashTable &hash)
{
    Pair **table = hash.getTable();
    if (table != nullptr)
    {
        for (unsigned i = 0; i < hash.getSize(); i++)
        {
            if (table[i] != nullptr)
            {
                std::cout << "Index " << i << ": " << table[i]->key << " -> " << table[i]->value.description() << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Error: hash table is null." << std::endl;
    }
}

/*
    Add elements to the hash table
    @param file, hash file to read tracks from, hash to read from and write to initialized when running the program
    @return good
*/

std::string add(std::string file, hashTable &hash)
{
    int numLines = 0;
    std::ifstream tracksfile(file);
    std::string word;
    while (std::getline(tracksfile, word))
    {
        ++numLines;
    }
    int lines = hash.getSize() + numLines;
    hash.resize(lines);

    // read data from file and add to hash table
    std::ifstream infile(file);
    std::string line;
    int str;
    int start1;
    std::string duplicates =
        "\x1b[1m \x1b[4m\n\nThe following tracks were already present in the library, so they were not added again: \x1b[0m\n\n";
    bool duplicates1 = false;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string newTitle, newArtist;
        std::string duration1;
        int start = 0;
        int c = 0;
        /* Everytime a "	" is found, the count is incremented,
        when the count reaches a specific number it means that a specific attribute
        that is needed is stored so we use the word to display it*/
        for (int i = 0; i < 3; i++)
        {
            str = line.find("	", start);
            start1 = start;
            start = str + 1;
            c += 1;
            if (c == 1)
            {
                newTitle = line.substr(start1, str - start1);
            }
            if (c == 2)
            {
                newArtist = line.substr(start1, str - start1);
            }
            if (c == 3)
            {
                duration1 = line.substr(start1, str - start1);
            }
        }

        std::vector<Pair *> results1 = hash.findPair(newArtist, newTitle); // use the find function that returns a vector

        if (results1.empty())
        {
            hash.add(newArtist, Track(newTitle, newArtist, std::stoi(duration1)));
        }
        else
        {
            for (const auto &pair : results1)
            {
                //     if (pair->value.getTitle() == newTitle)
                //     {
                duplicates += ("\x1b[1mTITLE: \x1b[0m" + pair->value.getTitle() + "       \x1b[1mARTIST(S)/BAND: \x1b[0m" + pair->key +
                               "         \x1b[1mDURATION: \x1b[0m" + pair->value.getDuration() +
                               // std::cout << pair->key << ": " << pair->value.description() << std::endl;
                               "\n+----------------------------------+----------------------------------+---------------------+\n");
                duplicates1 = true;
            }
        }
    }

    if (duplicates1)
    {
        std::cout << duplicates;
        std::cout << "\n\n\n";
    }

    // print contents of hash table
    std::cout << "Hash table size: " << hash.getSize() << std::endl;
    std::cout << "Total items: " << hash.getTotal() << std::endl;
    mainmenu(hash);
    return "good";
}

/*
    Check if the file inputted exists
    @param file file to read from and check if it esxists
    @return true if file exists, false if it does not exist
*/
bool fileverification(std::string file)
{
    std::fstream tracks_file;
    tracks_file.open(file, std::ios::in);
    if (tracks_file)
    {
        std::cout << "File exists\n";
        return true;
    }
    else
    {
        std::cout << "\n\n\n"
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << std::setw(20) << std::setfill(' ') << ""
                  << "\x1b[1m \x1b[4mFILE NOT FOUND!\n\x1b[0m\x1b[3mPlease try again.\x1b[0m "
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << "\n\n\n"
                  << std::endl;

        return false;
    }
    return false;
}

/*
    Ask the user to choose a file to add tracks from
    @param hash hash to read from and write to initialized when running the program
    @return true
*/
bool fileselection(hashTable &hash)
{
    bool filev = false;
    std::string file;
    while (!filev)
    {
        std::cout << "Please enter a file to add tracks from to the library: ";
        std::cin >> file;
        filev = fileverification(file);
        if (filev)
        {
            add(file, hash);
        }
    }

    return true;
}

/*
    Save the library to a chosen file
    @param hash hash to read from and write to initialized when running the program
    @return 0
*/
std::string save(hashTable &hash)
{
    std::string file;
    std::cout << "Enter the name of the file where you want to save your library: ";
    std::cin >> file;
    std::ofstream outputfile(file);
    if (!outputfile.is_open())
    {
        std::cout << "\n\n\n"
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << std::setw(20) << std::setfill(' ') << ""
                  << "\x1b[1m \x1b[4mERROR!\n\x1b[0m        \x1b[3mCould not open file for writing.\x1b[0m "
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << "\n\n\n"
                  << std::endl;
        return 0;
    }

    // Get the table from the hash table
    Pair **table = hash.getTable();

    // Loop through the table and write each entry to the file
    for (unsigned i = 0; i < hash.getSize(); i++)
    {
        if (table[i] != nullptr)
        {
            outputfile << table[i]->value.descriptionsave() << std::endl;
        }
    }

    // Close the file
    outputfile.close();
    std::cout << "\n\n\n"
              << std::endl;
    std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
    std::cout << std::setw(20) << std::setfill(' ') << ""
              << "\x1b[1m \x1b[4mSuccessful!\n\x1b[0m        \x1b[3mLibrary successfully saved to " << file << "\x1b[0m "
              << std::endl;
    std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
    std::cout << "\n\n\n"
              << std::endl;
    mainmenu(hash);
    return 0;
}

/*
    Search for a track in the hash table
    @param hash hash to read from and write to initialized when running the program
    @return none
*/
std::string search(hashTable &hash)
{
    // search for tracks in the hash table
    std::string query;
    std::cout << "Enter an Artist/Band name to search for: ";
    std::cin.ignore();
    std::getline(std::cin, query);

    std::vector<Pair *> results = hash.find(query); // use the find function that returns a vector

    if (results.empty())
    {
        std::cout << "\n\n\n"
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << std::setw(20) << std::setfill(' ') << ""
                  << "\x1b[1m \x1b[4mNO TRACKS FOUND!\n\x1b[0m                    \x1b[3mPlease try again!\x1b[0m "
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << "\n\n\n"
                  << std::endl;
    }
    else
    {
        std::cout << "\x1b[1m \x1b[4m\n\nTracks found:\n\x1b[0m\n\n"
                  << std::endl;
        std::cout << "+----------------------------------+----------------------------------+---------------------+"
                  << std::endl;
        std::cout << "|               Title              |               Artist             |       Duration      |"
                  << std::endl;
        std::cout << "+----------------------------------+----------------------------------+---------------------+"
                  << std::endl;
        for (const auto &pair : results)
        {
            std::cout << "|" << std::setw(34) << std::left << pair->value.getTitle()
                      << "|" << std::setw(34) << std::left << pair->key << "|" << std::setw(21)
                      << std::left << pair->value.getDuration() << "|" << std::endl;
            std::cout << "+----------------------------------+----------------------------------+---------------------+" << std::endl;
        }
        std::cout << "\n\n\n";
    }

    mainmenu(hash);
    return 0;
}

/*
    Delete a chosen track
    @param hash hash to read from and write to initialized when running the program
    @return 0
*/
std::string del(hashTable &hash)
{

    // search for tracks in the hash table
    std::string query;
    std::string tracksearch;
    std::cout << "Enter an Artist/Band name to delete a song: ";
    std::cin.ignore();
    std::getline(std::cin, query);
    std::cout << "Enter the name of a track to delete: ";
    std::getline(std::cin, tracksearch);
    bool trackexist = false;
    int x;
    std::vector<Pair *> results = hash.findPair(query, tracksearch); // use the find function that returns a vector

    if (results.empty())
    {
        std::cout << "\n\n\n"
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << std::setw(20) << std::setfill(' ') << ""
                  << "\x1b[1m \x1b[4mNO TRACKS FOUND!\n\x1b[0m                    \x1b[3mPlease try again!\x1b[0m "
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << "\n\n\n"
                  << std::endl;
    }
    else
    {
        std::cout << "\n\n\n";
        std::cout << "\x1b[1m \x1b[4m\n\nTracks found:\n\x1b[0m\n\n"
                  << std::endl;
        std::cout << "+----------------------------------+----------------------------------+---------------------+"
                  << std::endl;
        std::cout << "|               Title              |               Artist             |       Duration      |"
                  << std::endl;
        std::cout << "+----------------------------------+----------------------------------+---------------------+"
                  << std::endl;
        for (const auto &pair : results)
        {
            std::cout << std::setw(36) << std::left << tracksearch
                      << std::setw(35) << std::left << query << std::setw(22)
                      << std::left << pair->value.getDuration() << std::endl;
            std::cout << "+----------------------------------+----------------------------------+---------------------+"
                      << std::endl;

            if (tracksearch != pair->value.getTitle())
            {
                trackexist = false;
            }
            else
            {
                trackexist = true;
            }
        }

        if (trackexist == true)
        {

            std::cout << "\nAre you sure you want to delete " << tracksearch
                      << "?\n1)Yes\n2)No\nChoose an option: "
                      << std::endl;
            std::cin >> x;
            if (x == 1)
            {
                hash.remove(hash.index(query, tracksearch));
                std::cout << "\n\n\n"
                          << std::endl;
                std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
                std::cout << std::setw(20) << std::setfill(' ') << ""
                          << "\x1b[1m \x1b[4mTRACK SUCCESSFULLY DELETED...\n\x1b[0m "
                          << std::endl;
                std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
                std::cout << "\n\n\n"
                          << std::endl;
                mainmenu(hash);
            }
            else if (x == 2)
            {
                std::cout << "\n\n\n"
                          << std::endl;
                std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
                std::cout << std::setw(20) << std::setfill(' ') << ""
                          << "\x1b[1m \x1b[4mCANCELLING DELETION...\n\x1b[0m "
                          << std::endl;
                std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
                std::cout << "\n\n\n"
                          << std::endl;
            }
            else
            {
                std::cout << "\n\n\n"
                          << std::endl;
                std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
                std::cout << std::setw(20) << std::setfill(' ') << ""
                          << "\x1b[1m \x1b[4mERROR!\n\x1b[0m        \x1b[3mPlease try again! Choose between 1 or 2 only...\x1b[0m "
                          << std::endl;
                std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
                std::cout << "\n\n\n"
                          << std::endl;
            }
        }
        else
        {
            std::cout << "\n\n\n"
                      << std::endl;
            std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
            std::cout << std::setw(20) << std::setfill(' ') << ""
                      << "\x1b[1m \x1b[4mNO TRACK FOUND!\n\x1b[0m        \x1b[3mPlease try again or look for another artist.\x1b[0m "
                      << std::endl;
            std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
            std::cout << "\n\n\n"
                      << std::endl;
        }
    }
    mainmenu(hash);
    return 0;
}

/*
    Validate the menu
    @param x x a number to choose from the menu
    @return true if the input matches the menu options, false i it does not match
*/
bool menuverification(std::string x)
{
    if (x == "1" || x == "2" || x == "3" || x == "4" || x == "5")
    {
        return true;
    }
    return false;
}

/*
    Display the menu
    @param none
    @return none
*/
void displayMenu()
{

    std::cout << std::endl;
    std::cout << std::setw(60) << std::setfill('*') << "" << std::endl;
    std::cout << std::setw(50) << std::setfill(' ')
              << u8"\U0001F3B6 Welcome to the Audio Streaming Service Menu" << std::endl;
    std::cout << std::setw(60) << std::setfill('*') << "" << std::endl;
    std::cout << "\n";
    std::cout << "    █▀█▄▄▄▄     ██▄" << std::setw(8) << std::setfill(' ') << ""
              << "1. Add tracks to library" << std::endl;
    std::cout << "    █▀▄▄▄▄█     █▀▀█" << std::setw(7) << std::setfill(' ') << ""
              << "2. Save tracks to your file" << std::endl;
    std::cout << " ▄▄▄█     █  ▄▄▄█"
              << std::setw(10) << std::setfill(' ') << ""
              << "3. Search by Artist/Band Name" << std::endl;
    std::cout << "██▀▄█ ▄██▀█ ███▀█"
              << std::setw(10) << std::setfill(' ') << ""
              << "4. Remove a track" << std::endl;
    std::cout << " ▀▀▀  ▀█▄█▀ ▀█▄█▀"
              << std::setw(10) << std::setfill(' ') << ""
              << "5. Exit" << std::endl;
    std::cout << "\n";
    std::cout << std::setw(60) << std::setfill('*') << "" << std::endl;
    std::cout << std::setw(10) << std::setfill(' ') << ""
              << "Choose an option (1-5): ";
}

/*
    Main menu to choose what to do next
    @param hash hash to read from and write to initialized when running the program
    @return 0
*/
int mainmenu(hashTable &hash)
{
    std::string x;
    displayMenu();
    std::cin >> x;

    while (!menuverification(x))
    {
        std::cout << std::setw(60) << std::setfill('*') << "" << std::endl;
        std::cout << "\n\n\n"
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << std::setw(20) << std::setfill(' ') << ""
                  << "\x1b[1m \x1b[4mINVALID INPUT!\n\x1b[0m        \x1b[3mPlease choose a number between 1 and 5.\x1b[0m "
                  << std::endl;
        std::cout << std::setw(60) << std::setfill('_') << "" << std::endl;
        std::cout << "\n\n\n"
                  << std::endl;
        displayMenu();
        std::cin >> x;
    }

    int option = std::stoi(x);

    switch (option)
    {
    case 1:
        // code to add tracks
        std::cout << "Add tracks selected!" << std::endl;
        fileselection(hash);
        // read(hash);
        break;
    case 2:
        // code to save tracks to file
        std::cout << "Save tracks to file selected!" << std::endl;
        save(hash);
        break;
    case 3:
        // code to search by artist/band name
        // read(hash);
        std::cout << "Search by artist/band name selected!" << std::endl;
        search(hash);
        break;
    case 4:
        // code to remove a track
        std::cout << "Remove a track selected!" << std::endl;
        del(hash);
        break;
    case 5:
        // code to exit
        std::cout << "Exiting program..." << std::endl;
        return 0;
    }
    return 0;
}
