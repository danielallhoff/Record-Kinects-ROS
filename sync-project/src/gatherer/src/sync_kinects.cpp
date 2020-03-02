#include <iostream>
using namespace std;

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/CameraInfo.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int frames_images = 0;
int frames_depth = 0;
cv_bridge::CvImagePtr cv_ptr;
void callback(const ImageConstPtr& kinect1,const ImageConstPtr& kinect2,const ImageConstPtr& kinect3){
    save_image(kinect1,"../kinect1/images/" + frames_images + ".png");
    save_image(kinect2,"../kinect2/images/"+ frames_images + ".png");
    save_image(kinect3,"../kinect3/images/"+ frames_images + ".png");
    frames_images += 1;
}

void callback_depth(const ImageConstPtr& kinect1,const ImageConstPtr& kinect2,const ImageConstPtr& kinect3){
    save_image(kinect1,"../kinect1/depth/"+ frames_depth + ".png");
    save_image(kinect2,"../kinect2/depth/"+ frames_depth + ".png");
    save_image(kinect3,"../kinect3/depth/"+ frames_depth + ".png");
    frames_depth += 1;
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

    TimeSynchronizer<Image,Image,Image> sync(kinect1,kinect2,kinect3,10);
    sync.registerCallback(boost::bind(&callback,_1,_2,_3));

    message_filters::Subscriber<Image> kinect1_d(n, "/kinect1/depth/image",1);
    message_filters::Subscriber<Image> kinect2_d(n, "/kinect2/depth/image",1);
    message_filters::Subscriber<Image> kinect3_d(n, "/kinect3/depth/image",1);
    /*
    typedef sync_policies::ApproximateTime<Image, Image, Image> MySyncPolicy;
    // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
    Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), kinect1, kinect2,kinect3);
    */
    TimeSynchronizer<Image,Image,Image> sync(kinect1,kinect2,kinect3,10);
    sync.registerCallback(boost::bind(&callback_depth,_1,_2,_3));
    ros::spin();

    return 0;
}
