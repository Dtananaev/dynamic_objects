
#ifndef DATA_LOADER_H_
#define DATA_LOADER_H_

#include <string>
#include <png++/png.hpp>

namespace dynamic_objects
{
    class DataLoader
    {

    public:
        DataLoader();
        ~DataLoader();
        bool load_image(std::string filename);

    private:
    };

} // namespace dynamic_objects

#endif // DATA_LOADER_H_