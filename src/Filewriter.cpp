#include "Filewriter.h"
#include <vector>
void Filewriter::createfolder(const std::string& folder){
	std::string command="rm -rf "+folder;
	system(command.c_str());
	mkdir(folder.c_str(),0777);
	std::cout<<"successfull removed and created \"" <<folder<<"\" \n"<<std::flush;
}

void Filewriter::imu2txt(const std::string& file_name, const sensor_msgs::ImuConstPtr& imu_data,int& frame_number){
	std::ofstream myfile;
	myfile.open (file_name,std::fstream::out|std::fstream::app);
	//frame
	myfile << frame_number<<"\n";
	//orientation
	myfile << (*imu_data).orientation.x<<" "<<(*imu_data).orientation.y<<" "<<(*imu_data).orientation.z<<" "<<(*imu_data).orientation.w<<"\n";
	// orientation covariance
	for (auto& val:(*imu_data).orientation_covariance){
		myfile << val<<" ";
	}myfile<<"\n";

	//angular velocity
	myfile << (*imu_data).angular_velocity.x<<" "<<(*imu_data).angular_velocity.y<<" "<<(*imu_data).angular_velocity.z<<"\n";
	//angular velocity covariance	
	for (auto& val:(*imu_data).angular_velocity_covariance){
		myfile << val<<" ";
	}myfile<<"\n";
	//linear acceleration
	myfile << (*imu_data).linear_acceleration.x<<" "<<(*imu_data).linear_acceleration.y<<" "<<(*imu_data).linear_acceleration.z<<"\n";
	//linear acceleration covariance
	for (auto& val:(*imu_data).linear_acceleration_covariance){
		myfile << val<<" ";
	}myfile<<"\n";

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