# 2022-23 CST2550 Software Engineering Management and Development coursework2

## Brief Task Description
A new audio streaming service requires a system to maintain the library of tracks available. There
will be billions of tracks in the system and they will be constantly searched by artist/band name.
New tracks will also be added regularly by loading a list of new tracks from a file.
You should select, with justification, and implement an appropriate data structure to store
song details to be searched. You must complete time complexity analysis of the key operations
using this data structure. A sample file of song details will be made available for use in designing,
implementing and testing the system [note: different files of the same format will be used for
marking].
The focus of this task is the library and search functionality, you should not implement any
audio playing functionality.
You should not use any third party libraries or code as a part of your solution and all code
should be written by you, i.e. not automatically generated. You also shouldn’t use non-standard or
operating system dependant libraries in your program or operating system calls (the code should
all be standard C++).
As the focus of this task is the data structure, you must design and implement the data
structures yourself. Marks will not be allocated for the use of standard template library (STL)
data structures.
Apply the knowledge you have gained on this module to select and design the data structures
and algorithms which are most appropriate and to analysis the time-complexity for your report.

## Scenario
A new audio streaming service will be introduced. At this initial phase of development a program
with efficient track search functionality is required. The client program with audio play
functionality is NOT required at this stage.
Details of tracks will be loaded from files. If a file is loaded it should add all tracks to the
library. If a track is already in the library it should not be added again.
There should be functionality to:
• add all tracks from a file
• save tracks in the library to a file
• search by artist/band name
• remove specific track(s)
Your program must use an appropriate data structure to store the details of tracks in the
library.
You will be provided with a small sample data file in the correct format to use when writing
and testing your program. However, the program should work with any file of this format (and
another file will be used when marking your work); therefore, your program should allow the user
to specify the input file name (do NOT hardcode the file name).
