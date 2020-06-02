
#ifndef DATA_LOADER_H_
#define DATA_LOADER_H_

#include <string>
#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <cstdint>
#include <geometry_msgs/Point32.h>
#include <sensor_msgs/ChannelFloat32.h>
#include <fstream>
namespace dynamic_objects
{
    class DataLoader
    {

    public:
        DataLoader();
        ~DataLoader();
        static void get_sorted_files_with_ext(const std::string &dir, const std::string &ext, std::vector<std::string> &ret);
        static bool load_image(const std::string &filename, std::vector<uint8_t> &image, int &height, int &width);
        static bool load_lidar(const std::string &filename, std::vector<geometry_msgs::Point32> &lidar, std::vector<float> &intensities);

    private:
    };

} // namespace dynamic_objects

#endif // DATA_LOADER_H_