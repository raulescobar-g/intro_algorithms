#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using namespace std;

Course::Course(std::string id, std::string title, Date startTime, Date endTime):
id(id),title(title),startTime(startTime),endTime(endTime){
}

std::string Course::getID(){
    return id;
}
std::string Course::getTitle(){
    return title;
}
Date Course::getStartTime(){
    return startTime;
}
Date Course::getEndTime(){
    return endTime;
}
  

void Course::addAttendanceRecord(AttendanceRecord ar){
    if ((ar.getDate()).getTime() >= startTime.getTime() && (ar.getDate()).getTime() <= endTime.getTime()){
        attendanceRecords.push_back(ar);
    }
    else{
        cout <<"did not save this record.\n";
    }
}

void Course::outputAttendance(){
    if (attendanceRecords.size() == 0){
        cout <<"No Records\n";
    }
    for (int i = 0; i < attendanceRecords.size(); ++i){
        string a = (attendanceRecords[i].getDate()).getDate();
        string c = (attendanceRecords[i].getDate()).getTime();
        cout << a <<' ' <<c <<','<< attendanceRecords[i].getCourseID()<<','<< attendanceRecords[i].getStudentID()<<endl;
    }
}
void Course::outputAttendance(std::string student_id){
    int count = 0;
    if (attendanceRecords.size() == 0){
        cout <<"No Records\n";
    }
    for (int i = 0; i < attendanceRecords.size(); ++i){
        if (student_id == attendanceRecords[i].getStudentID()){
            count += 1;
            string a = (attendanceRecords[i].getDate()).getDateTime();
            cout << a <<','<< attendanceRecords[i].getCourseID()<<','<< attendanceRecords[i].getStudentID()<<endl;
        }
    }
    if (count == 0){
        cout <<"No Records\n";
    }
    
}

