#ifndef DYNAMIC_OBJECTS_DATA_TYPES_H
#define DYNAMIC_OBJECTS_DATA_TYPES_H
#include <geometry_msgs/Point32.h>
#include <vector>
namespace dynamic_objects
{
    typedef struct
    {
        int label = -1;
        std::vector<geometry_msgs::Point32> orientation = std::vector<geometry_msgs::Point32>(2);
        std::vector<geometry_msgs::Point32> points = std::vector<geometry_msgs::Point32>(8);
    } bbox;

} // namespace dynamic_objects

#endif //DYNAMIC_OBJECTS_DATA_TYPES_H