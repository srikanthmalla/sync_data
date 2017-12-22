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

class Filewriter{
	public:
		void imu2txt(const std::string& file_name, const sensor_msgs::ImuConstPtr& imu_data);
		void pointcloud2ply(const std::string& file_name,const sensor_msgs::PointCloud2ConstPtr& pointcoud_data);
};

void Filewriter::imu2txt(const std::string& file_name, const sensor_msgs::ImuConstPtr& imu_data){
  std::ofstream myfile;
  myfile.open (file_name);
  myfile << *imu_data;
  myfile.close();
}

void Filewriter::pointcloud2ply(const std::string& file_name,const sensor_msgs::PointCloud2ConstPtr& pointcoud_data){
	pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
	pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
	pcl::PCLPointCloud2 cloud_filtered;
	// Convert to PCL data type
	pcl_conversions::toPCL(*pointcoud_data, *cloud);
	// std::string file_name="pointcloud_000001.ply";
	pcl::PLYWriter ply_writer;
	ply_writer.write(file_name,cloudPtr);
}
#endif