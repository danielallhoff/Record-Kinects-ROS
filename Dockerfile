FROM ubuntu:16.04
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 421C365BD9FF1F717815A3895523BAEEB01FA116

# setup sources.list
RUN echo "deb http://packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list

# install bootstrap tools
RUN apt-get update && apt-get install --no-install-recommends -y --allow-unauthenticated\
    python-rosdep \
    python-rosinstall \
    python-vcstools \
    && rm -rf /var/lib/apt/lists/*

# setup environment
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

# bootstrap rosdep
RUN rosdep init \
    && rosdep update

# install ros packages
ENV ROS_DISTRO kinetic
#RUN apt-get update && apt-get install -y \
 #   ros-kinetic-ros-core=1.3.1-0* \
  #  && rm -rf /var/lib/apt/lists/*

#RUN apt-get update && apt-get install -y \
 #   ros-kinetic-ros-base=1.3.1-0* \
#&& rm -rf /var/lib/apt/lists/*

RUN apt-get update && sudo apt-get upgrade

RUN apt-get install ros-kinetic-desktop-full -y --allow-unauthenticated

RUN apt-get install python-wstool build-essential -y --allow-unauthenticated

RUN apt-get update

RUN apt-get install -y ros-kinetic-pcl-* 

RUN apt-get install -y ros-kinetic-moveit-* --allow-unauthenticated

RUN apt-get install -y liblapack-dev

RUN apt-get install -y ros-kinetic-gazebo-dev ros-kinetic-gazebo-ros

RUN echo 'deb http://realsense-hw-public.s3.amazonaws.com/Debian/apt-repo xenial main' | tee /etc/apt/sources.list.d/realsense-public.list && \
    apt-key adv --keyserver keys.gnupg.net --recv-key 6F3EFCDE && \
    apt-get update && \
    apt-get install -y librealsense2-dkms \
    librealsense2-utils \
    librealsense2-dev \
    librealsense2-dbg 

RUN apt-get install -y ros-kinetic-openni2-launch --allow-unauthenticated

RUN apt-get install -y vim screen terminator --allow-unauthenticated

RUN apt-get update

RUN apt-get install -y libpopt-dev ros-kinetic-libpcan --allow-unauthenticated

RUN apt-get install -y ros-kinetic-rqt-reconfigure --allow-unauthenticated

RUN apt-get install -y ros-kinetic-industrial-core ros-kinetic-moveit-ros-warehouse ros-kinetic-warehouse-ros --allow-unauthenticated

#Needed to compile ros-keyboard to use tf-keyboard-cal
RUN apt-get update

RUN apt-get install -y libsdl-dev libsdl2-dev --allow-unauthenticated

RUN apt-get update

RUN apt-get install -y ros-kinetic-diagnostic-updater --allow-unauthenticated

#RUN apt-get purge -y librealsense2*

#RUN apt-get install -y ros-kinetic-librealsense ros-kinetic-realsense-camera
#RUN echo 'source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
#source ~/.bashrc
