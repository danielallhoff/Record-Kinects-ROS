if [-z "$1" || -z "$2" ]
    then
        echo "Empty args: node MASTER_IP"
        exit 1
fi

ssh $1
export ROS_MASTER_URI=http://$2:11311
roslaunch openni_launch openni.launch
#rosrun turtlesim turtlesim_node __name:=my_turtle