#ifndef DATA_STREAMER_H
#define DATA_STREAMER_H
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <tf2/LinearMath/Quaternion.h>
#include <vector>
#include <cstdint>
#include "data_types.h"
#include "helpers.h"
namespace dynamic_objects
{
    class DataStreamer
    {
    public:
        DataStreamer();
        ~DataStreamer();

        void publish_image(const std::vector<uint8_t> &image, int height, int width);
        void publish_lidar(const std::vector<geometry_msgs::Point32> &lidar, const std::vector<float> &intensities);
        void publish_boxes(const std::vector<dynamic_objects::CwhlyBox> &boxes);

    private:
        ros::NodeHandle m_nh;
        image_transport::Publisher m_image_pub;
        ros::Publisher m_lidar_pub, m_boxes_pub;
    };
} // namespace dynamic_objects
#endif //DATA_STREAMER_H