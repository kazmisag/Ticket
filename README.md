# Ticket

A program developed in C++ to print flight tickets using data from two .txt files.

# Required data files:

flights.csv - To access pre-stored flights data in ./lib directory

bookings.csv - To access pre-stored bookings data ./lib  directory

# RUN PROGRAM  

# From command prompt

$ main.exe flights.csv bookings.csv // from command prompt 

# Using Makefile

$ make check // to build the program

$ make run // To run the program

$ make clean // To delete all ticket files and build directories

# ADDITIONAL CODING FEAUTRES

- try catch throw feature added to main() and some other functions.
- Implemented Inheritance through "class Common" for common variables and getters/setters functions for both Booking & Flight class.
- Added functionality to print a report of cancelled fligths in "cancelled-flights.txt".
