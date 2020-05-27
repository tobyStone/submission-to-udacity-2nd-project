#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

class Processor {
public:

    float Utilization(); // TODO: See src/processor.cpp

    // TODO: Declare any necessary private members
private:
    float utilization_;

    float IdleTime(const std::vector<float>);
    float NonIdleTime(const std::vector<float>);
};

#endif