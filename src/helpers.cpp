#include "helpers.h"

namespace dynamic_objects
{
    void Helpers::get_color_palette(std::vector<dynamic_objects::color> &colors)
    {
        colors.clear();
        //     "Tram" : 0, "Car" : 1, "Misc" : 2, "Van" : 3, "Person_sitting" : 4, "Pedestrian" : 5, "Truck" : 6, "Cyclist" : 7
        // [[1, 0, 0], [0, 1, 0], [1, 1, 0.2], [0.4, 1, 0.7], [1, 0, 0.5], [1, 0, 1], [0, 0, 1], [1, 0.5, 0]
        colors.push_back(color(1, 0, 0));
        colors.push_back(color(0, 1, 0));
        colors.push_back(color(1, 1, 0.2));
        colors.push_back(color(0.4, 1, 0.7));
        colors.push_back(color(1, 0, 0.5));
        colors.push_back(color(1, 0, 1));
        colors.push_back(color(0, 0, 1));
        colors.push_back(color(1, 0.5, 0));
    }

} // namespace dynamic_objects