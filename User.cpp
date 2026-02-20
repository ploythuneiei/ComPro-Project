#include<iostream>
#include<string>
#include <iomanip>
#include<vector>
using namespace std;

class Movie{
    public:
        string title;
        string genre;
        int duration;
        string Showtime[5];
        int timecount=0;

        void Display();
};

class Cinema{
    public:
        Movie allMovie[10];
        int movieCount=0;
        void showMovie();

};

class User{
    public:

    string userName;
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
    cout<<"Genre: "<<genre<<"\n";
    cout<<"Duration: "<<duration<<" minutes\n";
    cout<<"-----------------------------------\n";
    cout<<"Showtimes:\n";
    for(int i=0;i<timecount;i++){
        cout<<"["<<i+1<<"]"<<Showtime[i]<<"\n";
    }
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
    cout<<"Select movie numbet: \n";
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

int User::countShowtime(Cinema &c,int movieIdx){
    return c.allMovie[movieIdx].timecount;
    
}

void User::booking(Cinema &c){

    if(c.movieCount==0){
        cout<<"No movies available.\n";
        return;
    }

    cin.ignore();
    cout<<"Enter your name: ";
    getline(cin,userName);
    showMovieList(c);

    UserMovieIdx=selectMovie(c);
    if(countShowtime(c,UserMovieIdx)==0){
        cout<<"No showtime avaliable.\n";
        return;
    }

    showShowtime(c,UserMovieIdx);
    UserShowTimeIdx=selectShowTime(c,UserMovieIdx);
    
    cout<<"\n========== BOOKING ==========\n";
    cout<<"Name: "<<userName<<"\n";
    cout<<"Movie: "<<c.allMovie[UserMovieIdx].title<<"\n";
    cout<<"Genre: "<<c.allMovie[UserMovieIdx].genre<<"\n";
    cout<<"Duration(min): "<<c.allMovie[UserMovieIdx].duration<<"\n";
    cout<<"Show time: "<<c.allMovie[UserMovieIdx].Showtime[UserShowTimeIdx]<<"\n";
    cout<<"===============================\n";
}


