
#include "data_loader.h"
namespace dynamic_objects
{
    DataLoader::DataLoader()
    {
    }

    DataLoader::~DataLoader()
    {
    }

    bool DataLoader::load_image(std::string filename)
    {

        png::image<png::gray_pixel_16> img(file_name.c_str(), png::require_color_space<png::gray_pixel_16>());
        int x_size = img.get_width();
        int y_size = img.get_height();
        CMatrix<ushort> depth(x_size, y_size);

        for (int y = 0; y < y_size; y++)
        {
            for (int x = 0; x < x_size; x++)
            {
                ushort s = img.get_pixel(x, y);
                ushort r = (s << 13 | s >> 3);
                depth(x, y) = r;
            }
        }
        return depth;
    }

}