
#include "data_loader.h"
namespace dynamic_objects
{
    DataLoader::DataLoader()
    {
    }

    DataLoader::~DataLoader()
    {
    }
    void DataLoader::get_sorted_files_with_ext(const ::boost::filesystem::path &dir, const std::string &ext, std::vector<std::string> &ret)
    {
        if (!::boost::filesystem::exists(dir) || !::boost::filesystem::is_directory(dir))
            return;

        ::boost::filesystem::recursive_directory_iterator it(dir);
        ::boost::filesystem::recursive_directory_iterator endit;
        while (it != endit)
        {

            if (::boost::filesystem::is_regular_file(*it) && it->path().extension() == ext)
            {
                ret.push_back(it->path().filename().string());
            }

            ++it;
        }
        if (ret.size() > 0)
        {
            std::sort(ret.begin(), ret.end());
        }
    }

    bool DataLoader::load_image(const std::string &filename, std::vector<float> &image)
    {
        image.clear();
        // Open a file
        FILE *fp = fopen(filename.c_str(), "r");

        // png_structp contains data, png_infop contains info
        png_structp pngptr =
            png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop pnginfo = png_create_info_struct(pngptr);
        // Convert to rgb
        // We read data from fp file
        png_init_io(pngptr, fp);
        png_bytepp rows;
        png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
        rows = png_get_rows(pngptr, pnginfo);

        int width = png_get_image_width(pngptr, pnginfo);
        int height = png_get_image_height(pngptr, pnginfo);
        png_byte color_type = png_get_color_type(pngptr, pnginfo);
        png_byte bit_depth = png_get_bit_depth(pngptr, pnginfo);
        if (color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(pngptr);
        else
        {
            std::cerr << "[DataLoader] Error: non supported color format. Supported only rgb.";
        }

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width * 3; j += 3)
            {
                image.push_back(rows[i][j]);
                image.push_back(rows[i][j + 1]);
                image.push_back(rows[i][j + 2]);
            }
        }
    }

} // namespace dynamic_objects