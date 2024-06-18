#pragma once

#include "pugixml.hpp"
#include "Tear.h"
#include "Tear_Basic.h"
#include "Tear_Guided.h"
#include "Tear_River.h"
#include <string>
#include <vector>

class Patern {
public :
    explicit Patern(const pugi::xml_node& node);

    // Build Level
    std::vector<std::unique_ptr<Tear>>      copyTears() const;
    double                                  getMaxSpawnable_x(double const windowWidth) const;
    double                                  getMaxSpawnable_y(double const windowLenght) const;

    // Debug
    std::string                             dump(std::string const& indent = "") const;

private :
    int                                     id;
    std::string                             name;
    Vector2                                 size = { 0, 0 };
    std::vector<std::unique_ptr<Tear>>      tears;
};