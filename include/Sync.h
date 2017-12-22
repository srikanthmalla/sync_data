#ifndef _SYNC_H_
#define _SYNC_H_

#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <iostream>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/LaserScan.h>
#include <laser_geometry/laser_geometry.h>
#include "Filewriter.h"
#include <ros/console.h>
#include <ros/package.h>

class Sync{
public:
	Sync();
	void imu_pointcloud(const sensor_msgs::ImuConstPtr& imu_data, const sensor_msgs::PointCloud2ConstPtr& pointcoud_data);
	void imu_laserscan(const sensor_msgs::ImuConstPtr& imu_data, const sensor_msgs::LaserScanConstPtr& laserscan_data);
	void imu_callback(const sensor_msgs::ImuConstPtr& imu_data);
private:
	Filewriter writer;
	ros::NodeHandle nh_;
	ros::Subscriber imu_subscriber;
	int frame_number=0;
	std::string imu_folder=	ros::package::getPath("sync_data")+"/imu/";
	std::string pcl_folder= ros::package::getPath("sync_data")+"/pointcloud/";
	std::stringstream imu_filename;
	std::stringstream ply_filename;
	laser_geometry::LaserProjection projector_;
};

#endif