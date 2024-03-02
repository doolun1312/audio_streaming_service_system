#ifndef _TRACKS_H_
#define _TRACKS_H_

/*
tracks.h
Author: M00835210
Created: 18/03/2023
Updated: 17/04/2023
*/

#include <string>

/*Track class defining and displaying the attributes of all the tracks in a function returning
 the description with labels such as Title, Artist and duration, another function returning the 
 tracks in the same layout as the files inputed and functions displaying the title, 
 the artist and the duration seperately*/
class Track
{
private:
  std::string title;
  std::string artist;
  int duration;

public:
  Track() {}
  Track(std::string title, std::string artist, int duration);
  virtual ~Track();
  std::string description();
  std::string getTitle();
  std::string getArtist();
  std::string getDuration();
  std::string descriptionsave();
  std::string add();
};

#endif
