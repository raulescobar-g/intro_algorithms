#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"
using namespace std;

void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
      students.push_back(Student(uin, name));
    }
  }
}
void School::addCourses(std::string filename){
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    if (ifs.fail()){
      break;
    }
    istringstream ss(line);
    string id;
    getline(ss, id, ',');
    
    string sHour;
    string sMin;
    getline(ss,sHour,':');
    getline(ss,sMin,',');
    int sHourInt = stoi(sHour);
    int sMinInt = stoi(sMin);
    Date startTime(sHourInt,sMinInt);
    
    string eHour;
    string eMin;
    getline(ss,eHour,':');
    getline(ss,eMin,',');
    int eHourInt = stoi(eHour);
    int eMinInt = stoi(eMin);
    Date endTime(eHourInt,eMinInt);
    
    string title;
    getline(ss,title);
    if (!ss.fail()) {
      courses.push_back(Course(id,title,startTime,endTime));
    }
  }
}
void School::addAttendanceData(std::string filename){
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof() || !ifs.fail()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string year;
    string month;
    string day;
    string hour;
    string minute;
    string second;
    getline(ss, year, '-');
    getline(ss, month, '-');
    getline(ss, day, ' ');
    getline(ss, hour, ':');
    getline(ss, minute, ':');
    getline(ss, second,',');
    if (ss.fail()){
      break;
    }
    int iyear = stoi(year);
    int imonth = stoi(month);
    int iday = stoi(day);
    int ihour = stoi(hour);
    int iminute = stoi(minute);
    int isecond = stoi(second);

    //debug
    //cout<< iyear<<'-'<<imonth<<'-'<<iday<<' '<<ihour<<':'<<iminute<<':'<<isecond<<endl;
    Date time(iyear,imonth,iday,ihour,iminute,isecond);
    string course_id;
    getline(ss,course_id,',');
    string student_id;
    getline(ss,student_id);

    if (!ss.fail()){
      for (int i = 0; i < courses.size(); ++i){ 
        if (courses[i].getID() == course_id){
          AttendanceRecord ar(course_id,student_id,time);
          courses[i].addAttendanceRecord(ar); 
        }
      }
    }

  }
    
}
    


void School::listCourses(){
  if (courses.size() == 0){
    cout<<"No Courses"<<endl;
  }
  for (int i = 0; i < courses.size();++i){
    string a = (courses[i].getStartTime()).getTime(false);
    string b = (courses[i].getEndTime()).getTime(false);
    cout << courses[i].getID()<<','<< a <<','<< b <<","<<courses[i].getTitle()<<endl;
  }
}
void School::listStudents(){
  if (students.size() == 0){
    cout <<"No Students"<<endl;
  }
  for (int i = 0; i < students.size();++i){
    cout <<students[i].get_id()<<','<<students[i].get_name()<<endl;
  }
}
void School::outputCourseAttendance(std::string course_id){
  if (courses.size() == 0){
    cout << "No records"<<endl;
  }
  for (int i = 0; i < courses.size(); ++i){
    if (courses[i].getID() == course_id){
      courses[i].outputAttendance();
    }
  }
}
void School::outputStudentAttendance(std::string student_id, std::string course_id){
  if (courses.size() == 0){
    cout << "No records"<<endl;
  }
  for (int i = 0; i < courses.size(); ++i){
    if (courses[i].getID() == course_id){
      courses[i].outputAttendance(student_id);
    }
  }
}

