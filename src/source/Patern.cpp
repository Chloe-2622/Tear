#include "Patern.h"
#include "iostream"
#include "vector"
#include <sstream>
#include <string>

using namespace std;

Patern::Patern(const pugi::xml_node& node) :
    id{ node.attribute("id").as_int() },
    name{ node.attribute("name").as_string() }
{
    cout << "Loading patern: " << node.attribute("name").as_string() << "\n";

    for (pugi::xml_node tear : node.children()) {

        if (tear.name() == "Tear"s) {
            tears.push_back(make_unique<Tear>(tear));
        }
        // if (tear.name() == "Guided_Tear"s) {
        //     tears.push_back(make_unique<Guided_Tear>(tear));
        // }

        if (!tears.empty()) {
            double compar_x = tears.back()->getPosition().x + tears.back()->getSize().x;
            if (compar_x > size.x) { size.x = compar_x; }

            double compar_y = tears.back()->getPosition().y + tears.back()->getSize().y;
            if (compar_y > size.y) { size.y = compar_y; }
        }
    }
    cout << "Loading successful with " << tears.size() << " tears" << endl;
}

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

std::string Patern::dump(std::string indent) const {
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
