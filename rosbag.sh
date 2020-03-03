if [-z "$1"]
    then
        echo "Empty args: name_bag_file"
        exit 1
fi


rosbag record -O $1 kinect1_image kinect2_image kinect3_image kinect1_depth kinect2_depth kinect3_depth