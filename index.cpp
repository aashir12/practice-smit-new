#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int MAX_FLIGHTS = 100;
const int MAX_PASSENGERS = 100;
const int MAX_BOOKINGS = 100;

class Flight {
public:
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
    string arrivalTime;
    int availableSeats;

    Flight() : availableSeats(0) {}
    Flight(string fn, string o, string d, string dt, string at, int seats)
        : flightNumber(fn), origin(o), destination(d), departureTime(dt), arrivalTime(at), availableSeats(seats) {}

    void displayFlightDetails() {
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Origin: " << origin << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure Time: " << departureTime << endl;
        cout << "Arrival Time: " << arrivalTime << endl;
        cout << "Available Seats: " << availableSeats << endl;
    }
    void scheduleFlight() {
        cout << "Flight " << flightNumber << " has been scheduled!" << endl;
    }
    void modifyFlight(string newDepartureTime, string newArrivalTime, int newAvailableSeats) {
        departureTime = newDepartureTime;
        arrivalTime = newArrivalTime;
        availableSeats = newAvailableSeats;
        cout << "Flight " << flightNumber << " has been modified!" << endl;
    }
    void cancelFlight() {
        cout << "Flight " << flightNumber << " has been cancelled!" << endl;
    }
};

class Passenger {
public:
    string passengerID;
    string name;
    string email;
    string phone;
    int baggageAllowance;

    Passenger() : baggageAllowance(0) {}
    Passenger(string id, string n, string e, string p, int ba)
        : passengerID(id), name(n), email(e), phone(p), baggageAllowance(ba) {}

    void registerPassenger() {
        cout << "Passenger " << name << " has been registered!" << endl;
    }
    void updateProfile(string newEmail, string newPhone, int newBaggageAllowance) {
        email = newEmail;
        phone = newPhone;
        baggageAllowance = newBaggageAllowance;
        cout << "Profile for " << name << " has been updated!" << endl;
    }
    void viewProfile() {
        cout << "Passenger ID: " << passengerID << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Baggage Allowance: " << baggageAllowance << "kg" << endl;
    }
};

class Booking {
public:
    string bookingID;
    Passenger passenger;
    Flight flight;
    string bookingDate;
    string status;

    Booking() : status("Pending") {}
    Booking(string id, Passenger p, Flight f, string date)
        : bookingID(id), passenger(p), flight(f), bookingDate(date), status("Confirmed") {}

    void createBooking() {
        cout << "Booking ID: " << bookingID << " has been created for " << passenger.name << " on Flight " << flight.flightNumber << endl;
    }
    void cancelBooking() {
        cout << "Booking ID: " << bookingID << " has been cancelled!" << endl;
        flight.availableSeats++;
    }
    void viewBookingDetails() {
        cout << "Booking ID: " << bookingID << endl;
        passenger.viewProfile();
        flight.displayFlightDetails();
        cout << "Booking Date: " << bookingDate << endl;
        cout << "Status: " << status << endl;
    }
};

class Ticket {
public:
    string ticketID;
    Booking booking;
    string issueDate;
    string ticketStatus;

    Ticket() : ticketStatus("Not Issued") {}
    Ticket(string id, Booking b, string date)
        : ticketID(id), booking(b), issueDate(date), ticketStatus("Issued") {}

    void generateTicket() {
        ticketStatus = "Issued";
        cout << "Ticket " << ticketID << " has been generated for booking " << booking.bookingID << endl;
    }
    void validateTicket() {
        cout << "Ticket " << ticketID << " status: " << ticketStatus << endl;
    }
    void reissueTicket() {
        ticketStatus = "Reissued";
        cout << "Ticket " << ticketID << " has been reissued!" << endl;
    }
};

class AirlineManagement {
public:
    Flight flights[MAX_FLIGHTS];
    Passenger passengers[MAX_PASSENGERS];
    Booking bookings[MAX_BOOKINGS];
    int numFlights, numPassengers, numBookings;

    AirlineManagement() : numFlights(0), numPassengers(0), numBookings(0) {}

    string generateBookingID() {
        return "B" + to_string(time(0));
    }

    void addFlight() {
        if (numFlights >= MAX_FLIGHTS) {
            cout << "Maximum number of flights reached." << endl;
            return;
        }
        string fn, origin, destination, dt, at;
        int seats;
        cout << "Enter Flight Number: ";
        cin >> fn;
        cout << "Enter Origin: ";
        cin >> origin;
        cout << "Enter Destination: ";
        cin >> destination;
        cout << "Enter Departure Time (HH:MM): ";
        cin >> dt;
        cout << "Enter Arrival Time (HH:MM): ";
        cin >> at;
        cout << "Enter Available Seats: ";
        cin >> seats;
        flights[numFlights++] = Flight(fn, origin, destination, dt, at, seats);
        cout << "Flight " << fn << " added successfully!" << endl;
    }

    void bookFlight() {
        if (numPassengers >= MAX_PASSENGERS || numBookings >= MAX_BOOKINGS) {
            cout << "Maximum capacity reached. Cannot book more flights." << endl;
            return;
        }
        string name, email, phone, flightNumber;
        int baggageAllowance;
        cout << "Enter Passenger Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        cout << "Enter Baggage Allowance (kg): ";
        cin >> baggageAllowance;
        cout << "Enter Flight Number to Book: ";
        cin >> flightNumber;

        Passenger p("P" + to_string(numPassengers + 1), name, email, phone, baggageAllowance);

        for (int i = 0; i < numFlights; ++i) {
            if (flights[i].flightNumber == flightNumber && flights[i].availableSeats > 0) {
                time_t now = time(0);
                string bookingDate(ctime(&now));
                bookingDate.erase(bookingDate.find('\n'));
                bookings[numBookings++] = Booking(generateBookingID(), p, flights[i], bookingDate);
                flights[i].availableSeats--;
                cout << "Booking confirmed!" << endl;
                return;
            }
        }
        cout << "Flight not found or no seats available." << endl;
    }

    void displayBookings() {
        if (numBookings == 0) {
            cout << "No bookings found." << endl;
            return;
        }
        cout << "\nBookings:\n";
        for (int i = 0; i < numBookings; ++i) {
            bookings[i].viewBookingDetails();
            cout << "-------------------------" << endl;
        }
    }

    void cancelBooking(string bookingID) {
        for (int i = 0; i < numBookings; ++i) {
            if (bookings[i].bookingID == bookingID) {
                bookings[i].cancelBooking();
                bookings[i] = bookings[--numBookings];
                cout << "Booking " << bookingID << " cancelled successfully!" << endl;
                return;
            }
        }
        cout << "Booking " << bookingID << " not found." << endl;
    }
};

int main() {
    AirlineManagement airline;
    int choice;
    do {
        cout << "\nAirline Management System\n";
        cout << "1. Add Flight\n";
        cout << "2. Display Flights\n";
        cout << "3. Book Flight\n";
        cout << "4. Display Bookings\n";
        cout << "5. Cancel Booking\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                airline.addFlight();
                break;
            case 2:
                for (int i = 0; i < airline.numFlights; ++i) {
                    airline.flights[i].displayFlightDetails();
                    cout << "-----------------------------" << endl;
                }
                break;
            case 3:
                airline.bookFlight();
                break;
            case 4:
                airline.displayBookings();
                break;
            case 5: {
                string bookingID;
                cout << "Enter Booking ID to cancel: ";
                cin >> bookingID;
                airline.cancelBooking(bookingID);
            } break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
    return 0;
}
