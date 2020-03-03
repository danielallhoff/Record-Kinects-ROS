#include <iostream>
using namespace std;

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/CameraInfo.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
using namespace sensor_msgs;
using namespace message_filters;
ros::NodeHandle n("~");

ros::Publisher kinect1_pub_image = n.advertise<Image>("kinect1_image", 1);
ros::Publisher kinect2_pub_image = n.advertise<Image>("kinect2_image", 1);
ros::Publisher kinect3_pub_image = n.advertise<Image>("kinect3_image", 1);

ros::Publisher kinect1_pub_depth = n.advertise<Image>("kinect1_depth", 1);
ros::Publisher kinect2_pub_depth = n.advertise<Image>("kinect2_depth", 1);
ros::Publisher kinect3_pub_depth = n.advertise<Image>("kinect3_depth", 1);


typedef sync_policies::ApproximateTime<Image, Image, Image> MySyncPolicy;

void callback(const ImageConstPtr& kinect1,const ImageConstPtr& kinect2,const ImageConstPtr& kinect3){
    kinect1_pub_image.publish(kinect1);
    kinect2_pub_image.publish(kinect2);
    kinect3_pub_image.publish(kinect3);
}

void callback_depth(const ImageConstPtr& kinect1,const ImageConstPtr& kinect2,const ImageConstPtr& kinect3){
    kinect1_pub_depth.publish(kinect1);
    kinect2_pub_depth.publish(kinect2);
    kinect3_pub_depth.publish(kinect3);
}


int main(int argc, char **argv){
    ros::init(argc,argv, "Gatherer");
    //ros::Subscriber sub = n.subscribe("/kinect1/rgb/image_raw")
    message_filters::Subscriber<Image> kinect1(n, "/kinect1/rgb/image",1);
    message_filters::Subscriber<Image> kinect2(n, "/kinect2/rgb/image",1);
    message_filters::Subscriber<Image> kinect3(n, "/kinect3/rgb/image",1);

    

    message_filters::Subscriber<Image> kinect1_d(n, "/kinect1/depth/image",1);
    message_filters::Subscriber<Image> kinect2_d(n, "/kinect2/depth/image",1);
    message_filters::Subscriber<Image> kinect3_d(n, "/kinect3/depth/image",1);

    
    
    // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
    Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), kinect1, kinect2,kinect3);
    sync.registerCallback(boost::bind(&callback,_1,_2,_3));
    Synchronizer<MySyncPolicy> sync_depth(MySyncPolicy(10),kinect1_d,kinect2_d,kinect3_d);
    sync_depth.registerCallback(boost::bind(&callback_depth,_1,_2,_3));
    ros::spin();
    
    return 0;
}
