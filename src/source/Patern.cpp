#include <iostream>
#include <sstream>
#include "Patern.h"

using namespace std;

// Constructeur
Patern::Patern(const pugi::xml_node& node) :
    id{ node.attribute("id").as_int() },
    name{ node.attribute("name").as_string() }
{
    cout << "Loading patern: " << node.attribute("name").as_string() << "\n";

    for (pugi::xml_node tear : node.children()) {

        if (tear.name() == "Tear_Basic"s) {
            tears.push_back(make_unique<Tear_Basic>(tear));
        }
        else if (tear.name() == "Tear_Guided"s) {
            tears.push_back(make_unique<Tear_Guided>(tear));
        }
        else if (tear.name() == "Tear_River"s) {
            tears.push_back(make_unique<Tear_River>(tear));
        }

        if (!tears.empty()) {
            double compar_x = tears.back()->getPosition().x + tears.back()->getSize().x;
            if (compar_x > size.x) { size.x = compar_x; }

            double compar_y = tears.back()->getPosition().y + tears.back()->getSize().y;
            if (compar_y > size.y) { size.y = compar_y; }
        }
    }
    cout << "Loading successful with " << tears.size() << " tears" << endl;
}

// Build level
#pragma region Build level
vector<unique_ptr<Tear>> Patern::copyTears() const {

    cout << tears.size() << "\n";

    vector<unique_ptr<Tear>> newTears;
    for (const auto& tear : tears) {
        newTears.push_back(tear->copy());
    }
    return newTears;
}

double Patern::getMaxSpawnable_x(double const windowWidth) const {
    return windowWidth - size.x;
}

double Patern::getMaxSpawnable_y(double const windowLenght) const {
    return windowLenght - size.y;
}
#pragma endregion Build level

// Debug
std::string Patern::dump(std::string const& indent) const {
    std::ostringstream oss;
    oss << indent
        << "id: " << id
        << " Name: " << name
        << " Size: " << size.x << ", " << size.y << endl;
    for (auto const& tear : tears) {
        oss << tear->dump("| ");
    }
    return oss.str();
}
