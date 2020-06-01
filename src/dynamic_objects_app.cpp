/*
 * Author: Denis Tananaev
 * Date: 01.06.2020
 */

#include <ros/ros.h>
#include "data_loader.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamic_objects");

  std::string image_dir = "/home/denis/kitti/raw_data/2011_10_03/2011_10_03_drive_0047_sync/bboxes_image";
  ::boost::filesystem::path destination(image_dir);
  std::vector<std::string> image_list;

  dynamic_objects::DataLoader::get_sorted_files_with_ext(destination, ".png", image_list);

  std::cout << "image_list " << image_list[1] << "\n";

  //dl.load_image(image_filename);
  // while (ros::ok())
  // {
  // std::cout << "I am working!"
  //             << "\n";
  // }

  return 0;
}