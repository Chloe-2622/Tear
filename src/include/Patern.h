#pragma once

#include <string>
#include <vector>
#include "pugixml.hpp"
#include "GameObjects/Tears/Tear.h"
#include "GameObjects/Tears/Tear_Basic.h"
#include "GameObjects/Tears/Tear_Guided.h"
#include "GameObjects/Tears/Tear_River.h"

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