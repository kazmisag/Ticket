/**
 * @file ticketing_onefile.cpp
 * @author Syed A G Kazmi (kazmisag@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#define CANCELLED_FLIGHTS "cancelled-flights.txt"

using namespace std;

// Class Common

class Common
{
private:
    std::string datestr; /* !< The departure date */
    std::string timestr; /* !< The departure time */
    std::string dep;     /* !< The departure airport */
    std::string des;     /* !< The destination airport */
public:
    string getDate(void) { return this->datestr; }
    string getTime(void) { return this->timestr; }
    string getDestination(void) { return this->des; }
    string getDeparture(void) { return this->dep; }

    void setDate(string datestr) { this->datestr = datestr; }
    void setTime(string timestr) { this->timestr = timestr; }
    void setDeparture(string dep) { this->dep = dep; }
    void setDestination(string des) { this->des = des; }

}; // End Class Common

// Class to create a Booking of link list

/**
 * @brief Booking class to handle bookings.csv data
 *
 */
class Booking : public Common
{
private:
    int bNumber = 0;       /* !< The booking number */
                           // std::string datestr;   /* !< The departure date */
    std::string timestr;   /* !< The departure time */
    std::string dep;       /* !< The departure airport */
    std::string des;       /* !< The destination airport */
    std::string seatClass; /* !< Seat class */
    std::string fName;     /* !< First name */
    std::string lName;     /* !< First name */
    Booking *next;

public:
    /**
     * @brief Construct a new Booking object
     *
     * @param bNumber !< The booking number
     *@param dateStr                    !< The departure date
     *@param timeStr             !< The departure date
     *@param departure           !< The departure airport
     *@param destination     !< The destination airport
     *@param seatCl  Seat class
     *@param firstN
     *@param lastN
     *@param next
     */
    Booking(int bNumber, string dateStr, string timeStr, string departure,
            string destination, string seatCl, string firstN, string lastN,
            Booking *next = nullptr)
    {
        // cout << "Testing Booking cl" << seatCl << endl;
        this->bNumber = bNumber;
        this->setDate(dateStr);
        this->setTime(timeStr);
        this->setDeparture(departure);
        this->setDestination(destination);
        //  this->datestr = dateStr;
        // this->timestr = timeStr;
        // this->dep = departure;
        // this->des = destination;
        this->seatClass = seatCl;
        this->fName = firstN;
        this->lName = lastN;
        this->next = next;
    }
    /**
     * @brief Get the Booking Number object
     *
     * @return int
     */
    int getBookingNumber(void) { return this->bNumber; }

    /**
     * @brief Get the First Name object
     *
     * @return string
     */
    string getFirstName(void) { return this->fName; }

    /**
     * @brief Get the Last Name object
     *
     * @return string
     */
    string getLastName(void) { return this->lName; }

    /**
     * @brief Get the Seat Class object
     *
     * @return string
     */
    string getSeatClass(void) { return this->seatClass; }

    /**
     * @brief Get the Date object
     *
     * @return string
     */
    //  string getDate(void) { return this->datestr; }

    /**
     * @brief Get the Time object
     *
     * @return string
     */
    //    string getTime(void) { return this->timestr; }

    /**
     * @brief Get the Departure object
     *
     * @return string
     */
    //    string getDeparture(void) { return this->dep; }

    /**
     * @brief Get the Destination object
     *
     * @return string
     */
    // string getDestination(void) { return this->des; }

    /**
     * @brief Get the Next Node object
     *
     * @return Booking*
     */
    Booking *getNextNode(void) { return this->next; }

    /**
     * @brief Set the Next Node object
     *
     * @param next
     */
    void setNextNode(Booking *next) { this->next = next; }
}; // End Booking classs

// Class to creat a linked list
/**
 * @brief BookingManager class to create linked list of flight data
 *
 */
class BookingManager
{
private:
    Booking *head;

public:
    /**
     * @brief Construct a new Booking Manager object
     *
     */
    BookingManager(void) { this->head = nullptr; }

    /**
     * @brief Constructor to load bookings.txt data into bookings linked list
     *
     */
    BookingManager(const string bookingFile)
    {
        // For reading text file
        string line;

        // Creating ifstream class object
        std::ifstream in_file{bookingFile};
        if (in_file.is_open())
        {
            while (in_file >> line)
            {
                stringstream ss(line);
                string bookingN, dateStr, timeStr, departure, destination, seatCl,
                    firstN, lastN;
                // string word;
                // while (!ss.eof()) // works fine
                while (ss.good())
                {
                    getline(ss, bookingN, ',');
                    getline(ss, dateStr, ',');
                    getline(ss, timeStr, ',');
                    getline(ss, departure, ',');
                    getline(ss, destination, ',');
                    getline(ss, seatCl, ',');
                    getline(ss, firstN, ',');
                    getline(ss, lastN, ',');
                    //  cout << bookingN << dateStr << timeStr << departure << destination
                    //   << seatCl << firstN << lastN;

                    // push each booking row to list of bookings
                    BookingManager::push(stoi(bookingN), dateStr, timeStr, departure,
                                         destination, seatCl, firstN, lastN);
                }
                cout << endl;
            }
            in_file.close();
        }
        else
        {
            cout << "Error... Can not open the file\n";
        }
    }

    /**
     * @brief Destroy the Booking Manager object
     *
     */
    ~BookingManager()
    {
        while (this->head != nullptr)
            pop();
    }

    /**
     * @brief Get the Bookings object
     *
     * @return Booking*
     */
    Booking *getBookings(void) { return this->head; } // Getter for booking  node

    // Insertion operator Print out data from Bookings
    /**
     * @brief output stream operator overload function to display linked list data
     *
     * @param os
     * @param rhs
     * @return std::ostream&
     */

    friend std::ostream &operator<<(std::ostream &os, const BookingManager &rhs)
    {
        for (Booking *currNode = rhs.head; currNode != nullptr;
             currNode = currNode->getNextNode())
        {
            os << currNode->getBookingNumber() << " " << currNode->getSeatClass()
               << currNode->getFirstName() << " " << currNode->getLastName() << endl;
            // check if the current node is not NULL
            if (currNode->getNextNode() != nullptr)
                os << " ";
        }
        return os;
    }

    /**
     * @brief  Add a link (push)
     *
     * @param bookingN
     * @param dateStr
     * @param timeStr
     * @param departure
     * @param destination
     * @param seatCl
     * @param firstN
     * @param lastN
     */
    void push(int bookingN, string dateStr, string timeStr, string departure,
              string destination, string seatCl, string firstN, string lastN)
    {
        this->head = new Booking(bookingN, dateStr, timeStr, departure, destination,
                                 seatCl, firstN, lastN, this->head);
    }

    /**
     * @brief  remove a link (pop)
     *
     * @return int
     */
    int pop(void)
    {
        int bookingN;
        if (this->head != nullptr)
        {
            bookingN = this->head->getBookingNumber();
            // Swap the Booking pointers
            Booking *temp = this->head;
            this->head = this->head->getNextNode();
            delete temp;
        }
        else
        {
            throw std::range_error("List is empty!");
        }
        return bookingN;
    } // end pop()

    /**
     * @brief Find lenght ()
     *
     * @return int
     */
    int length(void)
    {
        int count = 0;

        for (Booking *currNode = this->head; currNode != nullptr;
             currNode = currNode->getNextNode())
        {
            count++;
        }
        return count;
    }
    /**
     * @brief Find a booking number
     *
     * @param bn
     * @return true
     * @return false
     */
    bool isBookingFound(int bn)
    {
        for (Booking *currNode = this->head; currNode != nullptr;
             currNode = currNode->getNextNode())
        {
            if (bn == currNode->getBookingNumber())
                return true;
        }
        return false;
    }

}; // End of BookingManager class

/**
 * @brief  Class to create a Flight node
 *
 */
class Flight : public Common
{
private:
    int fNumber = 0; /* !< Flight number */
                     // std::string dep;     /* !< The departure airport */
                     // std::string des;     /* !< The destination airport */
                     // std::string dateStr; /* !< The departure date */
    // std::string timeStr; /* !< The departure time */
    Flight *next;

public:
    int fSeat = 0, /* !< Number of First class seats */
        bSeat = 0, /* !< Number of Business class seats */
        eSeat = 0; /* !< Number of Economy class seats */
    int *fs;       /* !< An array with flags of if
                      a seat is taken or not. 1==occupied, 0==not occupied */
    int *bs;       /* !< An array with flags of if a seat is taken or not. 1==occupied,
                      0==not occupied */
    int *es;       /* !< An array with flags of if a seat is taken or not. 1==occupied,
                      0==not occupied */

    /**
     * @brief Construct a new Flight object
     *
     * @param flightN
     * @param departure
     * @param destination
     * @param dateStr
     * @param timeStr
     * @param firstClass
     * @param busClass
     * @param economyClass
     * @param next
     */
    Flight(int flightN, string departure, string destination, string dateStr,
           string timeStr, int firstClass, int busClass, int economyClass,
           Flight *next = nullptr)
    {
        this->fNumber = flightN;
        this->setDeparture(departure);
        this->setDestination(destination);
        this->setDate(dateStr);
        this->setTime(timeStr);
        // this->dep = departure;
        // this->des = destination;
        //   this->dateStr = dateStr;
        // this->timeStr = timeStr;

        this->fSeat = firstClass;
        this->fs = new int[firstClass * 7]; // create array of seats by multiplying
                                            // Rows by No of seats in each row i.e 7
        memset(this->fs, 0, sizeof(int) * firstClass * 7);

        this->bSeat = busClass;
        this->bs = new int[busClass * 7];
        memset(this->bs, 0, sizeof(int) * busClass * 7);
        this->eSeat = economyClass;
        this->es = new int[economyClass * 7];
        memset(this->es, 0, sizeof(int) * economyClass * 7);
        this->next = next;
    }

    /**
     * @brief Get the Flight Number object
     *
     * @return int
     */
    int getFlightNumber(void) { return this->fNumber; }

    /**
     * @brief Get the Departure object
     *
     * @return string
     */
    // string getDeparture(void) { return this->dep; }

    /**
     * @brief Get the Destination object
     *
     * @return string
     */
    // string getDestination() { return this->des; }

    /**
     * @brief Get the Date object
     *
     * @return string
     */
    // string getDate() { return this->dateStr; }

    /**
     * @brief Get the Time object
     *
     * @return string
     */
    // string getTime() { return this->timeStr; }

    /**
     * @brief Get the Fseat object
     *
     * @return int
     */
    int getFseat(void) { return this->fSeat; }

    /**
     * @brief Get the Bseat object
     *
     * @return int
     */
    int getBseat(void) { return this->bSeat; }

    /**
     * @brief Get the Eseat object
     *
     * @return int
     */
    int getEseat(void) { return this->eSeat; }

    /**
     * @brief Get the Next Node object
     *
     * @return Flight*
     */
    Flight *getNextNode(void) { return this->next; }

    /**
     * @brief Set the Next Node object
     *
     * @param next
     */
    void setNextNode(Flight *next) { this->next = next; }
};

/// @brief Class to creat a Flight linked list
class FlightManager
{
private:
    Flight *head;

public:
    /**
     * @brief Construct a new Flight Manager object
     *
     */
    FlightManager(void) { this->head = nullptr; }

    /**
     * @brief Construct a new Flight Manager object
     *
     * @param flightFile
     */
    FlightManager(const string flightFile)
    {
        string line;
        // For reading text file
        // Creating ifstream class object
        std::ifstream in_file{flightFile};
        if (in_file.is_open())
        {
            while (in_file >> line)
            {
                stringstream ss(line);
                string flightN, departure, destination, dateStr, timeStr, firstClass,
                    busClass, economyClass;
                // while (!ss.eof()) // works fine
                while (ss.good())
                {
                    getline(ss, flightN, ',');
                    getline(ss, departure, ',');
                    getline(ss, destination, ',');
                    getline(ss, dateStr, ',');
                    getline(ss, timeStr, ',');
                    getline(ss, firstClass, ',');
                    getline(ss, busClass, ',');
                    getline(ss, economyClass, ',');
                    // Test print
                    // cout << flightN << dateStr << timeStr << departure << destination
                    // << firstClass << busClass << economyClass << endl;

                    // push each flight record to flights linked list
                    FlightManager::push(stoi(flightN), departure, destination, dateStr,
                                        timeStr, stoi(firstClass), stoi(busClass),
                                        stoi(economyClass));
                }
                cout << endl;
            }
            in_file.close();
        }
        else
        {
            cout << "Error... Can not open the file\n";
        }
    }

    /**
     * @brief Destroy the Flight Manager object
     *
     */
    ~FlightManager()
    {
        while (this->head != nullptr)
            pop();
    }

    /**
     * @brief Get the Flights object
     *
     * @return Flight*
     */
    Flight *getFlights(void) { return this->head; }

    //  Print flight data to screen(Insertion operator)
    friend std::ostream &operator<<(std::ostream &os, const FlightManager &rhs)
    {
        for (Flight *currNode = rhs.head; currNode != nullptr;
             currNode = currNode->getNextNode())
        {
            os << currNode->getFlightNumber() << " " << endl;
            // check if the current node is not NULL
            if (currNode->getNextNode() != nullptr)
                os << "";
        }
        return os;
    }

    /**
     * @brief  Add a link (push)
     *
     * @param flightN
     * @param departure
     * @param destination
     * @param dateStr
     * @param timeStr
     * @param firstClass
     * @param busClass
     * @param economyClass
     */
    void push(int flightN, string departure, string destination, string dateStr,
              string timeStr, int firstClass, int busClass, int economyClass)
    {
        this->head = new Flight(flightN, departure, destination, dateStr, timeStr,
                                firstClass, busClass, economyClass, this->head);
    }

    /**
     * @brief  remove a link (pop)
     *
     * @return int
     */
    int pop(void)
    {
        int flightN;
        try
        {
            if (this->head == nullptr)
            {
                throw "List is empty!";
            }
            else
            {
                flightN = this->head->getFlightNumber();
                // Swap the Booking pointers
                Flight *temp = this->head;
                this->head = this->head->getNextNode();
                delete temp;
            }
        }
        catch (const char *emptyList)
        {
            std::cout << emptyList << std::endl;
        }
        return flightN;
    } // end pop()

    /**
     * @brief  Find lenght ()
     *
     * @return int
     */
    int length(void)
    {
        int count = 0;
        for (Flight *currNode = this->head; currNode != nullptr;
             currNode = currNode->getNextNode())
        {
            count++;
        }

        return count;
    }
    /**
     * @brief  Find the flight
     *
     * @param fn
     * @return true
     * @return false
     */
    bool isFlightFound(int fn)
    {
        for (Flight *currNode = this->head; currNode != nullptr;
             currNode = currNode->getNextNode())
        {
            if (fn == currNode->getFlightNumber())
                return true;
        }
        return false;
    }
}; // End of linkedlist class

/**
 * @brief  Class to create tickets and print txt files.
 *
 */
class Ticket
{

public:
    /**
     * @brief Construct a new Ticket object
     *
     * @param bookings
     * @param flights
     */
    Ticket(Booking *bookings, Flight *flights)
    {
        int num_tickets = 0, num_flights = 0;
        fprintf(stdout, "Writing tickets: ");
        // Code to find flights with booking and print tickets
        for (Booking *blnp = bookings; blnp != nullptr;
             blnp = blnp->getNextNode())
        {
            for (Flight *flnp = flights; flnp != nullptr;
                 flnp = flnp->getNextNode())
            {
                /* find the flight for this booking */
                if (!(blnp->getDate().compare(flnp->getDate())) &&
                    !(blnp->getTime().compare(flnp->getTime())) &&
                    !(blnp->getDeparture().compare(flnp->getDeparture())) &&
                    !(blnp->getDestination().compare(flnp->getDestination())))
                {
                    int row = 0, seat = 0;
                    if (allocate_seat(flnp, blnp, &row, &seat))
                    {
                        fprintf(stdout, "[ticket-%d.txt]\n", blnp->getBookingNumber());
                        print_ticket(blnp, flnp, seat, row);
                        num_tickets++;
                    }
                }
            }
        }
        // Cancel this flight without any bookings and print in cancelled-flihgts.txt

        for (Flight *flnp = flights; flnp != nullptr;
             flnp = flnp->getNextNode())
        {
            bool isFound = false; // flag to check if the booking is found for this flight
            for (Booking *blnp = bookings; blnp != nullptr;
                 blnp = blnp->getNextNode())
            {
                /* find the flight for this booking */
                if (!(flnp->getDate().compare(blnp->getDate())) &&
                    !(flnp->getTime().compare(blnp->getTime())) &&
                    !(flnp->getDeparture().compare(blnp->getDeparture())) &&
                    !(flnp->getDestination().compare(blnp->getDestination())))
                {
                    isFound = true;
                    // cout << flnp->getFlightNumber() << " Booking not found";
                }
                /*  else
                  {
                      std::cout << "Cancelling flight number: " << flnp->getFlightNumber() << std::endl;
                      cancel_flight(flnp);
                      num_flights++;
                  }*/
            }
            if (!isFound)
            {
                std::cout << "Cancelling flight number: " << flnp->getFlightNumber() << std::endl;
                cancel_flight(flnp);
                num_flights++;
            }
            // else
            //   isFound = false; // Reset the flag
        }
    }
    /**
     * @brief Allocate a seat
     *
     * @param flight
     * @param booking
     * @param row
     * @param seat
     * @return int
     */
    int allocate_seat(Flight *flight, Booking *booking, int *row, int *seat);

    /**
     * @brief Print tickets to text files
     *
     * @param blnp
     * @param flnp
     * @param seat
     * @param row
     */
    void print_ticket(Booking *blnp, Flight *flnp, int seat, int row);

    /**
     * @brief Function to cancel flights without any bookings
     *
     * @param flnp Flight class pointer
     */
    void cancel_flight(Flight *flnp);

}; // End Class Ticket

/**
 * @brief Implementation of allocate seat function
 *
 * @param flight
 * @param booking
 * @param row
 * @param seat
 * @return int
 */
int Ticket::allocate_seat(Flight *flight, Booking *booking, int *row,
                          int *seat)
{
    int sn = 0;
    int rn = 0;
    if (booking->getSeatClass().compare("first") == 0)
    {
        for (int p = 0; p < flight->fSeat * 7; p++)
        {
            if (flight->fs[p] == 0)
            {
                flight->fs[p] = 1;
                sn = p + 1;
                rn = (int)p / 7 + 1;
                break;
            }
        }
    }
    if (booking->getSeatClass().compare("business") == 0)
    {
        for (int p = 0; p < flight->bSeat * 7; p++)
        {
            if (flight->bs[p] == 0)
            {
                flight->bs[p] = 1;
                sn = p + flight->fSeat * 7 + 1; /* humans usually start counting at 1 */
                rn = flight->fSeat + (int)p / 7 + 1;
                break;
            }
        }
    }
    if ((booking->getSeatClass().compare("economy")) == 0)
    {
        for (int p = 0; p < flight->eSeat * 7; p++)
        {
            if (flight->es[p] == 0)
            {
                flight->es[p] = 1;
                sn = p + flight->fSeat * 7 + flight->bSeat * 7 +
                     1; /* humans usually start counting at 1 */
                rn = flight->fSeat + flight->bSeat + (int)p / 7 + 1;
                break;
            }
        }
    }
    if (rn == 0 || sn == 0)
    {
        cout << "Did not find class " << booking->getSeatClass()
             << " for booking on this plane\n";
        return (0);
    }
    *row = rn;
    *seat = sn;
    return (1);
}
/**
 * @brief Function to print cancelled fligths into a cancelled-flihgts.txt
 *
 * @param flnp Flight class pointer
 */
void Ticket::cancel_flight(Flight *flnp)
{

    std::ofstream flight_report(CANCELLED_FLIGHTS, ios::app); // create txt file in append mode

    if (flight_report.is_open())
    {
        flight_report << flnp->getFlightNumber() << " has been cancelled due to non-booking" << std::endl;
    }
    else
    {
        cout << "Error... cancelled-flihgts.txt can not be created/opened!" << endl;
    }
}
/*
 * @brief Function to print tickets into txt files
 *
 *
 * @param blnp
 * @param flnp
 * @param seat
 * @param row
 */

void Ticket::print_ticket(Booking *blnp, Flight *flnp, int seat, int row)
{
    char file_name[255];
    sprintf(file_name, "ticket-%d.txt", blnp->getBookingNumber());
    // cout << file_name << endl;
    std::ofstream ticket_file(file_name, ios::out); // Create a file

    // Handle file opening error
    if (ticket_file.is_open()) // Open the file
    {
        ticket_file << "BOOKING: " << blnp->getBookingNumber() << endl;
        ticket_file << "FLIGHT: " << flnp->getFlightNumber()
                    << " DEPARTURE: " << flnp->getDeparture()
                    << " DESTINATION:" << flnp->getDestination() << flnp->getDate()
                    << flnp->getTime() << endl;
        ticket_file << "PASSENGER: " << blnp->getFirstName() << blnp->getLastName()
                    << endl;
        ticket_file << "CLASS: " << blnp->getSeatClass() << endl;
        ticket_file << "ROW " << row << " SEAT " << seat << endl;
        ticket_file.close(); // Close the file
    }
    else
    {
        cout << "Error... Ticket file can not be created/opened!" << endl;
    }
} // print_tickets()

/// @brief main() function to run the program.
/// @param argc
/// @param argv
/// @return

int main(int argc, char **argv)
{
    try
    {
        if (argc != 3)
        {
            throw "Please provide both data files (flights.csv & bookings.csv)\n";
        }
    }
    catch (const char *what)
    { // catch all char * exceptions
        cerr << "Error: " << what << endl;
        return (-1);
    }
    FlightManager flights{argv[1]};
    BookingManager bookings{argv[2]};

    Ticket ticket(bookings.getBookings(), flights.getFlights());

    std::cout << "Total number of flights: " << flights.length()
              << std::endl;
    std::cout << "Total number of bookings: " << bookings.length() << endl;
    return 0;
} // End main()