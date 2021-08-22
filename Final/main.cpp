#include <iostream>
#include <string>
#include <set>
#include <map>
#include <stdexcept>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
    Date(int new_year = 0, int new_month = 1, int new_day = 1){
        year = new_year;
        month = new_month;
        day = new_day;
    }

    int GetYear() const{
        return year;
    }
    int GetMonth() const{
        return month;
    }
    int GetDay() const{
        return day;
    }

private:
    int year;
    int month;
    int day;
};

istream& operator>> (istream& is, Date& d){
    int year, month, day;
    char c1, c2;
    //cout << "in << operator" << endl;
    is >> year >> c1 >> month >> c2 >> day;
    //cout << year << '-' << month << '-' << month << endl;

    if (c1 == c2 == '-')
        throw runtime_error("Wrong date format: " + year +
                            c1 + month + c2 + day);
    if (month < 1 || month > 12)
        throw runtime_error("Month value is invalid: " + month);

    if (day < 1 || day > 31)
        throw runtime_error("Day value is invalid: " + day);

    d = Date(year, month, day);

    return is;
}

ostream& operator<< (ostream& os, Date d){
    os << setw(4) << setfill('0') << d.GetYear() << '-' <<
    setw(2) << setfill('0') << d.GetMonth() << '-' <<
    setw(2) << setfill('0') << d.GetDay();
    return os;
}

bool operator< (const Date& lhs, const Date& rhs){
    if (lhs.GetYear() != rhs.GetYear())
        return lhs.GetYear() < rhs.GetYear();
    if (lhs.GetMonth() != rhs.GetMonth())
        return lhs.GetMonth() < rhs.GetMonth();
    return lhs.GetDay() < rhs.GetDay();
}

class Database {
public:
    void AddEvent(const Date& date, const string& event){
        dataBase[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event){
        if (dataBase[date].count(event) == 0)
            cout << "Event not found" << endl;
        else {
            dataBase[date].erase(event);
            cout << "Deleted successfully" << endl;
        }
    }

    int  DeleteDate(const Date& date){
        if (dataBase.count(date) == 0) {
            cout << "Deleted 0 events" << endl;
            return 0;
        }
        else{
            int N_events = dataBase[date].size();
            dataBase.erase(date);
            cout << "Deleted " << N_events << " events" << endl;
            return N_events;
        }


    }

    void Find(const Date& date) const{
        for (const string& event: dataBase.at(date)){
            cout << event << endl;
        }
    }

    void Print() const{
        for (const auto& item: dataBase){
            for (const string& event: item.second){
                cout << item.first << ' ' << event << endl;
            }
        }
    }

private:
    map<Date, set<string>> dataBase;
};

bool verifyCommand(string command){
    if (command == "Add" || command == "Del" ||
        command == "Print" || command == "Find" ||
        command == "")
        return true;
    return false;
}

int main() {
    Database db;

    string line;
    while (getline(cin, line)) {
        stringstream stream(line);
        string command;
        stream >> command;
        //cout << "Command is: " << command << endl;
        if (verifyCommand(command)) {
            if (command == "Print")
                db.Print();
            else if  (command == "Find"){
                Date date;
                stream >> date;
                db.Find(date);
            }else if (command == "Del"){
                Date date;
                stream >> date;
                if (stream.peek() > 0){
                    string event;
                    stream >> event;
                    db.DeleteEvent(date, event);
                } else{
                    //cout << "In Delete Date branch" << endl;
                    db.DeleteDate(date);
                }
            }else if (command == "Add"){
                Date date;
                string event;
                stream >> date >> event;
                db.AddEvent(date, event);
            }

        }else
            cout << "Unknown command: " << command << endl;
    }

    return 0;
}