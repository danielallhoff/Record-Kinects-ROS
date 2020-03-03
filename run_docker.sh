
export containerName=ros_kinetic

sleep 3 && \
        xhost +local:`docker inspect --format='{{ .Config.Hostname }}' $containerName` >/dev/null 2>&1 &

XSOCK=/tmp/.X11-unix
docker run --gpus '"device=1"' --rm -it \
        --volume=/home/dallhoff/Synthetic-Pipeline:/mnt/workspace:rw \
        --volume=$HOME/.Xauthority:/root/.Xauthority:ro \
        --volume=$XSOCK:$XSOCK:rw \
        --env="DISPLAY" \
        --net=host \
        --name $containerName \
        kinect/ros:latest bash
