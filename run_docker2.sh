
export containerName=ros_kinetic

sleep 3 && \
        xhost +local:`docker inspect --format='{{ .Config.Hostname }}' $containerName` >/dev/null 2>&1 &

XSOCK=/tmp/.X11-unix
nvidia-docker run --rm -it \
        --volume=/home/john/daniel/Synthetic-Pipeline:/mnt/workspace/ros-sync/Synthetic-Pipeline:rw \
        --volume=$HOME/.Xauthority:/root/.Xauthority:ro \
        --volume=$XSOCK:$XSOCK:rw \
        --volume=/dev/pcan32:/dev/pcan32 \
        --volume=/dev/pcan33:/dev/pcan33 \
        --volume=/dev/pcanusb32:/dev/pcanusb32:rw \
        --volume=/dev/pcanusb33:/dev/pcanusb33:rw \
        --volume=/dev/pcan-usb/:/dev/pcan-usb \
        --volume=/dev/pcan-usb/0/can0:/dev/pcan-usb/0/can0 \
        --volume=/dev/pcan-usb/1/can0:/dev/pcan-usb/1/can0 \
        --volume=/lib/modules:/lib/modules:ro \
	--privileged \
        --env="DISPLAY" \
	--env="QT_X11_NO_MITSHM=1" \
        --net=host \
        --name $containerName \
        kinect/ros:latest bash -c "source /mnt/workspace/ros-sync/Synthetic-Pipeline/sync-project/devel/setup.bash && export ROS_IP=172.16.34.141 && roslaunch openni2_launch openni2.launch"
        #kinect/ros:latest bash -c "source /mnt/workspace/ros-sync/Synthetic-Pipeline/sync-project/devel/setup.bash && export ROS_IP=172.16.34.141 && roscore"
	#kinetic/ros:latest
