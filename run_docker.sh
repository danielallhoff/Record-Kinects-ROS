
export containerName=rosdocker

sleep 3 && \
        xhost +local:`docker inspect --format='{{ .Config.Hostname }}' $containerName` >/dev/null 2>&1 &

XSOCK=/tmp/.X11-unix
docker run --gpus '"device=1"' --rm -it \
        --volume=/home/.../Synthetic-Pipeline/:/workspace:rw \
        --volume=$HOME/.Xauthority:/root/.Xauthority:ro \
        --volume=$XSOCK:$XSOCK:rw \
        --env="DISPLAY" \
        --net=host \
        --name $containerName \
        rosdocker bash