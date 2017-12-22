#ifndef _FILE_WRITER_H_
#define _FILE_WRITER_H_

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>


class Filewriter{
	public:
		void createfolder(const std::string& folder);
		void imu2txt(const std::string& file_name, const sensor_msgs::ImuConstPtr& imu_data, int& frame_number);
		void pointcloud2ply(const std::string& file_name,const sensor_msgs::PointCloud2ConstPtr& pointcoud_data);
};

#endif