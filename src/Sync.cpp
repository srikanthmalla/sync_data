#include "Sync.h"
Sync::Sync(){
	std::cout<<"synchronization node started..\n";
	writer.createfolder(imu_folder);
	writer.createfolder(pcl_folder);
	imu_subscriber = nh_.subscribe<sensor_msgs::Imu>("imu/data", 200, &Sync::imu_callback, this);
	message_filters::Subscriber<sensor_msgs::Imu> imu_sub(nh_, "imu/data", 200);
	message_filters::Subscriber<sensor_msgs::PointCloud2> pointcloud_sub(nh_, "velodyne_points", 10);
	//Approximate time synchronizer
	typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::PointCloud2> MySyncPolicy;
	message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(50), imu_sub, pointcloud_sub);
	sync.registerCallback(boost::bind(&Sync::imu_pointcloud,this, _1, _2));
	ros::spin();
}
void Sync::imu_callback(const sensor_msgs::ImuConstPtr& imu_data){
	//writing imu files
	imu_filename<<imu_folder<<"imu_00000"<<frame_number<<".txt";
	writer.imu2txt(imu_filename.str(),imu_data,counter);
	imu_filename.str(std::string());
	counter++;
}
void Sync::imu_pointcloud(const sensor_msgs::ImuConstPtr& imu_data, const sensor_msgs::PointCloud2ConstPtr& pointcloud_data){
	frame_number++;
	counter=0;
	std::cout<<"\rFrame number: "<< frame_number<<std::flush;
	//writing pointcloud to ply files
	ply_filename<<pcl_folder<<"pointcloud_00000"<<frame_number<<".ply";
	writer.pointcloud2ply(ply_filename.str(),pointcloud_data);
	ply_filename.str(std::string());
}
void Sync::imu_laserscan(const sensor_msgs::ImuConstPtr& imu_data, const sensor_msgs::LaserScanConstPtr& laserscan_data){
	frame_number++;
	counter=0;
	std::cout<<"\rFrame number: "<< frame_number<<std::flush;
	sensor_msgs::PointCloud2* cloud=new sensor_msgs::PointCloud2;
	sensor_msgs::PointCloud2ConstPtr cloudPtr(cloud);
	projector_.projectLaser(*laserscan_data, *cloud);
	//writing pointcloud to ply files
	ply_filename<<pcl_folder<<"pointcloud_00000"<<frame_number<<".ply";
	writer.pointcloud2ply(ply_filename.str(),cloudPtr);
	ply_filename.str(std::string());
}