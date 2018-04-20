# coding=utf-8
import cv2
import numpy as np
import sys


def correctionForCamera(inner_name, dist_name):
    """
    利用已标定的相机内参、畸变参数实时校正相机影像

    :param inner_name: 标定好的内参矩阵文件
    :param dist_name: 畸变参数文件
    :return: 空
    """

    inner = np.loadtxt(inner_name)
    dist = np.loadtxt(dist_name)

    print("Load success.")
    print("Inner parameters:")
    print(inner)
    print("Calibration parameters:")
    print(dist)

    cap = cv2.VideoCapture(0)

    # 一直循环捕获，直到手动退出
    while 1:
        ret, frame = cap.read()
        if frame is None:
            break
        else:
            cv2.imshow("origin", frame)
            h, w = frame.shape[:2]
            newcameramtx, roi = cv2.getOptimalNewCameraMatrix(inner, dist, (w, h), 1, (w, h))
            # undistort
            dst = cv2.undistort(frame, inner, dist, None, newcameramtx)

            # crop the image
            x, y, w, h = roi
            dst = dst[y:y + h, x:x + w]

            cv2.imshow("correct", dst)

            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                break

    cap.release()


def correctionForImages(inner_name, dist_name, ori_img):
    """
    利用已标定的参数对相片进行校正
    程序会将校正后的影像保存为correct.jpg

    :param inner_name: 内参矩阵文件
    :param dist_name: 畸变参数文件
    :param ori_img: 待校正影像文件
    :return: 空
    """

    inner = np.loadtxt(inner_name)
    dist = np.loadtxt(dist_name)

    print("Load success.")
    print("Inner parameters:")
    print(inner)
    print("Calibration parameters:")
    print(dist)

    ori = cv2.imread(ori_img)

    cv2.imshow("origin", ori)
    h, w = ori.shape[:2]
    newcameramtx, roi = cv2.getOptimalNewCameraMatrix(inner, dist, (w, h), 1, (w, h))
    # undistort
    dst = cv2.undistort(ori, inner, dist, None, newcameramtx)

    # crop the image
    x, y, w, h = roi
    dst = dst[y:y + h, x:x + w]

    cv2.imshow("correct", dst)
    cv2.imwrite("correct.jpg", dst)


if sys.argv.__len__() == 2 and sys.argv[1] == "help":
    print("通过读取已标定的参数，对摄像头或相片进行校正\n")
    print("脚本启动命令格式：")
    print("correctionForCamera:[inner_name] [dist_name]")
    print("correctionForImages:[inner_name] [dist_name] [ori_img]")
    print("\n函数帮助:")
    exec "help(correctionForCamera)"
    exec "help(correctionForImages)"
elif sys.argv.__len__() == 3:
    print("correctionForCamera")
    correctionForCamera(sys.argv[1], sys.argv[2])
elif sys.argv.__len__() == 4:
    print("correctionForImages")
    correctionForImages(sys.argv[1], sys.argv[2], sys.argv[3])
else:
    print("Input \"scriptname.py help\" for help information.")
