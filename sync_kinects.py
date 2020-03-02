import rospy
import cv2 as cv
import sys
import os
from std_msgs.msg import String
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist
from cv_bridge import CvBridge, CvBridgeError
import message_filters

PATH = os.path.abspath('images')
PATH = PATH + "/images"
print('Saving path = {}'.format(PATH))

class Gatherer:
    def __init__(self):
        self.frame_image = 0
        self.frame_depth = 0
        self.bridge = CvBridge()
        self.kinect1 = message_filters.Subscriber('/kinect1/rgb/image_raw', Image)
        self.kinect2 = message_filters.Subscriber('/kinect2/rgb/image_raw', Image)
        self.kinect3 = message_filters.Subscriber('/kinect3/rgb/image_raw', Image)
        self.timeSync = message_filters.ApproximateTimeSynchronizer([self.kinect1, self.kinect2, self.kinect3 ], queue_size=10,slop=0.1, allow_headerless=True)
        self.timeSync.registerCallback(self.SyncCallbackImage)

        self.kinect1_d = message_filters.Subscriber('/kinect1/depth/image_raw', Image)
        self.kinect2_d = message_filters.Subscriber('/kinect2/depth/image_raw', Image)
        self.kinect3_d = message_filters.Subscriber('/kinect3/depth/image_raw', Image)
        self.timeSync = message_filters.ApproximateTimeSynchronizer([self.kinect1_d, self.kinect2_d, self.kinect3_d ], queue_size=10,slop=0.1, allow_headerless=True)
        self.timeSync.registerCallback(self.SyncCallbackDepth)
        

    def SyncCallbackImage(self, kinect1, kinect2, kinect3):
        self.save_image(kinect1, "/kinect1/image")
        self.save_image(kinect2, "/kinect2/image")
        self.save_image(kinect2, "/kinect3/image")
        self.frame_image +=1
    def SyncCallbackDepth(self, kinect1, kinect2, kinect3):
        self.save_depth(kinect1, "/kinect1/depth")
        self.save_depth(kinect2, "/kinect2/depth")
        self.save_depth(kinect2, "/kinect3/depth")
        self.frame_depth +=1
        
    def save_image(self, img, path):
        cv_image = self.bridge.imgmsg_to_cv2(img, "bgr8")
        cv.imwrite(PATH+path + "_" + str(self.frame_image) + ".jpg", cv_image)  
    def save_depth(self, img, path):
        cv_image = self.bridge.imgmsg_to_cv2(img, "bgr8")
        cv.imwrite(PATH+path + "_" + str(self.frame_depth) + ".jpg", cv_image) 


def main():
    handler = Gatherer()
    rospy.init_node('Gatherer', anonymous=True)
    rate = rospy.Rate(2)
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)