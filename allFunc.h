#include<iostream>
#include<string>
#include <iomanip>
#include<vector>
using namespace std;

int row=7,col=7;
int booked=0;
bool seats[10][10][7][7];

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
        int duration;
        string Showtime[5];
        int timecount=0;
        void Display();
};

class Cinema{
    public:
        Movie allMovie[10];
        int movieCount=0; //เชื่อมกับ vect movie ของพลอย
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
    if (a.row < 0 || a.row >= row)
        return false;

    if (a.col < 0 || a.col >= col)
        return false;

    if (a.booked == false)
        return true;
    else
        return false;
}

void bookSeat(seat &a){
    a.booked = true;
}

void showBookingSum(seat a){
    int available=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(!seats[a.movie][a.showtime][i][j]) available+=1;
            else booked+=1;
        }
    }
    cout << "Available seat: " << available << "\nBooked seat: " << booked;
}

double calculatePrice(seat a){
    showBookingSum(a);
    
}

void showReceipt(seat a, double price){
    double total;

    if (a.booked == true){
        total = price;   // คำนวณราคารวม

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