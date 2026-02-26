#include "allFunc.h"

int main(){
    int login;
    cout << "Would you like to log-in as a/an...?\n";
    cout << "[1] admin, [2] user :";
    cin >> login;
    
    if(login==1){
        Admin admin;
        if(admin.adminlogin()) adminMenu();
        else cout << "Wrong password\n";
    } else if (login==2){
        seat a;
        User b;
        Cinema c;

        b.showMovieList(c);
        int choice = b.selectMovie(c);
        a.movie = choice;
        b.showShowtime(c, choice);
        b.selectShowTime(c, choice);

        showSeatPlan(a);
        cout << "Select your seat\n Enter row: ";
        cin >> a.row;
        cout << "Enter column: ";
        cin >> a.col;

        while (true){
            if (isSeatAvailable(a)){
                cout << "Seat available\n";
                bookSeat(a);
                cout << "Booking successful\n";
                break;
            } else {
                cout << "Seat not available\n";
                cout << "Please enter new seat: ";
                cin >> a.row >> a.col;
            }
        }

        double price = calculatePrice(a);
        showReceipt(a, price);

    }
}