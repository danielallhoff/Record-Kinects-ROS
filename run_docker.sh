
export containerName=ros_kinetic

sleep 3 && \
        xhost +local:`docker inspect --format='{{ .Config.Hostname }}' $containerName` >/dev/null 2>&1 &

XSOCK=/tmp/.X11-unix
docker run --rm -it \
        --volume=/home/daniel/Desktop/Synthetic-Pipeline:/mnt/workspace/Synthetic-Pipeline:rw \
        --volume=$HOME/.Xauthority:/root/.Xauthority:ro \
        --volume=$XSOCK:$XSOCK:rw \
        --volume=/dev/bus/usb:/dev/bus/usb \
        --volume=/lib/modules:/lib/modules:ro \
	--privileged \
        --env="DISPLAY" \
        --net=host \
        --name $containerName \
        kinect/ros:latest bash -c "source /mnt/workspace/Synthetic-Pipeline/sync-project/devel/setup.bash && export ROS_IP=172.19.33.191 && export ROS_MASTER_URI=http://172.16.34.141:11311 && roslaunch freenect_launch freenect.launch camera:=kinect1"

#roslaunch openni2_launch openni2.launch" in primesense case
