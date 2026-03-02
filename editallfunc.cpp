#include <iostream>
#include "editallfunc.h"
using namespace std;

int main(){
    Cinema cinema;
    Admin admin;
    User user;

    int choice;
    while(true){
        cout << "Would you like to log-in as a/an...?\n";
        cout << "[1] admin, [2] user, [3] exit\nSelect:";
        cin >> choice;

        if(choice == 1){
            if(admin.login()){
                int a;
                do{
                    cout << "\n1. Add Movie\n";
                    cout << "2. Edit Ticket Price\n";
                    cout << "3. Edit Showtime\n";
                    cout << "4. Back\n";
                    cout << "Select: ";
                    cin >> a;

                    if(a == 1) admin.addMovie(cinema);
                    else if(a == 2) admin.editPrice(cinema);
                    else if(a == 3) admin.editShowtime(cinema);
                }while(a != 4);
            }else{
                cout << "Wrong password\n";
            }
        }
        else if(choice == 2){
            user.booking(cinema);
        }
        else{
            break;
        }
    }
    return 0;
}