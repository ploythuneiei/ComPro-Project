#include <iostream>
using namespace std;

int row=5;
int col=5;

struct seat{
    int movieNo;
    double showtime;
    int row;
    int col;
    bool booked; //true=จองแล้ว, false=ว่าง
};

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

double calculatePrice(seat a){
    double price;

    if (a.movieNo == 1)
        price = 150;
    else if (a.movieNo == 2)
        price = 180;
    else if (a.movieNo == 3)
        price = 200;
    else
        price = 160;

    return price;
}


void showReceipt(seat a, double price){
    double total;

    if (a.booked == true){
        total = price;   // คำนวณราคารวม

        cout << "----------- RECEIPT -----------\n";
        cout << "Movie No     : " << a.movieNo << endl;
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


int main(){
    seat a;
    cin >> a.movieNo >> a.showtime >> a.row >> a.col;
    a.booked = false;

    if (isSeatAvailable(a)){
        cout << "Seat available\n";
        bookSeat(a);
        cout << "Booking successful\n";
        double price = calculatePrice(a);
        showReceipt(a, price);
    } else {
        cout << "Seat not available\n";
    }
}
