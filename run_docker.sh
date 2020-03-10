
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
        kinect/ros:latest bash -c "source /mnt/workspace/Synthetic-Pipeline/sync-project/devel/setup.bash &&  roslaunch freenect_launch freenect.launch"

#roslaunch openni2_launch openni2.launch"
