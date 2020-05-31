#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/surface/convex_hull.h>
#include <pcl/segmentation/extract_polygonal_prism_data.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/segmentation/extract_clusters.h>
#include <image_geometry/pinhole_camera_model.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <sensor_msgs/Image.h>
#include <pcl_ros/transforms.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

static ros::Publisher pc_pub;

int main(int argc, char** argv) {
    ros::init(argc, argv, "obj_detect_pointcloud_publish");
    ROS_INFO("Object Pointcloud starts publishing.");
    

    ros::NodeHandle n;
    pc_pub = n.advertise<sensor_msgs::PointCloud2>("/robot2077/obj_detect/pc_publish", 1000);
    std_msgs::Header header;
    header.seq = 1000;
    header.frame_id = "kinect2_ir_optical_frame";
    sensor_msgs::PointCloud2 save;
    pcl::io::loadPCDFile("/home/cauchymars/demo2_ws/src/robot2077_objdetect/test/save_1.pcd", save);
    save.header = header;
    ros::Rate loop_rate(1);

    while (ros::ok()) {
        pc_pub.publish(save);
        loop_rate.sleep();
    }

    ros::spin();

    return 0;

}