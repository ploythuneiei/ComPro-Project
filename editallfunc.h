#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_MOVIE = 10;

void printTime(int minute){
    int h = minute / 60;
    int m = minute % 60;
    cout << h << ":";
    if(m < 10) cout << "0";
    cout << m;
}

double calculatePrice(double ticketPrice, int seatCount){
    return ticketPrice * seatCount;
}

class Movie{
public:
    string name;
    double price;
    int duration; // นาที

    vector<int> showtimes;                         // รอบฉาย (นาที)
    vector<vector<vector<bool>>> seats;            // [รอบ][แถว][คอลัมน์]

    void generateShowtimes(){
        const int OPEN_TIME = 600;   // 10:00
        const int CLOSE_TIME = 1440; // 24:00
        const int BREAK_TIME = 30;   // พัก 30 นาที

        showtimes.clear();
        seats.clear();

        int currentTime = OPEN_TIME;
        while(currentTime + duration + BREAK_TIME <= CLOSE_TIME){
            showtimes.push_back(currentTime);
            seats.push_back(vector<vector<bool>>(7, vector<bool>(7,false)));
            currentTime += duration + BREAK_TIME;
        }
    }

    void showSeats(int showIdx){
        cout << "    ";
        for(int c = 1; c <= 7; c++){
            cout << c << " ";
        }
        cout << endl;

        cout << "  ----------------\n";

        for(int r = 0; r < 7; r++){
            cout << r + 1 << " | ";
            for(int c = 0; c < 7; c++){
                if(seats[showIdx][r][c])
                    cout << "X ";
                else
                    cout << "O ";
            }
            cout << endl;
        }
    }
};

class Cinema{
public:
    vector<Movie> movies;
};

class Admin{
private:
    const string password = "DoBeforeDebug";

public:
    bool login(){
        string p;
        cout << "Enter admin password: ";
        cin >> p;
        return p == password;
    }

    void addMovie(Cinema &c);
    void editPrice(Cinema &c);
    void editShowtime(Cinema &c);
};

int selectMovieForAdmin(Cinema &c){
    if(c.movies.empty()){
        cout << "No movies available\n";
        return -1;
    }

    for(int i = 0; i < c.movies.size(); i++){
        cout << i + 1 << ". " << c.movies[i].name << endl;
    }

    int idx;
    cout << "Select movie number: ";
    cin >> idx;
    idx--;

    if(idx < 0 || idx >= c.movies.size()){
        cout << "Invalid selection\n";
        return -1;
    }

    return idx;
}

void Admin::addMovie(Cinema &c){
    if(c.movies.size() >= MAX_MOVIE){
        cout << "Movie limit reached\n";
        return;
    }

    Movie m;
    cin.ignore();
    cout << "Movie name: ";
    getline(cin, m.name);
    cout << "Ticket price: ";
    cin >> m.price;
    cout << "Duration (minutes): ";
    cin >> m.duration;

    m.generateShowtimes();
    c.movies.push_back(m);

    cout << "Movie added successfully\n";
}

void Admin::editPrice(Cinema &c){
    int idx = selectMovieForAdmin(c);
    if(idx == -1) return;

    cout << "New ticket price: ";
    cin >> c.movies[idx].price;
    cout << "Price updated\n";
}

void Admin::editShowtime(Cinema &c){
    int idx = selectMovieForAdmin(c);
    if(idx == -1) return;

    int newDuration;
    cout << "Enter new duration (minutes): ";
    cin >> newDuration;

    c.movies[idx].duration = newDuration;
    c.movies[idx].generateShowtimes();

    cout << "Showtime updated successfully\n";
}

class User{
public:
    int selectMovie(Cinema &c);
    int selectShowtime(Movie &m);
    int selectSeats(Movie &m, int showIdx);
    void printReceipt(Movie &m, int showIdx, int seatCount);
    void booking(Cinema &c);
};

int User::selectMovie(Cinema &c){
    cout << "\n=== Movie List ===\n";
    for(int i=0;i<c.movies.size();i++)
        cout << i+1 << ". " << c.movies[i].name << endl;

    int idx;
    cout << "Select movie number: ";
    cin >> idx;
    idx--;

    if(idx < 0 || idx >= c.movies.size()){
        cout << "Invalid movie\n";
        return -1;
    }
    return idx;
}

int User::selectShowtime(Movie &m){
    cout << "\n=== Showtimes ===\n";
    for(int i=0;i<m.showtimes.size();i++){
        cout << i+1 << ". ";
        printTime(m.showtimes[i]);
        cout << endl;
    }

    int idx;
    cout << "Select showtime number: ";
    cin >> idx;
    idx--;

    if(idx < 0 || idx >= m.showtimes.size()){
        cout << "Invalid showtime\n";
        return -1;
    }
    return idx;
}

int User::selectSeats(Movie &m, int showIdx){
    int seatCount = 0;
    int r, c;

    while(true){
        cout << "\n=== Seat Plan (O=Free, X=Booked) ===\n";
        m.showSeats(showIdx);

        cout << "Select seat (Row 1-7, Column 1-7) or 0 0 to finish: ";
        cin >> r >> c;

        if(r == 0 && c == 0) break;

        r--;
        c--;

        if(r < 0 || r >= 7 || c < 0 || c >= 7){
            cout << "Invalid seat! Row and Column must be between 1 and 7.\n";
            continue;
        }

        if(m.seats[showIdx][r][c]){
            cout << "Seat already booked\n";
            continue;
        }

        m.seats[showIdx][r][c] = true;
        seatCount++;
        cout << "Seat booked! (Row " << r+1 << ", Column " << c+1 << ")\n";
    }

    return seatCount;
}

void User::printReceipt(Movie &m, int showIdx, int seatCount){
    double total = calculatePrice(m.price, seatCount);

    cout << "\n===== RECEIPT =====\n";
    cout << "Movie: " << m.name << endl;
    cout << "Time: ";
    printTime(m.showtimes[showIdx]);
    cout << endl;
    cout << "Seats booked: " << seatCount << endl;
    cout << "Ticket price: " << m.price << " Baht\n";
    cout << "Total price : " << total << " Baht\n";
    cout << "===================\n";
}

void User::booking(Cinema &c){
    if(c.movies.empty()){
        cout << "No movies available\n";
        return;
    }

    int movieIdx = selectMovie(c);
    if(movieIdx == -1) return;

    Movie &m = c.movies[movieIdx];

    int showIdx = selectShowtime(m);
    if(showIdx == -1) return;

    int seatCount = selectSeats(m, showIdx);
    if(seatCount == 0){
        cout << "No seat selected\n";
        return;
    }

    printReceipt(m, showIdx, seatCount);
}