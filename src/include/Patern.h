#pragma once

#include "pugixml.hpp"
#include "Tear.h"
#include "Guided_Tear.h"

class Patern {
public :
    explicit Patern(const pugi::xml_node& node);

    std::vector<std::unique_ptr<Tear>>      copyTears() const;
    double                                  getMaxSpawnable_x(double const windowWidth) const;
    double                                  getMaxSpawnable_y(double const windowLenght) const;
    std::string                             dump(std::string indent = "") const;

private :
    int                                     id;
    std::string                             name;
    Vector2                                 size = { 0, 0 };
    std::vector<std::unique_ptr<Tear>>      tears;
};