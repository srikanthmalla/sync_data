#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <iostream>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>
#include "Filewriter.h"

using namespace sensor_msgs;
using namespace message_filters;
void callback(const ImuConstPtr& imu_data, const PointCloud2ConstPtr& pointcoud_data)
{

	Filewriter writer;
	std::cout<< "callback"<<"\n";
	ROS_INFO_STREAM("Imu data " << imu_data << "\n");


}
int main(int argc, char* argv[])
{
    ros::init(argc, argv, "synchronizer_node");
	ros::NodeHandle nh;
	std::cout<<"synchronization node started\n";
	message_filters::Subscriber<Imu> imu_sub(nh, "imu/data", 1);
	message_filters::Subscriber<PointCloud2> pointcloud_sub(nh, "velodyne_points", 1);
	typedef sync_policies::ApproximateTime<Imu, PointCloud2> MySyncPolicy;
	//Approximate time synchronizer
	Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), imu_sub, pointcloud_sub);
	sync.registerCallback(boost::bind(&callback, _1, _2));

	ros::spin();

	return 0;
}