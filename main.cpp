#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

class Node {
public:
    string name;
    string gen;
    int age;
    shared_ptr<Node> link;
};

shared_ptr<Node> start = nullptr;

// Function declarations
void details(int);
int seat(int);
int cal(int, int, int);
void bill(int, int);
void add_node(const string&, const string&, int);
void display_seat_matrix();
void clear_data();

// Global variables
string source, des, train;
string station, cla;
int time1, time2;
vector<int> booked_seats(61, 0); // Seat flags (1-60)
vector<int> passenger_seats;

int main() {
    char choice;

    do {
        int train_choice, total_fare = 0, num_passengers;
        bool valid_train = false;

        cout << "\n==================== TRAIN TICKET BOOKING ====================\n";
        cout << "Enter Number Of Passengers: ";
        cin >> num_passengers;
        cin.ignore();

        details(num_passengers);

        cout << "\nEnter The Source Place: ";
        getline(cin, source);
        cout << "Enter The Destination Place: ";
        getline(cin, des);

        cout << "\n=============== Available Trains ===============\n";
        cout << "1. Rajdhani Express........10:00 a.m........Sealdah Station\n";
        cout << "2. Satabdi Express.........05:00 p.m........Howrah Station\n";
        cout << "3. Humsafar Express........11:00 p.m........Kolkata Chitpur Station\n";
        cout << "4. Garib-Rath Express......05:00 p.m........Sealdah Station\n";
        cout << "5. Duronto Express.........07:00 a.m........Santraganchi Station\n";

        while (!valid_train) {
            cout << "Enter Train Choice (1-5): ";
            cin >> train_choice;

            switch (train_choice) {
            case 1:
                train = "Rajdhani Express";
                station = "Sealdah Station";
                time1 = 10; time2 = 00;
                total_fare = cal(1499, 899, num_passengers);
                valid_train = true;
                break;
            case 2:
                train = "Satabdi Express";
                station = "Howrah Station";
                time1 = 17; time2 = 00;
                total_fare = cal(1399, 799, num_passengers);
                valid_train = true;
                break;
            case 3:
                train = "Humsafar Express";
                station = "Kolkata Chitpur Station";
                time1 = 23; time2 = 00;
                total_fare = cal(1599, 1099, num_passengers);
                valid_train = true;
                break;
            case 4:
                train = "Garib-Rath Express";
                station = "Sealdah Station";
                time1 = 17; time2 = 00;
                total_fare = cal(1199, 699, num_passengers);
                valid_train = true;
                break;
            case 5:
                train = "Duronto Express";
                station = "Santraganchi Station";
                time1 = 7; time2 = 00;
                total_fare = cal(1699, 1199, num_passengers);
                valid_train = true;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        }

        cout << "\n>> Total Fare (incl. 10% GST): Rs. " << total_fare << "\n";

        seat(num_passengers);
        bill(total_fare, num_passengers);

        cout << "\nDo you want to book another ticket? (Y/N): ";
        cin >> choice;
        cin.ignore();

        clear_data();

    } while (choice == 'Y' || choice == 'y');

    cout << "\n================= THANK YOU FOR USING OUR SYSTEM! =================\n";
    return 0;
}

// ---------- Other Function Definitions ---------- //

int cal(int ac_price, int sleeper_price, int count) {
    int total = 0, choice, sub_choice;

    cout << "\nChoose Class:\n";
    cout << "1. Sleeper Class\n";
    cout << "2. A.C. Class\n";
    cin >> choice;

    switch (choice) {
    case 1:
        cla = "Sleeper Class";
        total = sleeper_price * count;
        break;
    case 2:
        cout << "Choose A.C. Type:\n";
        cout << "1. 3A Class\n2. 2A Class\n3. 1st Class A.C.\n";
        cin >> sub_choice;
        switch (sub_choice) {
        case 1:
            cla = "3A Class";
            total = ac_price * count;
            break;
        case 2:
            cla = "2A Class";
            total = (ac_price + 700) * count;
            break;
        case 3:
            cla = "1st Class A.C.";
            total = (ac_price + 2500) * count;
            break;
        default:
            cout << "Invalid class type selected.\n";
            return cal(ac_price, sleeper_price, count);
        }
        break;
    default:
        cout << "Invalid class selected.\n";
        return cal(ac_price, sleeper_price, count);
    }

    return total + (total * 0.10); // 10% GST
}

void details(int k) {
    for (int i = 1; i <= k; i++) {
        string name, gen;
        int age;
        cout << "\nEnter Passenger " << i << " Name: ";
        getline(cin, name);
        cout << "Enter Gender: ";
        getline(cin, gen);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        add_node(name, gen, age);
    }
}

void add_node(const string& name, const string& gen, int age) {
    auto new_node = make_shared<Node>();
    new_node->name = name;
    new_node->gen = gen;
    new_node->age = age;
    new_node->link = nullptr;

    if (!start)
        start = new_node;
    else {
        auto temp = start;
        while (temp->link)
            temp = temp->link;
        temp->link = new_node;
    }
}

void display_seat_matrix() {
    cout << "\n------------------ SEAT MATRIX (1-60) ------------------\n";
    cout << "(XX = Booked)\n\n";
    for (int i = 1; i <= 60; i++) {
        if (booked_seats[i])
            cout << "XX ";
        else
            cout << setw(2) << setfill('0') << i << " ";
        if (i % 5 == 0) cout << "\n";
    }
    cout << "--------------------------------------------------------\n";
}

int seat(int p) {
    cout << "\n==================== BOOK YOUR SEATS ====================\n";

    for (int i = 0; i < p; i++) {
        int s;
        while (true) {
            display_seat_matrix();
            cout << "Choose seat for Passenger " << i + 1 << ": ";
            cin >> s;
            if (s >= 1 && s <= 60 && booked_seats[s] == 0) {
                booked_seats[s] = 1;
                passenger_seats.push_back(s);
                break;
            } else {
                cout << "Seat unavailable or invalid. Try again.\n";
            }
        }
    }

    return 0;
}

void bill(int fare, int count) {
    auto ptr = start;
    cout << "\n====================== TICKET SUMMARY ======================\n";
    for (int i = 0; i < count && ptr != nullptr; i++) {
        cout << "\nPassenger " << i + 1 << ":\n";
        cout << "Name      : " << ptr->name << "\n";
        cout << "Gender    : " << ptr->gen << "\n";
        cout << "Age       : " << ptr->age << "\n";
        ptr = ptr->link;
    }

    cout << "\nJourney Details:\n";
    cout << "From            : " << source << "\n";
    cout << "To              : " << des << "\n";
    cout << "Boarding From   : " << station << "\n";
    cout << "Train           : " << train << "\n";
    cout << "Class           : " << cla << "\n";
    cout << "Departure Time  : " << setfill('0') << setw(2) << time1 << ":" << setw(2) << time2 << "\n";
    cout << "Total Fare      : Rs. " << fare << "\n";

    cout << "\nAllocated Seats: ";
    for (int seat : passenger_seats)
        cout << setw(2) << setfill('0') << seat << " ";
    cout << "\n============================================================\n";
    cout << "        THANK YOU FOR BOOKING!\n";
    cout << "============================================================\n";
}

void clear_data() {
    // Clear passenger linked list
    start = nullptr;
    // Clear seat assignments for the session
    passenger_seats.clear();
}
