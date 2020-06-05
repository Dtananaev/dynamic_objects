#ifndef DYNAMIC_OBJECTS_DATA_TYPES_H
#define DYNAMIC_OBJECTS_DATA_TYPES_H
#include <geometry_msgs/Point32.h>
#include <vector>

namespace dynamic_objects
{
    struct color
    {
        color(float a_r, float a_g, float a_b) : r(a_r), g(a_g), b(a_b) {}
        float r, g, b;
    };
    typedef struct
    {
        int label = -1;
        std::vector<geometry_msgs::Point32> orientation = std::vector<geometry_msgs::Point32>(2);
        std::vector<geometry_msgs::Point32> points = std::vector<geometry_msgs::Point32>(8);
    } EightPointsBox;

    struct CwhlyBox
    {
        CwhlyBox(float a_x, float a_y, float a_z, float a_w, float a_l, float a_h, float a_yaw, int a_label) : x(a_x), y(a_y), z(a_z), w(a_w), l(a_l), h(a_h), yaw(a_yaw), label(a_label) {}
        int label;
        float x, y, z, w, l, h, yaw;
    };

} // namespace dynamic_objects

#endif //DYNAMIC_OBJECTS_DATA_TYPES_H