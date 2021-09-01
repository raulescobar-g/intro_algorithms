#include <string>
#include "AttendanceRecord.h"
#include "Date.h"

using namespace std;


AttendanceRecord::AttendanceRecord(std::string course_id, std::string student_id, Date time) : 
course_id(course_id),student_id(student_id),time(time){
}
std::string AttendanceRecord::getCourseID(){
    return course_id;
}
std::string AttendanceRecord::getStudentID(){
    return student_id;
}

Date AttendanceRecord::getDate(){
    return time;
}

