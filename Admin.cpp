#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class Movie{
    public:
        string name;
        double ticketPrice;
        int duration;
        vector<int> showtimes;
};

class Admin{
    private:
        const string pass = "DoBeforeDebug";

    public:
        bool adminlogin();
};

const int MAX_MOVIE = 10;
const int OPEN_TIME = 600;   // เปิด10:00
const int CLOSE_TIME = 1440; // ปิด 24:00
const int BREAK_TIME = 30; // พัก 30 นาที

vector<Movie> movies;

void addMovie();
void editTicketPrice(int movieIndex);
void addShowtime(int movieIndex);
void printTime(int minute);

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
        cout << i+1 << ". " << movies[i].name << endl;
    }

    int choice;
    cout << "Select movie: ";
    cin >> choice;

    if(choice < 1 || choice > movies.size()
){
        cout << "Invalid choice\n";
        return -1;
    }

    return choice - 1;
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



void addMovie(){

    if(movies.size() >= MAX_MOVIE){
        cout << "Cannot add more movies\n";
        return;
    }

    Movie m;

    cout << "Enter movie name: ";
    getline(cin >> ws, m.name);


    cout << "Enter ticket price: ";
    cin >> m.ticketPrice;

    cout << "Enter movie duration(minutes): ";
    cin >> m.duration;


    movies.push_back(m);

    cout << "Movie added successfully\n";

    addShowtime(movies.size() - 1);
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

int main(){
    Admin admin;
    if(admin.adminlogin()){
        adminMenu();
    }
    else{
        cout << "Wrong password\n";
    }
    return 0;
}

