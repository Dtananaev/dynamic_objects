
#include "data_loader.h"
namespace dynamic_objects
{

    DataLoader::DataLoader()
    {
    }

    DataLoader::~DataLoader()
    {
    }
    void DataLoader::get_sorted_files_with_ext(const std::string &dir, const std::string &ext, std::vector<std::string> &ret)
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

    bool DataLoader::load_image(const std::string &filename, std::vector<uint8_t> &image, int &height, int &width)
    {
        image.clear();
        // Open a file
        FILE *fp = fopen(filename.c_str(), "r");
        if (fp)
        {

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

            width = png_get_image_width(pngptr, pnginfo);
            height = png_get_image_height(pngptr, pnginfo);
            png_byte color_type = png_get_color_type(pngptr, pnginfo);
            png_byte bit_depth = png_get_bit_depth(pngptr, pnginfo);
            png_set_palette_to_rgb(pngptr);

            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width * 3; j += 3)
                {
                    image.push_back(static_cast<uint8_t>(rows[i][j]));
                    image.push_back(static_cast<uint8_t>(rows[i][j + 1]));
                    image.push_back(static_cast<uint8_t>(rows[i][j + 2]));
                }
            }
            return true;
        }
        return false;
    }

    bool DataLoader::load_lidar(const std::string &filename, std::vector<geometry_msgs::Point32> &lidar, std::vector<float> &intensities)
    {
        lidar.clear();
        intensities.clear();
        std::ifstream input(filename, std::ios::binary);
        if (input.is_open())
        {

            for (size_t i = 0; input.good() && !input.eof(); ++i)
            {
                geometry_msgs::Point32 point;
                float intensity;
                input.read((char *)&point.x, 3 * sizeof(float));
                input.read((char *)&intensity, sizeof(float));
                lidar.push_back(point);
                intensities.push_back(intensity);
            }
            input.close();
            return true;
        }
        return false;
    }
    bool DataLoader::load_bboxes(const std::string &filename, std::vector<dynamic_objects::CwhlyBox> &boxes)
    {
        boxes.clear();
        std::ifstream input(filename);

        if (input.is_open())
        {
            std::string line;
            while (std::getline(input, line))
            {
                std::istringstream iss(line);
                float x, y, z, w, l, h, yaw;
                int label;
                iss >> x >> y >> z >> w >> l >> h >> yaw >> label;
                CwhlyBox b(x, y, z, w, l, h, yaw, label);
                boxes.push_back(b);
            }
            input.close();
            return true;
        }
        return false;
    }

} // namespace dynamic_objects