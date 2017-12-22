#include "Sync.h"
Sync::Sync(){
	std::cout<<"synchronization node started..\n";
	writer.createfolder(imu_folder);
	writer.createfolder(pcl_folder);
	imu_subscriber = nh_.subscribe<sensor_msgs::Imu>("torso_lift_imu/data", 10, &Sync::imu_callback, this);
	message_filters::Subscriber<sensor_msgs::Imu> imu_sub(nh_, "torso_lift_imu/data", 10);
	message_filters::Subscriber<sensor_msgs::LaserScan> pointcloud_sub(nh_, "tilt_scan", 10);
	typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::LaserScan> MySyncPolicy;
	//Approximate time synchronizer
	message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(50), imu_sub, pointcloud_sub);
	sync.registerCallback(boost::bind(&Sync::imu_laserscan,this, _1, _2));
	ros::spin();
}
void Sync::imu_callback(const sensor_msgs::ImuConstPtr& imu_data){
	//writing imu files
	imu_filename<<imu_folder<<"imu_"<<frame_number<<".txt";
	writer.imu2txt(imu_filename.str(),imu_data);
	imu_filename.str(std::string());
}
void Sync::imu_pointcloud(const sensor_msgs::ImuConstPtr& imu_data, const sensor_msgs::PointCloud2ConstPtr& pointcoud_data){
	frame_number=frame_number+1;
	//writing pointcloud to ply files
	ply_filename<<pcl_folder<<"pointcloud_"<<frame_number<<".ply";
	writer.pointcloud2ply(ply_filename.str(),pointcoud_data);
	ply_filename.str(std::string());
}
void Sync::imu_laserscan(const sensor_msgs::ImuConstPtr& imu_data, const sensor_msgs::LaserScanConstPtr& laserscan_data){
	frame_number=frame_number+1;
	ROS_DEBUG("Frame number: %d", frame_number);
	sensor_msgs::PointCloud2* cloud=new sensor_msgs::PointCloud2;
	sensor_msgs::PointCloud2ConstPtr cloudPtr(cloud);
	projector_.projectLaser(*laserscan_data, *cloud);
	//writing pointcloud to ply files
	ply_filename<<pcl_folder<<"pointcloud_"<<frame_number<<".ply";
	writer.pointcloud2ply(ply_filename.str(),cloudPtr);
	ply_filename.str(std::string());
}