# Synchronizing lidar and Imu data using time stamps

1. Clone the repo to your workspace `https://github.com/srikanthmalla/sync_data.git`

2. go the package `cd sync_data`

3. Download the test ros_bag file by running `sh download_dataset.sh`, it downloads sample dataset from MIT Stata Center.

4. Compile the code using `catkin_make` 

5. Run `roslaunch sync_data synchronizer.launch`

6. You can find the outputs in project folder `pointcloud/` and `imu/`
