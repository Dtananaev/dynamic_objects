#include "data_streamer.h"
namespace dynamic_objects
{
    DataStreamer::DataStreamer() : m_nh("~")
    {
        image_transport::ImageTransport it(m_nh);
        m_image_pub = it.advertise("camera/bbox_image", 1);
        m_lidar_pub = m_nh.advertise<sensor_msgs::PointCloud>("lidar", 10);
    }
    DataStreamer::~DataStreamer() {}

    void DataStreamer::publish_image(const std::vector<uint8_t> &image, int height, int width)
    {
        sensor_msgs::Image msg;
        msg.header.stamp = ros::Time::now();
        msg.header.frame_id = "/map";
        msg.height = height;
        msg.width = width;
        msg.encoding = "rgb8";
        msg.is_bigendian = false;
        msg.step = width * 3;
        msg.data = image;
        m_image_pub.publish(msg);
    }
    void DataStreamer::publish_lidar(const std::vector<geometry_msgs::Point32> &lidar, const std::vector<float> &intensities)
    {
        sensor_msgs::PointCloud msg;
        msg.header.stamp = ros::Time::now();
        msg.header.frame_id = "/map";
        msg.points = lidar;
        msg.channels.resize(1);
        msg.channels[0].name = "intensity";
        msg.channels[0].values = intensities;
        m_lidar_pub.publish(msg);
    }

} // namespace dynamic_objects