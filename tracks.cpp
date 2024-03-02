/*
tracks.cpp
Author: M00835210
Created: 19/03/2023
Updated: 17/04/2023
*/

#include "tracks.h"
#include <iostream>

Track::Track(std::string title, std::string artist, int duration)
{
    this->title = title;
    this->artist = artist;
    this->duration = duration;
};

Track::~Track()
{
}

/* 
    Display the title, artist and duration of the tracks in order
    @param none
    @return all attributes of the tracks in a single line
*/
std::string Track::description()
{
    return ("Track name: " + title + "  Artist(s): " + artist + "   Duration: " + std::to_string(duration));
}

/* 
    Dislay title of a track
    @param none
    @return title of a track
*/
std::string Track::getTitle()
{
    return (title);
}

/* 
    Dislay artist of a track
    @param none
    @return artist of a track
*/
std::string Track::getArtist()
{
    return (artist);
}

/* 
    Dislay duration of a track
    @param none
    @return duration of a track
*/
std::string Track::getDuration()
{
    return (std::to_string(duration));
}

/* 
    Display the title, artist and duration of the tracks in the same format as the files
    @param none
    @return all attributes of the tracks in a single line
*/
std::string Track::descriptionsave()
{

    return (title + "	" + artist + "	" + std::to_string(duration));
}

/* 
    Add a track
    @param none
    @return all new attributes of the tracks in a single line
*/
std::string Track::add()
{
    std::cout << "\nPlease enter the title of the track: ";
    std::cin >> title;
    std::cout << "\nPlease enter the artist(s) of the track: ";
    std::cin >> artist;
    std::cout << "\nPlease enter the duration of the track: ";
    std::cin >> duration;
    return (title + "	" + artist + "   " + std::to_string(duration));
}
