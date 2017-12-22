#include "Filewriter.h"

void Filewriter::createfolder(const std::string& folder){
	rmdir(folder.c_str());
	mkdir(folder.c_str(),0777);
}
void Filewriter::imu2txt(const std::string& file_name, const sensor_msgs::ImuConstPtr& imu_data){
  std::ofstream myfile;
  myfile.open (file_name,std::fstream::out|std::fstream::app);
  myfile << *imu_data;
  myfile.close();
}

void Filewriter::pointcloud2ply(const std::string& file_name,const sensor_msgs::PointCloud2ConstPtr& pointcoud_data){
	pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
	pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
	// Convert to PCL data type
	pcl_conversions::toPCL(*pointcoud_data, *cloud);
	//ply writer
	pcl::PLYWriter ply_writer;
	ply_writer.write(file_name,cloudPtr);
}