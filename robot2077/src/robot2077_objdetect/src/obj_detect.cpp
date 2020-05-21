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


static tf::TransformListener* tf_listener;
static std::string point_cloud_topic;
static ros::Publisher pc_pub;
static ros::Publisher mark_pub;

static visualization_msgs::Marker line_box;
static visualization_msgs::Marker line_follow;
static visualization_msgs::Marker text_marker;

ros::Publisher seg_objs;
ros::Publisher seg_planes;
ros::Publisher clustering0;
ros::Publisher clustering1;
ros::Publisher clustering2;
ros::Publisher clustering3;
ros::Publisher clustering4;
ros::Publisher masking;
ros::Publisher color;

cv::Mat rgb_image;
int img_counter = 0;

typedef struct stBoxMarker
{
    float xMax;
    float xMin;
    float yMax;
    float yMin;
    float zMax;
    float zMin;
}stBoxMarker;

static stBoxMarker boxMarker;

typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloud;
typedef pcl::PointCloud<pcl::PointXYZRGB>::Ptr PointCloud_Ptr;

void DrawBox(float inMinX, float inMaxX, float inMinY, float inMaxY, float inMinZ, float inMaxZ, float inR, float inG, float inB);
void DrawText(std::string inText, float inScale, float inX, float inY, float inZ, float inR, float inG, float inB);
void DrawPath(float inX, float inY, float inZ);
void RemoveBoxes();

void pc2_callback(const sensor_msgs::PointCloud2& pc) {
    printf("In callback!\n");
    sensor_msgs::PointCloud2 footprint;
    if (!tf_listener->waitForTransform("/base_footprint", pc.header.frame_id, pc.header.stamp, ros::Duration(5.0))) {
        return ;
    }
    printf("step1.\n");

    pcl_ros::transformPointCloud("/base_footprint", pc, footprint, *tf_listener);
    PointCloud cloud_src;
    pcl::fromROSMsg(footprint , cloud_src);
    ROS_INFO("cloud_src size = %d",cloud_src.size()); 

    PointCloud_Ptr cloud_src_ptr = cloud_src.makeShared();

    pcl::PassThrough<pcl::PointXYZRGB> pass;            //设置滤波器对象
    pass.setInputCloud (cloud_src_ptr);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (0.3, 1.5);
    pass.filter (*cloud_src_ptr);
    pass.setFilterFieldName ("x");
    pass.setFilterLimits (0.0, 1.5);
    pass.filter (*cloud_src_ptr);
    pass.setFilterFieldName ("y");
    pass.setFilterLimits (-1.5, 1.5);
    pass.filter (*cloud_src_ptr);

    PointCloud_Ptr plane(new PointCloud);
    PointCloud_Ptr convexHull(new PointCloud);
    PointCloud_Ptr objects(new PointCloud);

    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::SACSegmentation<pcl::PointXYZRGB> segmentation;
    segmentation.setInputCloud(cloud_src_ptr);
    segmentation.setModelType(pcl::SACMODEL_PERPENDICULAR_PLANE);
    segmentation.setMethodType(pcl::SAC_RANSAC);
    segmentation.setDistanceThreshold(0.005);
    segmentation.setOptimizeCoefficients(true);
    Eigen::Vector3f axis = Eigen::Vector3f(0.0,0.0,1.0);
    segmentation.setAxis(axis);
    segmentation.setEpsAngle(  10.0f * (M_PI/180.0f) );
    pcl::PointIndices::Ptr planeIndices(new pcl::PointIndices);
    segmentation.segment(*planeIndices, *coefficients);
    ROS_INFO_STREAM("1_Planes: " << planeIndices->indices.size());
    pcl::ExtractIndices<pcl::PointXYZRGB> extract;

    PointCloud_Ptr cloud_f (new PointCloud);
    int i = 0, nr_points = (int)(cloud_src_ptr->points.size());
    printf("step2.\n");

    while (cloud_src_ptr->points.size () > 0.03 * nr_points)
    {
        // Segment the largest planar component from the remaining cloud
        segmentation.setInputCloud (cloud_src_ptr);
        segmentation.segment (*planeIndices, *coefficients);
        if (planeIndices->indices.size () == 0)
        {
            ROS_WARN("Could not estimate a planar model for the given dataset.");
            break;
        }

        // Extract the planeIndices
        extract.setInputCloud (cloud_src_ptr);
        extract.setIndices (planeIndices);
        extract.setNegative (false);
        extract.filter (*plane);
        float plane_height = plane->points[0].z;
        ROS_WARN("%d - plana: %d points. height =%.2f" ,i, plane->width * plane->height,plane_height);
        if(plane_height > 0.6 && plane_height < 1.5) 
        break;

        // Create the filtering object
        extract.setNegative (true);
        extract.filter (*cloud_f);
        cloud_src_ptr.swap (cloud_f);
        i++;
    }
    printf("step3.\n");

    if (planeIndices->indices.size() == 0)
        std::cout << "Could not find a plane in the scene." << std::endl;
    else
    {
        // Copy the points of the plane to a new cloud.
        extract.setInputCloud(cloud_src_ptr);
        extract.setIndices(planeIndices);
        extract.filter(*plane);

        // Retrieve the convex hull.
        pcl::ConvexHull<pcl::PointXYZRGB> hull;
        hull.setInputCloud(plane);
        // Make sure that the resulting hull is bidimensional.
        hull.setDimension(2);
        hull.reconstruct(*convexHull);

        // Redundant check.
        if (hull.getDimension() == 2)
        {
            // Prism object.
            pcl::ExtractPolygonalPrismData<pcl::PointXYZRGB> prism;
            prism.setInputCloud(cloud_src_ptr);
            prism.setInputPlanarHull(convexHull);
            prism.setHeightLimits(-0.30, -0.03); //height limit objects lying on the plane
            pcl::PointIndices::Ptr objectIndices(new pcl::PointIndices);

            // Get and show all points retrieved by the hull.
            prism.segment(*objectIndices);
            extract.setIndices(objectIndices);
            extract.filter(*objects);
            seg_objs.publish(objects);
            seg_planes.publish(plane); 

            // run clustering extraction on "objects" to get several pointclouds
            pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
            pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
            std::vector<pcl::PointIndices> cluster_indices;
            ec.setClusterTolerance (0.05);
            ec.setMinClusterSize (800);
            ec.setMaxClusterSize (10000000);
            ec.setSearchMethod (tree);
            ec.setInputCloud (objects);
            ec.extract (cluster_indices);

            pcl::ExtractIndices<pcl::PointXYZRGB> extract_object_indices;
            std::vector<pcl::PointCloud<pcl::PointXYZRGB> > objectf;
            cv::Mat element;

            RemoveBoxes();
            int nObjCnt = 0;
            for(int i = 0; i<cluster_indices.size(); ++i)
            {
                pcl::PointCloud<pcl::PointXYZRGB>::Ptr object_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
                extract_object_indices.setInputCloud(objects);
                extract_object_indices.setIndices(boost::make_shared<const pcl::PointIndices>(cluster_indices[i]));
                extract_object_indices.filter(*object_cloud);
                objectf.push_back(*object_cloud);

                bool bFirstPoint = true;
                for (int j = 0; j < object_cloud->points.size(); j++) 
                {
                    pcl::PointXYZRGB p = object_cloud->points[j];
                    if(bFirstPoint == true)
                    {
                        boxMarker.xMax = boxMarker.xMin = p.x;
                        boxMarker.yMax = boxMarker.yMin = p.y;
                        boxMarker.zMax = boxMarker.zMin = p.z;
                        bFirstPoint = false;
                    }

                    if(p.x < boxMarker.xMin) { boxMarker.xMin = p.x;}
                    if(p.x > boxMarker.xMax) { boxMarker.xMax = p.x;}
                    if(p.y < boxMarker.yMin) { boxMarker.yMin = p.y;}
                    if(p.y > boxMarker.yMax) { boxMarker.yMax = p.y;}
                    if(p.z < boxMarker.zMin) { boxMarker.zMin = p.z;}
                    if(p.z > boxMarker.zMax) { boxMarker.zMax = p.z;}

                }
                if(boxMarker.xMin < 1.5 && boxMarker.yMin > -0.5 && boxMarker.yMax < 0.5)
                {
                    DrawBox(boxMarker.xMin, boxMarker.xMax, boxMarker.yMin, boxMarker.yMax, boxMarker.zMin, boxMarker.zMax, 0, 1, 0);

                    std::ostringstream stringStream;
                    stringStream << "obj_" << nObjCnt;
                    std::string obj_id = stringStream.str();
                    DrawText(obj_id,0.08, boxMarker.xMax,(boxMarker.yMin+boxMarker.yMax)/2,boxMarker.zMax + 0.04, 1,0,1);
                    nObjCnt++;
                    ROS_WARN("[obj_%d] xMin= %.2f yMin = %.2f yMax = %.2f",i,boxMarker.xMin, boxMarker.yMin, boxMarker.yMax);
                } 
            }

        }
        else std::cout << "The chosen hull is not planar." << std::endl;
    }
    printf("step4.\n");

}

void DrawBox(float inMinX, float inMaxX, float inMinY, float inMaxY, float inMinZ, float inMaxZ, float inR, float inG, float inB)
{
    line_box.header.frame_id = "base_footprint";
    line_box.ns = "line_box";
    line_box.action = visualization_msgs::Marker::ADD;
    line_box.id = 0;
    line_box.type = visualization_msgs::Marker::LINE_LIST;
    line_box.scale.x = 0.005;
    line_box.color.r = inR;
    line_box.color.g = inG;
    line_box.color.b = inB;
    line_box.color.a = 1.0;

    geometry_msgs::Point p;
    p.z = inMinZ;
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);

    p.z = inMaxZ;
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMinY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMinY; p.z = inMaxZ; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMaxY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMaxY; p.z = inMaxZ; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMaxY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMaxY; p.z = inMaxZ; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMinY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMinY; p.z = inMaxZ; line_box.points.push_back(p);
    mark_pub.publish(line_box);
}

static int nTextNum = 2;
void DrawText(std::string inText, float inScale, float inX, float inY, float inZ, float inR, float inG, float inB)
{
    text_marker.header.frame_id = "base_footprint";
    text_marker.ns = "line_obj";
    text_marker.action = visualization_msgs::Marker::ADD;
    text_marker.id = nTextNum;
    nTextNum ++;
    text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    text_marker.scale.z = inScale;
    text_marker.color.r = inR;
    text_marker.color.g = inG;
    text_marker.color.b = inB;
    text_marker.color.a = 1.0;

    text_marker.pose.position.x = inX;
    text_marker.pose.position.y = inY;
    text_marker.pose.position.z = inZ;
    
    text_marker.pose.orientation=tf::createQuaternionMsgFromYaw(1.0);

    text_marker.text = inText;

    mark_pub.publish(text_marker);
}

void RemoveBoxes()
{
    line_box.action = 3;
    line_box.points.clear();
    mark_pub.publish(line_box);
    line_follow.action = 3;
    line_follow.points.clear();
    mark_pub.publish(line_follow);
    text_marker.action = 3;
    mark_pub.publish(text_marker);
}



int main(int argc, char** argv) {
    ros::init(argc, argv, "obj_detect");
    ROS_INFO("Object Detection starts.");
    
    tf_listener = new tf::TransformListener();

    ros::NodeHandle n_private("~");
    n_private.param<std::string>("topic", point_cloud_topic, "/kinect2/sd/points");

    ros::NodeHandle n;
    ros::Subscriber pc_sub = n.subscribe(point_cloud_topic, 10, pc2_callback);
    printf("subscribe finishes!\n");
    pc_pub = n.advertise<sensor_msgs::PointCloud2>("/robot2077/obj_detect/obj_pc", 10);
    mark_pub = n.advertise<visualization_msgs::Marker>("/robot2077/obj_detect/obj_mark", 10);

    seg_objs = n.advertise<PointCloud>("/robot2077/obj_detect/segment_objs", 10);
    seg_planes = n.advertise<PointCloud>("/robot2077/obj_detect/segment_planes", 10);

    ros::spin();

    return 0;

}