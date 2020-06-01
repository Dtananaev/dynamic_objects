/*
 * Author: Denis Tananaev
 * Date: 01.06.2020
 */

#include "data_loader.h"
#include "data_streamer.h"
#include <geometry_msgs/Point32.h>
#include <sensor_msgs/ChannelFloat32.h>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "dynamic_objects");

  std::string image_dir = "/home/denis/kitti/raw_data/2011_10_03/2011_10_03_drive_0047_sync/bboxes_image";
  std::string lidar_dir = "/home/denis/kitti/raw_data/2011_10_03/2011_10_03_drive_0047_sync/velodyne_points/data";

  std::vector<std::string> image_list;
  std::vector<std::string> lidar_list;
  dynamic_objects::DataLoader::get_sorted_files_with_ext(image_dir, ".png", image_list);
  dynamic_objects::DataLoader::get_sorted_files_with_ext(lidar_dir, ".bin", lidar_list);

  int width = 0;
  int height = 0;
  std::vector<uint8_t> image;
  std::vector<geometry_msgs::Point32> lidar;
  std::vector<sensor_msgs::ChannelFloat32> intensities;

  dynamic_objects::DataStreamer streamer;
  ros::Rate loop_rate(10);
  for (int i = 0; i < image_list.size(); ++i)
  {
    if (ros::ok())
    {
      // load image
      //std::string image_path = image_dir + "/" + image_list[i];
      //dynamic_objects::DataLoader::load_image(image_path, image, height, width);
      // load lidar
      std::string lidar_path = lidar_dir + "/" + lidar_list[i];
      std::cout << "lidar_path " << lidar_path << '\n';
      dynamic_objects::DataLoader::load_lidar(lidar_path, lidar, intensities);

      // Publish
      //streamer.publish_image(image, height, width);
      streamer.publish_lidar(lidar, intensities);
      ros::spinOnce();
      loop_rate.sleep();
    }
  }
  return 0;
}