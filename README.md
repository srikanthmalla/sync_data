# Synchronizing lidar and Imu data using time stamps

1. Clone the repo to your workspace `https://github.com/srikanthmalla/sync_data.git`

2. go the package `cd sync_data`

3. Download the ros_bag file and save it as `input_new.bag` in the project folder, this current version synchronizes `velodyne_points`(PointCloud2) ~10 Hz and `imu/data`(Imu)~200Hz. Around 200/10 ~20 imu points lie between two frames of velodyne topic.

(you can switch to `git reset --hard f983bccf308e9e575b2fd157f0a4fd3e370dff73`, to work with laserscans from MIT STATA Center Dataset, can be downloaded with`sh download_dataset.sh` and read that README file. The rosbag gives `tilt_scan`(LaserScan)~20hz and `torso_lift_imu/data`(Imu)~100hz. Around 100/20~5 imu points lie between two laser scans.)

4. Compile the code using `catkin_make` 

5. Run `roslaunch sync_data synchronizer.launch`

6. You can find the outputs in (ply files)`pointcloud/`, (txt files)`imu/` (inside the `sync_data/` project folder).
