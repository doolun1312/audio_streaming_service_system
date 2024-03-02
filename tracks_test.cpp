/*
tracks_test.cpp
Author: M00835210
Created: 18/04/2023
Updated: 20/04/2023
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "maintracks.h"


/*Test the track class, by creating objects and checking the data with getTitle(), 
getArtist() and getDuration() functions*/ 
TEST_CASE("Track Test")
{
    Track track1("title1", "artist1", 180);
    Track track2("title2", "artist2", 210);
    Track track3("title3", "artist3", 240);
    Track track4("title4", "artist4", 270);
    Track track5("title5", "artist5", 300);
    REQUIRE(track1.getTitle() == "title1");
    REQUIRE(track1.getArtist() == "artist1");
    REQUIRE(track1.getDuration() == std::to_string(180));
    REQUIRE(track2.getTitle() == "title2");
    REQUIRE(track2.getArtist() == "artist2");
    REQUIRE(track2.getDuration() == std::to_string(210));
    REQUIRE(track3.getTitle() == "title3");
    REQUIRE(track3.getArtist() == "artist3");
    REQUIRE(track3.getDuration() == std::to_string(240));
    REQUIRE(track4.getTitle() == "title4");
    REQUIRE(track4.getArtist() == "artist4");
    REQUIRE(track4.getDuration() == std::to_string(270));
    REQUIRE(track5.getTitle() != "title test");
    REQUIRE(track5.getArtist() != "artist test");
    REQUIRE(track5.getDuration() != std::to_string(400));
}

/*Test the hash table by adding key-value pairs to the hash and 
checking the total number of items in the hash and its size and 
what data there is at certain indexes*/
TEST_CASE("Hash Table Test")
{
    hashTable hash(2);
    Track t1("title1", "artist1", 450);
    Track t2("title2", "artist2", 320);
    hash.add("key1", t1);
    hash.add("key2", t2);
    REQUIRE(hash.getTotal() == 2);
    REQUIRE(hash.index("key1", "title1") == 0);
    REQUIRE(hash.index("key2", "title2") == 1);
    hash.remove(0);
    REQUIRE(hash.getTotal() == 1);
    REQUIRE(hash.index("key1", "title1") == -1);
    REQUIRE(hash.find("key2").size() == 1);
    hash.resize(5);
    REQUIRE(hash.getSize() == 5);
}

// Check if file exists
TEST_CASE("file test", "[file]")
{
    REQUIRE(fileverification("tracks.txt") == true);
    REQUIRE(fileverification("abc.txt") == false);
    REQUIRE(fileverification("123.dat") == false);
    REQUIRE(fileverification("testfile.txt") == false);
    REQUIRE(fileverification("testing.txt") == false);
}

// Check if menu input works well
TEST_CASE("menu test", "[menu]")
{
    std::vector<std::string> menu;
    menu.push_back("1");
    menu.push_back("2");
    menu.push_back("3");
    menu.push_back("4");
    menu.push_back("5");
    REQUIRE(menuverification(menu[0]) == true);
    REQUIRE(menuverification(menu[2]) == true);
    REQUIRE(menuverification(menu[3]) == true);
    REQUIRE(menuverification(menu[1]) == true);
    REQUIRE(menuverification(menu[4]) == true);
    REQUIRE(menuverification("9") == false);
    REQUIRE(menuverification("hello") == false);
}

// Check if the hash can be resized
TEST_CASE("add input", "[resize]")
{
    hashTable hash(6007);
    std::vector<std::string> added;
    std::string artisttest = "test1 title";
    Track track(artisttest, "test1 artist", 300);
    hash.add(artisttest, track);
    hash.resize(6007 + hash.getTotal());
    REQUIRE(hash.getTotal() == 1);
    REQUIRE(hash.getSize() == 6007 + 1);
}

// Check if a track is deleted
TEST_CASE("delete input", "[remove]")
{
    hashTable hash(6007);
    std::string artisttest = "test2 title";
    Track track(artisttest, "test2 artist", 350);
    hash.add(artisttest, track);
    REQUIRE(hash.getTotal() == 1);
    hash.remove(hash.index(artisttest, track.getTitle()));
    REQUIRE(hash.getTotal() == 0);
    REQUIRE(hash.index(artisttest, "test2 artist") == -1);
}

/*Check if when adding a key-value pair to the hash 
it is present in the hash table */
TEST_CASE("Testing add function", "[add]")
{
    Track track("title test", "artist test", 240);
    hashTable hash(1);
    hash.add("key test", track);
    Pair **table = hash.getTable();
    REQUIRE(table[0]->key == "key test");
    REQUIRE(table[0]->value.getTitle() == "title test");
    REQUIRE(table[0]->value.getArtist() == "artist test");
    REQUIRE(table[0]->value.getDuration() == std::to_string(240));
    REQUIRE(hash.getSize() == 1);
    REQUIRE(hash.getTotal() == 1);
}

/*Testing the find function to see if key-value pairs 
can be found by the key*/
TEST_CASE("Testing find function", "[find]")
{
    Track track1("title1", "artist1", 180);
    Track track2("title2", "artist2", 210);
    Track track3("title3", "artist3", 240);
    Track track4("title4", "artist4", 270);
    Track track5("title5", "artist5", 300);
    hashTable hash(10);
    hash.add(track1.getArtist(), track1);
    hash.add(track2.getArtist(), track2);
    hash.add(track3.getArtist(), track3);
    hash.add(track4.getArtist(), track4);
    hash.add(track5.getArtist(), track5);
    std::vector<Pair *> results1 = hash.find(track1.getArtist());
    REQUIRE(results1[0]->value.getTitle() == track1.getTitle());
    REQUIRE(results1[0]->value.getArtist() == track1.getArtist());
    REQUIRE(results1[0]->value.getDuration() == track1.getDuration());
    std::vector<Pair *> results2 = hash.find(track2.getArtist());
    REQUIRE(results2[0]->value.getTitle() == track2.getTitle());
    REQUIRE(results2[0]->value.getArtist() == track2.getArtist());
    REQUIRE(results2[0]->value.getDuration() == track2.getDuration());
    std::vector<Pair *> results3 = hash.find(track3.getArtist());
    REQUIRE(results3[0]->value.getTitle() == track3.getTitle());
    REQUIRE(results3[0]->value.getArtist() == track3.getArtist());
    REQUIRE(results3[0]->value.getDuration() == track3.getDuration());
    std::vector<Pair *> results4 = hash.find(track4.getArtist());
    REQUIRE(results4[0]->value.getTitle() == track4.getTitle());
    REQUIRE(results4[0]->value.getArtist() == track4.getArtist());
    REQUIRE(results4[0]->value.getDuration() == track4.getDuration());
    std::vector<Pair *> results5 = hash.find(track5.getArtist());
    REQUIRE(results5[0]->value.getTitle() == track5.getTitle());
    REQUIRE(results5[0]->value.getArtist() == track5.getArtist());
    REQUIRE(results5[0]->value.getDuration() == track5.getDuration());
}

/*Testing the find function to see if key-value pairs 
can be found by the key and title of the track*/
TEST_CASE("Testing findPair function", "[findPair]")
{
    Track track1("title1", "artist1", 180);
    Track track2("title2", "artist2", 210);
    Track track3("title3", "artist3", 240);
    Track track4("title4", "artist4", 270);
    Track track5("title5", "artist5", 300);
    hashTable hash(10);
    hash.add(track1.getArtist(), track1);
    hash.add(track2.getArtist(), track2);
    hash.add(track3.getArtist(), track3);
    hash.add(track4.getArtist(), track4);
    hash.add(track5.getArtist(), track5);
    std::vector<Pair *> results1 = hash.findPair(track1.getArtist(), track1.getTitle());
    REQUIRE(results1[0]->value.getTitle() == track1.getTitle());
    REQUIRE(results1[0]->value.getArtist() == track1.getArtist());
    REQUIRE(results1[0]->value.getDuration() == track1.getDuration());
    std::vector<Pair *> results2 = hash.findPair(track2.getArtist(), track2.getTitle());
    REQUIRE(results2[0]->value.getTitle() == track2.getTitle());
    REQUIRE(results2[0]->value.getArtist() == track2.getArtist());
    REQUIRE(results2[0]->value.getDuration() == track2.getDuration());
    std::vector<Pair *> results3 = hash.findPair(track3.getArtist(), track3.getTitle());
    REQUIRE(results3[0]->value.getTitle() == track3.getTitle());
    REQUIRE(results3[0]->value.getArtist() == track3.getArtist());
    REQUIRE(results3[0]->value.getDuration() == track3.getDuration());
    std::vector<Pair *> results4 = hash.findPair(track4.getArtist(), track4.getTitle());
    REQUIRE(results4[0]->value.getTitle() == track4.getTitle());
    REQUIRE(results4[0]->value.getArtist() == track4.getArtist());
    REQUIRE(results4[0]->value.getDuration() == track4.getDuration());
    std::vector<Pair *> results5 = hash.findPair(track5.getArtist(), track5.getTitle());
    REQUIRE(results5[0]->value.getTitle() == track5.getTitle());
    REQUIRE(results5[0]->value.getArtist() == track5.getArtist());
    REQUIRE(results5[0]->value.getDuration() == track5.getDuration());
}

/*Checking if when saving key-value pairs in a track if it
 is present in the file by calculating the number of lines 
 and checking if it is the same as the hash table's total*/
TEST_CASE("Testing save function", "[save]")
{
    std::string file;
    Track track1("title1", "artist1", 180);
    Track track2("title2", "artist2", 210);
    Track track3("title3", "artist3", 240);
    Track track4("title4", "artist4", 270);
    Track track5("title5", "artist5", 300);
    hashTable hash(10);
    hash.add(track1.getArtist(), track1);
    hash.add(track2.getArtist(), track2);
    hash.add(track3.getArtist(), track3);
    hash.add(track4.getArtist(), track4);
    hash.add(track5.getArtist(), track5);
    std::cout << "Enter the name of the file where you want to save your library: ";
    std::cin >> file;
    std::ofstream outputfile(file);
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
    int numLines = 0;
    std::ifstream tracksfile(file);
    std::string word;
    while (std::getline(tracksfile, word))
    {
        ++numLines;
    }
    REQUIRE(std::to_string(numLines) == std::to_string(hash.getTotal()));
}