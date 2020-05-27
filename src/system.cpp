#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"


using std::map;
using std::set;
using std::size_t;
using std::string;
using std::vector;




// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes



vector<Process>& System::Processes() {
    auto pids_list = LinuxParser::Pids();
    processes_.clear();
    for (auto pid : pids_list) {
        processes_.push_back(Process(pid, sysconf(_SC_CLK_TCK)));
    }
    std::sort(processes_.begin(), processes_.end(), [](Process& p1, Process& p2) {return (p1 < p2); });
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long System::UpTime() { return LinuxParser::UpTime(); }