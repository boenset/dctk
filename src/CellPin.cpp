// CellLib
//
// A CellLib is a library of Cells
//

#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

#include "CellPin.hpp"

namespace dctk {

CellPin::CellPin(const std::string& s) {
    _name = s;
    _rise_capacitance = std::numeric_limits<float>::quiet_NaN();
    _rise_capacitance_range_min = std::numeric_limits<float>::quiet_NaN();
    _rise_capacitance_range_max = std::numeric_limits<float>::quiet_NaN();
    _fall_capacitance = std::numeric_limits<float>::quiet_NaN();
    _fall_capacitance_range_min = std::numeric_limits<float>::quiet_NaN();
    _fall_capacitance_range_max = std::numeric_limits<float>::quiet_NaN();
}

void CellPin::add_arc(CellArc* a) {
    _arcs.push_back(a);
}

CellArc* CellPin::find_arc(const std::string& input_pin) {

    std::vector<CellArc*>::iterator iter = _arcs.begin();
    std::vector<CellArc*>::iterator iterEnd = _arcs.end();

    // return first arc for which related_pin == input_pin
    for ( ; iter != iterEnd; iter++) {
        CellArc* arc = *iter;
        if (arc->get_related_pin()->get_name() == input_pin) {
            return arc;
        }
    }

    // arc doesn't exist
    return nullptr;
}

void CellPin::dump() {
    std::cout << "    Pin Name = " << this->_name << std::endl;

    // print out all the cells that exist

    std::vector<dctk::CellArc*>::iterator it;

    for (it = this->_arcs.begin(); it != this->_arcs.end(); it++) {
        (*it)->dump();
    }

}

CellArc* CellPin::get_random_arc() {
    // find a random arc attached to that output pin

    if (_arcs.size() == 0) {
        return (nullptr);
    }
    size_t index = rand() % _arcs.size();
    return _arcs[index];

}

float CellPin::get_max_pin_cap() {
    float retval = 0.0;

    if (!std::isnan(_rise_capacitance)) {
        retval = std::max(retval, _rise_capacitance);
    }
    if (!std::isnan(_fall_capacitance)) {
        retval = std::max(retval, _fall_capacitance);
    }
    if (!std::isnan(_rise_capacitance_range_max)) {
        retval = std::max(retval, _rise_capacitance_range_max);
    }
    if (!std::isnan(_fall_capacitance_range_max)) {
        retval = std::max(retval, _fall_capacitance_range_max);
    }

    return retval;
    
}

float CellPin::get_min_pin_cap() {
    float retval = std::numeric_limits<double>::infinity();

    if (!std::isnan(_rise_capacitance)) {
        retval = std::min(retval, _rise_capacitance);
    }
    if (!std::isnan(_fall_capacitance)) {
        retval = std::min(retval, _fall_capacitance);
    }
    if (!std::isnan(_rise_capacitance_range_min)) {
        retval = std::min(retval, _rise_capacitance_range_min);
    }
    if (!std::isnan(_fall_capacitance_range_min)) {
        retval = std::min(retval, _fall_capacitance_range_min);
    }

    return retval;
    
}

}
