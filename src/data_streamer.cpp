#include "data_streamer.h"
namespace dynamic_objects
{
    DataStreamer::DataStreamer() : m_nh("~")
    {
        image_transport::ImageTransport it(m_nh);
        m_image_pub = it.advertise("camera/bbox_image", 10);
        m_lidar_pub = m_nh.advertise<sensor_msgs::PointCloud>("lidar", 10);
        m_boxes_pub = m_nh.advertise<visualization_msgs::MarkerArray>("/boxes", 10);
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
    void DataStreamer::publish_boxes(const std::vector<dynamic_objects::CwhlyBox> &boxes)
    {
        visualization_msgs::MarkerArray marker_bboxes_array;
        visualization_msgs::Marker marker_box;
        marker_box.header.frame_id = "/map";
        marker_box.header.stamp = ros::Time::now();
        marker_box.ns = "bboxes"; // namespace
        marker_box.id = 0;
        marker_box.lifetime = ros::Duration(0.1);
        marker_box.type = visualization_msgs::Marker::CUBE;
        marker_box.action = visualization_msgs::Marker::ADD;

        visualization_msgs::Marker marker_arrow;
        marker_arrow.header.frame_id = "/map";
        marker_arrow.header.stamp = ros::Time::now();
        marker_arrow.ns = "arrows"; // namespace
        marker_arrow.id = 0;
        marker_arrow.lifetime = ros::Duration(0.1);
        marker_arrow.type = visualization_msgs::Marker::ARROW;
        marker_arrow.action = visualization_msgs::Marker::ADD;

        for (const auto &box : boxes)
        {

            tf2::Quaternion box_orientation;
            box_orientation.setRPY(0, 0, box.yaw);
            box_orientation.normalize(); //The magnitude of a quaternion should be one\

            marker_box.pose.position.x = box.x;
            marker_box.pose.position.y = box.y;
            marker_box.pose.position.z = box.z;
            marker_box.pose.orientation.x = box_orientation.x();
            marker_box.pose.orientation.y = box_orientation.y();
            marker_box.pose.orientation.z = box_orientation.z();
            marker_box.pose.orientation.w = box_orientation.w();
            marker_box.scale.x = box.l;
            marker_box.scale.y = box.w;
            marker_box.scale.z = box.h;
            std::vector<dynamic_objects::color> colors;
            dynamic_objects::Helpers::get_color_palette(colors);
            marker_box.color.r = colors[box.label].r;
            marker_box.color.g = colors[box.label].g;
            marker_box.color.b = colors[box.label].b;
            marker_box.color.a = 1.0;
            marker_bboxes_array.markers.push_back(marker_box);
            marker_box.id++;

            marker_arrow.pose.position.x = box.x;
            marker_arrow.pose.position.y = box.y;
            marker_arrow.pose.position.z = box.z;
            marker_arrow.pose.orientation.x = box_orientation.x();
            marker_arrow.pose.orientation.y = box_orientation.y();
            marker_arrow.pose.orientation.z = box_orientation.z();
            marker_arrow.pose.orientation.w = box_orientation.w();
            marker_arrow.scale.x = box.l;
            marker_arrow.scale.y = 0.1;
            marker_arrow.scale.z = 0.1;
            marker_arrow.color.r = 1;
            marker_arrow.color.g = 0;
            marker_arrow.color.b = 0;
            marker_arrow.color.a = 1.0;
            marker_bboxes_array.markers.push_back(marker_arrow);
            marker_arrow.id++;
        }
        m_boxes_pub.publish(marker_bboxes_array);
    }
} // namespace dynamic_objects