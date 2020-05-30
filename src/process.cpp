#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "processor.h"

using std::string;
using std::to_string;
using std::vector;


Process::Process(const int pid) : pid_(pid), cpuUsage_(CpuUtilization()) {}

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
// Returns a value between 0 and 1.
float Process::CpuUtilization() { 
    const std::vector<long int> processInfo = LinuxParser::Cpu(pid_);
    long int total_time = processInfo[processElements::utime_] + processInfo[processElements::stime_];
    total_time += processInfo[processElements::cutime_] + processInfo[processElements::cstime_];
    const float seconds = (float) Process::UpTime();
    const float cpuUsage = ((total_time / sysconf(_SC_CLK_TCK)) / seconds);
    return cpuUsage; 
}


/*
Process::Process(const int pid): pid_(pid), cpuUsage_(CpuUtilization()) {
    vector<string> cpuNumbers = {};
    cpuNumbers.push_back(LinuxParser::Uid(pid));

  futime_ = stof(cpuNumbers[13]);
  fstime_ = stof(cpuNumbers[14]);[](Process& p1, Process& p2){return (p1<p2) ;}
  fcutime_ = stof(cpuNumbers[15]);
  fcstime_ = stof(cpuNumbers[16]);
  fstarttime_ = stof(cpuNumbers[21]);
  return ;
  }

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
int Process::CpuUtilization() {
    const float total_time = futime_ + fstime_ + fcutime_ + fcstime_; 
    const float seconds = Process::UpTime();
    const int cpuUsage_ = static_cast<int> ((total_time / sysconf(_SC_CLK_TCK))/seconds);
    return cpuUsage_;
      }
*/
// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    return (a.cpuUsage_ < this-> cpuUsage_);
}


/*
references and input from ''Programming Principles and Practice Using C++' by Bjarne Stroustrup.
'A Tour of C++' by Bjarne Stroustrup, 'The C++ Programming Language' by Bjarne Stroustrup, CppND System Monitor by Kaushik Samba, CppND System Monitor by The Full Resolution, GeeksforGeeks website, Bjarne Stroustrop website, Udacity Messaging Board.*/

