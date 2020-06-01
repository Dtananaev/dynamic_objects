
#include "data_loader.h"
namespace dynamic_objects
{
    template <class T>
    void read(std::ifstream &input, std::vector<T> &v)
    {
        input.read((char *)&v[0], sizeof(T) * v.size());
    }

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
    }

    bool DataLoader::load_lidar(const std::string &filename, std::vector<geometry_msgs::Point32> &lidar, std::vector<float> &intensities)
    {
        lidar.clear();
        intensities.clear();
        std::ifstream input(filename, std::ios::binary);

        float nx;

        input.read((char *)&nx, sizeof(nx));

        vector<float> x;
        x.resize(new_nx);

        for (int i = 0; i < nx; i++)
        {
            inputFile.read((char *)&x[i], sizeof(x[i]));
        }

        //input = static_cast<float>(input);
        input.seekg(0, std::ios::end);
        size_t size = input.tellg();
        input.seekg(0, std::ios::beg);
        char *memblock = new char[size];
        memcpy(&f, &b, size * sizeof(f));
        input.read(memblock, size);
        input.close();

        float x, y, z, i;
        for (int i = 0; i < size; i += 4)
        {
            geometry_msgs::Point32 p;

            p.x = static_cast<float>(memblock[i]);
            p.y = static_cast<float>(memblock[i + 1]);
            c = input.get();
            p.z = static_cast<float>(c);
            c = input.get();
            float i = static_cast<float>(c);
            lidar.push_back(p);
            intensities.push_back(i);
        }
        //float a = static_cast<float>(c);
        //std::cout << "x" << x << " y " << y << " z " << z << " i " << i << "\n ";
        //c = input.get();
    }
    // for (int i = 0; i < size; i + 4)
    // {
    // }
}; // namespace dynamic_objects

} // namespace dynamic_objects