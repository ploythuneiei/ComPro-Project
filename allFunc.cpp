#include "allFunc.h"

int main(){
    seat a;
    User b;
    Cinema c;
    b.showMovieList(c);
    int choice = b.selectMovie(c);
    b.showShowtime(c, choice);
    b.selectShowTime(c, choice);

    showSeatPlan(a);
    cout << "Select seat: ";
    cin >> a.row >> a.col;

    while (true){
    if (isSeatAvailable(a)){
        cout << "Seat available\n";
        bookSeat(a);
        cout << "Booking successful\n";
        break;
    }
    else{
        cout << "Seat not available\n";
        cout << "Please enter new seat: ";
        cin >> a.row >> a.col;
    }
}
    double price = calculatePrice(a);
    showReceipt(a, price);
    
}