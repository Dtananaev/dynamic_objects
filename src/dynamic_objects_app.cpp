/*
 * Author: Denis Tananaev
 * Date: 01.06.2020
 */

#include "data_loader.h"
#include "data_streamer.h"
#include <geometry_msgs/Point32.h>
#include "data_types.h"

int main(int argc, char **argv)
{

  ros::init(argc, argv, "dynamic_objects");

  std::string image_dir = "/home/denis/kitti/raw_data/2011_09_29/2011_09_29_drive_0071_sync/bboxes_image";
  std::string lidar_dir = "/home/denis/kitti/raw_data/2011_09_29/2011_09_29_drive_0071_sync/velodyne_points/data";
  std::string bbox_dir = "/home/denis/kitti/raw_data/2011_09_29/2011_09_29_drive_0071_sync/bboxes_3d";

  std::vector<std::string> image_list;
  dynamic_objects::DataLoader::get_sorted_files_with_ext(image_dir, ".png", image_list);

  int width = 0;
  int height = 0;
  std::vector<uint8_t> image;
  std::vector<geometry_msgs::Point32> lidar;
  std::vector<float> intensities;
  std::vector<dynamic_objects::CwhlyBox> boxes;
  dynamic_objects::DataStreamer streamer;
  ros::Rate loop_rate(10);
  for (int i = 0; i < image_list.size(); ++i)
  {
    if (ros::ok())
    {
      // name
      std::string timestamp = image_list[i].substr(0, image_list[i].find("."));

      // load image
      std::string image_path = image_dir + "/" + timestamp + ".png";
      if (dynamic_objects::DataLoader::load_image(image_path, image, height, width))
        streamer.publish_image(image, height, width);

      // load lidar
      std::string lidar_path = lidar_dir + "/" + timestamp + ".bin";
      if (dynamic_objects::DataLoader::load_lidar(lidar_path, lidar, intensities))
        streamer.publish_lidar(lidar, intensities);

      // load bboxes
      std::string bbox_path = bbox_dir + "/" + timestamp + ".txt";
      if (dynamic_objects::DataLoader::load_bboxes(bbox_path, boxes))
        streamer.publish_boxes(boxes);

      ros::spinOnce();
      loop_rate.sleep();
    }
  }
  return 0;
}