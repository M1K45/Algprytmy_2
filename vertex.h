#pragma once 
#include "edge.h"
#include <string>
#include <sstream>
#include <iostream>

class Vertex{
    public:
        std::string label_;
        int  index_;

        Vertex(int index): index_{index}{
            std::stringstream ss;
            ss << index;            
            label_ = ss.str();
        }   
};
