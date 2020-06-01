
#ifndef DATA_LOADER_H_
#define DATA_LOADER_H_

#include <string>
#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

namespace dynamic_objects
{
    class DataLoader
    {

    public:
        DataLoader();
        ~DataLoader();
        static void get_sorted_files_with_ext(const ::boost::filesystem::path &dir, const std::string &ext, std::vector<std::string> &ret);
        static bool load_image(const std::string &filename, std::vector<float> &image);

    private:
    };

} // namespace dynamic_objects

#endif // DATA_LOADER_H_