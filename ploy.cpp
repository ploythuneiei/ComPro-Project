#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

const int MAX_MOVIE = 10;
const int OPEN_TIME = 600;   // เปิด10:00
const int CLOSE_TIME = 1440; // ปิด 24:00
const int BREAK_TIME = 30;


vector<string> movieName;
vector<double> ticketPrice;
vector<int> movieDuration;
vector< vector<int> > movieTime;

int movieCount = 0;

void addMovie();
void editTicketPrice(int movieIndex);
void addShowtime(int movieIndex);
void printTime(int minute);

bool adminlogin(){
    string pass = "DoBeforeDebug";
    string input;
    cout << "Please enter password :";
    cin >> input;
    if(input == pass) return true;
    else return false;
}

int selectMovieForAdmin(){
    if(movieCount == 0){
        cout << "No movie available\n";
        return -1;
    }

    for(int i = 0; i < movieCount; i++){
        cout << i+1 << ". " << movieName[i] << endl;
    }

    int choice;
    cout << "Select movie: ";
    cin >> choice;

    if(choice < 1 || choice > movieCount){
        cout << "Invalid choice\n";
        return -1;
    }

    return choice - 1;
}


void adminMenu(){
    int input;
    do{
        cout << "Please choose menu\n";
        cout << "1.Add movie\n2.Edit ticket price\n3.Add showtime\n4.Log out\n";
        cin >> input;
    }while(input < 1 || input > 4);

    if(input == 1){
        addMovie();
    }
    else if(input == 2){
        int idx = selectMovieForAdmin();
        if(idx != -1) editTicketPrice(idx);
    }
    else if(input == 3){
        int idx = selectMovieForAdmin();
        if(idx != -1) addShowtime(idx);
    }
    else{
        return;
    }
}


void addMovie(){

    if(movieCount >= MAX_MOVIE){
        cout << "Cannot add more movies\n";
        return;
    }

    string name;
    double price,duration;

    cout << "Enter movie name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter ticket price: ";
    cin >> price;

    cout << "Enter movie duration(minutes): ";
    cin >> duration;


    movieName.push_back(name);
    ticketPrice.push_back(price);
    movieDuration.push_back(duration);
    movieTime.push_back(vector<int>());

    movieCount++;

    cout << "Movie added successfully\n";

    int movieIndex = movieCount - 1;
    cout << "Movie added at index " << movieIndex << endl;

    addShowtime(movieIndex);
}

void editTicketPrice(int movieIndex){

    if(movieIndex < 0 || movieIndex >= movieCount){
        cout << "Invalid movie index\n";
        return;
    }

    double price;
    cout << "Please input new ticket price: ";
    cin >> price;

    ticketPrice[movieIndex] = price;

    cout << "Ticket price updated successfully\n";
}

void addShowtime(int movieIndex){
    movieTime[movieIndex].clear();

    int currentTime = OPEN_TIME;

    while(currentTime + movieDuration[movieIndex] + BREAK_TIME <= CLOSE_TIME){
        movieTime[movieIndex].push_back(currentTime);
        currentTime = currentTime + movieDuration[movieIndex] + BREAK_TIME;
    }

    cout << "Showtimes added: \n";
    for(int i = 0; i < movieTime[movieIndex].size(); i++){
        int minute = movieTime[movieIndex][i];
        printTime(minute);
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
    if(adminlogin()){
        adminMenu();
    }
    else{
        cout << "Wrong password\n";
    }
    return 0;
}

