#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>
#include<vector>
using namespace std;

int row=7,col=7;
bool seats[10][10][7][7];

const int MAX_MOVIE = 10;
const int OPEN_TIME = 600;   // เปิด10:00
const int CLOSE_TIME = 1440; // ปิด 24:00
const int BREAK_TIME = 30; // พัก 30 นาที

vector<Movie> movies;

struct seat{
    int movie;
    int showtime;
    int row;
    int col;
    bool booked=false; //true=จองแล้ว, false=ว่าง
};

class Movie{
    public:
        string title;
        double ticketPrice;
        int duration;
        string Showtime[5];
        vector<int> showtimes;
        int timecount=0;
        void Display();
        seat seats;
};

class Cinema{
    public:
        Movie allMovie[10];
        int movieCount=0;
        void showMovie();
};

class User{
    public:
    int UserShowTimeIdx;
    int UserMovieIdx;
    void showMovieList(Cinema &c);
    int selectMovie(Cinema &c);
    void showShowtime(Cinema &c,int movieIdx);
    int selectShowTime(Cinema &c,int movieIdx);
    int countShowtime(Cinema &c,int movieIdx);
    void booking(Cinema &c);
};

class Admin{
    private:
        const string pass = "DoBeforeDebug";

    public:
        bool adminlogin();
};

bool Admin::adminlogin(){
    string input;
    cout << "Please enter password :";
    cin >> input;
    if(input == pass) return true;
    else return false;
}

int selectMovieForAdmin(){
    if(movies.size() == 0){
        cout << "No movie available\n";
        return -1;
    }

    for(int i = 0; i < movies.size(); i++){
        cout << i+1 << ". " << movies[i].title << endl;
    }

    int choice;
    cout << "Select movie: ";
    cin >> choice;

    if(choice < 1 || choice > movies.size()){
        cout << "Invalid choice\n";
        return -1;
    }

    return choice - 1;
}

void addMovie(){
    if(movies.size() >= MAX_MOVIE){
        cout << "Cannot add more movies\n";
        return;
    }

    Movie m;
    cout << "Enter movie index: ";
    cin >> m.seats.movie;
    cout << "Enter movie title: ";
    getline(cin >> ws, m.title);
    cout << "Enter ticket price: ";
    cin >> m.ticketPrice;
    cout << "Enter movie duration(minutes): ";
    cin >> m.duration;
    movies.push_back(m);
    cout << "Movie added successfully\n";
    addShowtime(movies.size() - 1);
    resetSeat(m.seats);
}

void editTicketPrice(int movieIndex){

    if(movieIndex < 0 || movieIndex >= movies.size()){
        cout << "Invalid movie index\n";
        return;
    }

    double price;
    cout << "Please input new ticket price: ";
    cin >> price;

    movies[movieIndex].ticketPrice = price;

    cout << "Ticket price updated successfully\n";
}

void addShowtime(int movieIndex){
    movies[movieIndex].showtimes.clear();

    int currentTime = OPEN_TIME;

    while(currentTime + movies[movieIndex].duration + BREAK_TIME <= CLOSE_TIME){
        movies[movieIndex].showtimes.push_back(currentTime);
        currentTime = currentTime + movies[movieIndex].duration + BREAK_TIME;
    }

    cout << "Showtimes added: \n";
    for(int i = 0; i < movies[movieIndex].showtimes.size(); i++){
        printTime(movies[movieIndex].showtimes[i]);
        cout << endl;
    }
}

void printTime(int minute){
    int hour = minute / 60;
    int min = minute % 60;

    if(min < 10)
        cout << hour << ":0" << min;
    else
        cout << hour << ":" << min;
}

void adminMenu(){
    while(true){
        int input;
        cout << "1.Add movie\n2.Edit ticket price\n3.Add showtime\n4.Log out\n";
        cin >> input;

        if(input == 1) addMovie();
        else if(input == 2){
            int idx = selectMovieForAdmin();
            if(idx != -1) editTicketPrice(idx);
        }
        else if(input == 3){
            int idx = selectMovieForAdmin();
            if(idx != -1) addShowtime(idx);
        }
        else break;
    }
}

void Movie::Display(){
    cout<<"Title: "<<title<<"\n";
    cout<<"Duration: "<<duration<<" minutes\n";
    cout<<"-----------------------------------\n";
}

void Cinema::showMovie(){
    cout<<"================================\n";
    cout<<"========== MOVIE LIST ==========\n";
    cout<<"================================\n";

    if(movieCount==0){
        cout<<"No movies avaliable :(\n";
        cout<<"-----------------------------------\n";
        return;
    }

    for(int i=0;i<movieCount;i++){
        cout<<"Movie #"<<i+1<<"\n";
        cout<<"-----------------------------------\n";
        allMovie[i].Display();
    }
    return;
}

void User::showMovieList(Cinema &c){
    c.showMovie();
}

int User::selectMovie(Cinema &c){
    int choice;
    cout<<"Select movie number: \n";
    cin>>choice;
    choice--;

    while(choice<0||choice>=c.movieCount){
        cout<<"Invalid selection. Try again: \n";
        cin>>choice;
        choice--;
    }
    return choice;
}

void User::showShowtime(Cinema &c,int movieIdx){
    Movie &m=c.allMovie[movieIdx];
    
    for(int i=0;i<m.timecount;i++){
        cout<<"round["<<i+1<<"] "<<m.Showtime[i]<<"\n";
    }
}

int User::selectShowTime(Cinema &c,int movieIdx){
    Movie &m=c.allMovie[movieIdx];
    int choice;
    
    cout<<"Select showtime:\n";
    cin>>choice;
    choice--;
    while(choice<0||choice>=m.timecount){
        cout<<"Invalid showtime. Try again: \n";
        cin>>choice;
        choice--;
    }
    return choice;
}

void resetSeat(seat a){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            seats[a.movie][a.showtime][i][j]=false;
        }
    }
}

void showSeatPlan(seat a){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(!seats[a.movie][a.showtime][i][j]) cout << "O ";
            else cout << "X ";
        }
        cout << endl;
    }
}

bool isSeatAvailable(seat a){
    if (a.row < 0 || a.row >= row) return false;
    if (a.col < 0 || a.col >= col) return false;

    if (seats[a.movie][a.showtime][a.row][a.col] == false)
        return true;
    else
        return false;
}

void bookSeat(seat &a){
    seats[a.movie][a.showtime][a.row][a.col] = true;
    a.booked = true;
}

int showBookingSum(seat a){
    int available=0,booked=0;
    for(int i=0;i<row*col;i++){
        for(int j=0;j<col;j++){
            if(!seats[a.movie][a.showtime][i][j]) available+=1;
            else booked+=1;
        }
    }
    return booked;
}

double calculatePrice(seat a){
    Movie m;
    int amount = showBookingSum(m.seats);
    return (double) m.ticketPrice * amount;
}

void showReceipt(seat a, double price){
    double total;

    if (a.booked == true){
        total = price;

        cout << "----------- RECEIPT -----------\n";
        cout << "Movie No     : " << a.movie << endl;
        cout << "Showtime     : " << a.showtime << endl;
        cout << "Seat         : Row " << a.row << ", Column " << a.col << endl;
        cout << "Ticket Price : " << price << " Baht" << endl;
        cout << "Total Price  : " << total << " Baht" << endl;
        cout << "-------------------------------\n";
    }
    else{
        cout << "No booking information found.\n";
    }
}