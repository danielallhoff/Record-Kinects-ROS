#include <iostream>
using namespace std;

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/CameraInfo.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


cv_bridge::CvImagePtr cv_ptr;
ros::Publisher kinect1_pub_image = n.advertise<Image>("kinect1_image", 1000);
ros::Publisher kinect2_pub_image = n.advertise<Image>("kinect2_image", 1000);
ros::Publisher kinect3_pub_image = n.advertise<Image>("kinect3_image", 1000);

ros::Publisher kinect1_pub_depth = n.advertise<Image>("kinect1_depth", 1000);
ros::Publisher kinect2_pub_depth = n.advertise<Image>("kinect2_depth", 1000);
ros::Publisher kinect3_pub_depth = n.advertise<Image>("kinect3_depth", 1000);

void callback(const ImageConstPtr& kinect1,const ImageConstPtr& kinect2,const ImageConstPtr& kinect3){
    kinect1_pub_image.publish(kinect1)
    kinect2_pub_image.publish(kinect2)
    kinect3_pub_image.publish(kinect3)
}

void callback_depth(const ImageConstPtr& kinect1,const ImageConstPtr& kinect2,const ImageConstPtr& kinect3){
    kinect1_pub_depth.publish(kinect1)
    kinect2_pub_depth.publish(kinect2)
    kinect3_pub_depth.publish(kinect3)
}

void save_image(const ImageConstPtr& image,const String& path){
    
    try{
        cv_ptr = cv_bridge::toCvCpy(msg, sensor_msgs::image_encodings::BGR8):

    }catch(cv_bridge::Exception& e){
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::imwrite(path, cv_ptr->image);
}

int main(int argc, char **argv){
    ros::init(argc,argv, "Gatherer");
    ros::NodeHandle n("~");
    //ros::Subscriber sub = n.subscribe("/kinect1/rgb/image_raw")
    message_filters::Subscriber<Image> kinect1(n, "/kinect1/rgb/image",1);
    message_filters::Subscriber<Image> kinect2(n, "/kinect2/rgb/image",1);
    message_filters::Subscriber<Image> kinect3(n, "/kinect3/rgb/image",1);

    TimeSynchronizer<Image,Image,Image> sync(kinect1,kinect2,kinect3,1000);
    sync.registerCallback(boost::bind(&callback,_1,_2,_3));

    message_filters::Subscriber<Image> kinect1_d(n, "/kinect1/depth/image",1);
    message_filters::Subscriber<Image> kinect2_d(n, "/kinect2/depth/image",1);
    message_filters::Subscriber<Image> kinect3_d(n, "/kinect3/depth/image",1);

    /*
    typedef sync_policies::ApproximateTime<Image, Image, Image> MySyncPolicy;
    // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
    Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), kinect1, kinect2,kinect3);
    */
    TimeSynchronizer<Image,Image,Image> sync(kinect1,kinect2,kinect3,1000);
    sync.registerCallback(boost::bind(&callback_depth,_1,_2,_3));
    ros::spin();

    return 0;
}
