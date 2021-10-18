//john luzada
//04/11/19
//c++ 
//class types 
#include <iostream>
#include <cmath>
using namespace std;

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};
class Time {
public:
	int h;
	int m;
};

class Movie { 
public: 
    string title;
    Genre genre;     // only one genre per movie
    int duration;    // in minutes
};

class TimeSlot { 
public: 
    Movie movie;     // what movie
    Time startTime;  // when it starts
};

int minutesSinceMidnight(Time time) {
	int totalmin;
	totalmin = time.h * 60;        //number of hours in minutes
	totalmin = totalmin + time.m;  //number of minutes into the total
	return totalmin;
	}
int minutesUntil(Time earlier, Time later) {
	int timeone, timetwo, timediff;
	timeone = earlier.h * 60 + earlier.m;   //converting timeone into minutes
	timetwo = later.h * 60 + later.m;       //converting timetwo into minutes
	//if (timeone > timetwo) {  //10 30 - 13 40 == negative number
	//timediff = timeone - timetwo;	//finding difference by subtraction
	//}
	//else if (timetwo > timeone) {
	timediff = timetwo -timeone;  //
	//}
	return timediff;
	}

Time addMinutes(Time tyme, int bro) {
	Time Newtime;
	int total;
	total = tyme.h * 60; //converts time into total min
	total = total + tyme.m + bro; //total now holds the total amount of time 
	Newtime.h = total/60; //computes the number of hours h from new total time by dividing by 60 this number becomes h
	Newtime.m = total%60; //computes the remainder of the total amount of time which represents minutes
	return Newtime;
	}
	
void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

void printTimeSlot(TimeSlot ts) {
	Time endtime;
	int starterh = ts.startTime.h;
	int starterm = ts.startTime.m;
 	string g;
    switch (ts.movie.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;		
	}					
	endtime = addMinutes(ts.startTime, ts.movie.duration);
	int endtimeh = endtime.h;
	int endtimem = endtime.m;
	cout << ts.movie.title << " " << g << " " << "(" << ts.movie.duration << " min)" << " [starts at "<< starterh <<":" << starterm << "," << " ends by " << endtimeh << ":" << endtimem << "]";
	}
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie) {
	Time nxtmovietime;
	TimeSlot nxtmovie;
	nxtmovietime = addMinutes(ts.startTime, ts.movie.duration); //calculates the end time for the first movie this value is the startime for the next movie
	nxtmovie.movie = nextMovie; //intializes nextMovie as part of the type timeslot in the variable nxtmovie
	nxtmovie.startTime = nxtmovietime; //end time for first movie becomes starttime for next movie
	return nxtmovie;
}	
bool timeOverlap(TimeSlot ts1, TimeSlot ts2) {
	int timediff;
	bool overlap = false;
	timediff = minutesUntil(ts1.startTime, ts2.startTime);  //interval between time slots starting time
	cout << timediff << endl;
	if (timediff < 0 && ts2.movie.duration > abs(timediff)) {   //in the case where the second time slot is b4 the first resulting in a negative number
		//cout << "movie2 startime overlaps " << endl;
			overlap = true;
			return overlap;
	}
	else if (timediff == 0) {   //in the case where the times are the same its overlapping
		overlap = true;
		return overlap;
		}
	
	else if (timediff > 0 && ts1.movie.duration > timediff) {				//in the case where the first time slot is b4 the second
			overlap = true;
			return overlap; 	                // the case in which the first movies duration is longer then the time difference
		}
			                //an overlap has been found returns true
		
	
		return overlap;                         //if all cases fail there is no overlap meaning it should return false
	
}
		
	
	
int main() {
	Movie movie1 = {"FIrst movie", COMEDY, 63};
	Movie movie2 = {"wOlF of wAlL StrEeT", ACTION, 180};
	
	TimeSlot morning = {movie1, {8, 30}};  
	TimeSlot daytime = {movie2, {10, 30}}; 
	TimeSlot evening = {movie2, {16, 45}}; 
	
	
	
	scheduleAfter(morning, movie1);

	
	bool isit = timeOverlap(daytime, morning);
	cout << isit << endl;
	

	

	return 0;
}