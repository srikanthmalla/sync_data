#include "Filewriter.h"
#include "Sync.h"


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "synchronizer_node");
	Sync sync;
	return 0;
}