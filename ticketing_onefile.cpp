#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
// Class to create a Booking of link list

class Booking
{
private:
    int bNumber = 0;
    std::string datestr;   /* !< The departure date */
    std::string timestr;   /* !< The departure time */
    std::string dep;       /* !< The departure airport */
    std::string des;       /* !< The destination airport */
    std::string seatClass; /* !< Seat class */
    std::string fName;     /* !< First name */
    std::string lName;     /* !< First name */
    Booking *next;

public:
    Booking(int bNumber, string dateStr, string timeStr, string departure,
            string destination, string seatCl, string firstN, string lastN,
            Booking *next = nullptr)
    {
        // cout << "Testing Booking cl" << seatCl << endl;
        this->bNumber = bNumber;
        this->datestr = dateStr;
        this->timestr = timeStr;
        this->dep = departure;
        this->des = destination;
        this->seatClass = seatCl;
        this->fName = firstN;
        this->lName = lastN;
        this->next = next;
    }
    int getBookingNumber(void) { return this->bNumber; }
    string getFirstName(void) { return this->fName; }
    string getLastName(void) { return this->lName; }
    string getSeatClass(void) { return this->seatClass; }
    string getDate(void) { return this->datestr; }
    string getTime(void) { return this->timestr; }
    string getDeparture(void) { return this->dep; }
    string getDestination(void) { return this->des; }
    Booking *getNextNode(void) { return this->next; }
    void setNextNode(Booking *next) { this->next = next; }
}; // End Booking classs

// Class to creat a linked list

class BookingManager
{
private:
    Booking *head;

public:
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
    ~BookingManager()
    {
        while (this->head != nullptr)
            pop();
    }

    Booking *getBookings(void) { return this->head; } // Getter for booking  node

    // Insertion operator Print out data from Bookings
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
    //  Add a link (push)
    void push(int bookingN, string dateStr, string timeStr, string departure,
              string destination, string seatCl, string firstN, string lastN)
    {
        this->head = new Booking(bookingN, dateStr, timeStr, departure, destination,
                                 seatCl, firstN, lastN, this->head);
    }

    // remove a link (pop)
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

    // Find lenght ()
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
    // Find a booking number
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

// Class to create a Flight node
class Flight
{
private:
    int fNumber = 0;     /* !< Flight number */
    std::string dep;     /* !< The departure airport */
    std::string des;     /* !< The destination airport */
    std::string dateStr; /* !< The departure date */
    std::string timeStr; /* !< The departure time */
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

    Flight(int flightN, string departure, string destination, string dateStr,
           string timeStr, int firstClass, int busClass, int economyClass,
           Flight *next = nullptr)
    {
        this->fNumber = flightN;
        this->dep = departure;
        this->des = destination;
        this->dateStr = dateStr;
        this->timeStr = timeStr;

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

    int getFlightNumber(void) { return this->fNumber; }
    string getDeparture(void) { return this->dep; }
    string getDestination() { return this->des; }
    string getDate() { return this->dateStr; }
    string getTime() { return this->timeStr; }
    int getFseat(void) { return this->fSeat; }
    int getBseat(void) { return this->bSeat; }
    int getEseat(void) { return this->eSeat; }
    Flight *getNextNode(void) { return this->next; }
    void setNextNode(Flight *next) { this->next; }
};

// Class to creat a Flight linked list

/// @brief
class FlightManager
{
private:
    Flight *head;

public:
    FlightManager(void) { this->head = nullptr; }
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
    ~FlightManager()
    {
        while (this->head != nullptr)
            pop();
    }

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
    //  Add a link (push)
    void push(int flightN, string departure, string destination, string dateStr,
              string timeStr, int firstClass, int busClass, int economyClass)
    {
        this->head = new Flight(flightN, departure, destination, dateStr, timeStr,
                                firstClass, busClass, economyClass, this->head);
    }

    // remove a link (pop)
    int pop(void)
    {
        int flightN;
        if (this->head != nullptr)
        {
            flightN = this->head->getFlightNumber();
            // Swap the Booking pointers
            Flight *temp = this->head;
            this->head = this->head->getNextNode();
            delete temp;
        }
        else
        {
            throw std::range_error("List is empty!");
        }
        return flightN;
    } // end pop()
    // Find lenght ()
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
    // Find the flight
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

// Class to create tickets and print txt files.

class Ticket
{

public:
    Ticket(Booking *bookings, Flight *flights)
    {
        int num_tickets = 0;
        fprintf(stdout, "Writing tickets: ");

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
        //  return (num_tickets);
    }

    int allocate_seat(Flight *flight, Booking *booking, int *row, int *seat);
    void print_ticket(Booking *blnp, Flight *flnp, int seat, int row);

}; // End Class Ticket

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

// Print tickets
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
                    << "DEPARTURE: " << flnp->getDeparture()
                    << " DESTINATION:" << flnp->getDestination() << flnp->getDate()
                    << flnp->getTime() << endl;
        ticket_file << "PASSENGER " << blnp->getFirstName() << blnp->getLastName()
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
    FlightManager flights{argv[1]};
    BookingManager bookings{argv[2]};

    Ticket ticket(bookings.getBookings(), flights.getFlights());

    std::cout << "Total flights: " << flights.length()
              << std::endl;
    std::cout << "Total bookings: " << bookings.length() << endl;

    return 0;
} // End main()