#include<iostream>
using namespace std;

int row=7,col=7;
bool seats[10][10][7][7];

struct seat{
    int movie;
    int showtime;
    int row;
    int col;
};

void showSeatPlan(seat a){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(!seats[a.movie][a.showtime][i][j]) cout << "O ";
            else cout << "X ";
        }
        cout << endl;
    }
}

void resetSeat(seat a){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            seats[a.movie][a.showtime][i][j]=false;
        }
    }
}

void showBookingSum(seat a){
    int available=0,booked=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(!seats[a.movie][a.showtime][i][j]) available+=1;
            else booked+=1;
        }
    }
    cout << "Available seat: " << available << "\nBooked seat: " << booked;
}

void Book(seat a){          //เอามาเทสเฉยๆ
    if(!seats[a.movie][a.showtime][a.row][a.col]) seats[a.movie][a.showtime][a.row][a.col] = true;
    else cout << "The seat is not available\n";
}

int main(){
    seat a;
    cout << "select movie: ";
    cin >> a.movie;
    cout << "select showtime: ";
    cin >> a.showtime;
    resetSeat(a);
    showSeatPlan(a);
    cout << "select seat: ";
    while(cin >> a.row >> a.col){
        if(a.row!=999 || a.col!=999){
            Book(a);
            showSeatPlan(a);
            showBookingSum(a);
            cout << "\nselect seat or type 999 to exit: ";
        }else break;
    }
}
