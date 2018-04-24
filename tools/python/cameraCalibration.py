# coding=utf-8
import cv2
import numpy as np
import sys
import glob


def calibrationWithCamera(ROWS, COLOMONS):
    """
    通过摄像头实时拍摄进行相机标定
    使用方法，调用函数向函数传入棋盘格的行、列，程序会自动打开摄像头，
    将棋盘格移入摄像头的视野范围，程序会自动识别出棋盘格，
    调整棋盘格姿态，按键盘“s”键保存当前图片，
    重复上述步骤，选择10-20张图片，
    然后按键盘“c”键，
    程序自动计算相机的内参、畸变参数，
    并保存至对应的文本文件中
    执行过程中，按“esc”键退出

    :param ROWS: 棋盘格的行数
    :param COLOMONS: 棋盘格的列数
    :return: 空
    """

    # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
    objp = np.zeros((ROWS * COLOMONS, 3), np.float32)
    objp[:, :2] = np.mgrid[0:ROWS, 0:COLOMONS].T.reshape(-1, 2)

    # Arrays to store object points and image points from all the images.
    objpoints = []  # 3d point in real world space
    imgpoints = []  # 2d points in image plane.

    counter = 0

    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    cap = cv2.VideoCapture(0)

    # 一直循环捕获，直到手动退出
    while 1:
        ret, frame = cap.read()
        if frame is None:
            break
        else:
            cv2.imshow("video", frame)
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            ret, corners = cv2.findChessboardCorners(gray, (ROWS, COLOMONS), None)
            if corners is not None:
                corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)

                img = cv2.drawChessboardCorners(frame, (ROWS, COLOMONS), corners2, ret)
                cv2.imshow('chessboard', img)
                k = cv2.waitKey(1) & 0xFF
                if k == ord('s'):
                    objpoints.append(objp)
                    imgpoints.append(corners2)
                    cv2.imwrite(counter.__str__() + ".jpg", gray)
                    counter += 1
                    print("1 image added,total " + counter.__str__() + " images.")
                elif k == ord('c'):
                    if imgpoints.__len__() >= 10:
                        print("Calculating parameters...")
                        ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None,
                                                                           None)
                        np.savetxt("inner.txt", mtx)
                        np.savetxt("distort.txt", dist)
                        print("Saved parameters.")
                    else:
                        print("No enough images.")
            if cv2.waitKey(1) & 0xFF == 27:
                break
    cap.release()


def calibrationWithImages(ROWS, COLOMONS):
    """
    利用拍摄好的相片进行标定
    使用方法，调用函数向函数传入棋盘格的行、列
    程序根据数据计算出内参矩阵和畸变参数
    并以文本文件格式输出

    :param ROWS: 棋盘格的行数
    :param COLOMONS: 棋盘格的列数
    :return: 空
    """

    # termination criteria
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
    objp = np.zeros((ROWS * COLOMONS, 3), np.float32)
    objp[:, :2] = np.mgrid[0:ROWS, 0:COLOMONS].T.reshape(-1, 2)

    # Arrays to store object points and image points from all the images.
    objpoints = []  # 3d point in real world space
    imgpoints = []  # 2d points in image plane.

    images = glob.glob('*.jpg')

    count = 0

    for fname in images:
        img = cv2.imread(fname)
        # img = cv2.resize(img, None, fx=0.1, fy=0.1, interpolation=cv2.INTER_CUBIC)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        cv2.imshow("imgs", gray)
        cv2.waitKey(500)

        # Find the chess board corners
        ret, corners = cv2.findChessboardCorners(gray, (ROWS, COLOMONS), None)

        # If found, add object points, image points (after refining them)
        if ret == True:
            objpoints.append(objp)

            corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
            print(corners2.__len__())
            imgpoints.append(corners2)

            # Draw and display the corners
            img = cv2.drawChessboardCorners(img, (ROWS, COLOMONS), corners2, ret)
            cv2.imshow('chessboard', img)
            cv2.waitKey(500)
            count += 1
            print(count.__str__() + "/" + images.__len__().__str__())

    cv2.destroyAllWindows()

    print("Calculating parameters...")

    ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

    np.savetxt("inner.txt", mtx)
    np.savetxt("distort.txt", dist)

    print("Saved inner.txt")
    print("Saved distort.txt")


if sys.argv.__len__() == 2 and sys.argv[1] == "help":
    print("用于通过摄像头拍摄或相片对其进行标定，获得内参和畸变参数\n")
    print("脚本启动命令格式：")
    print("calibrationWithCamera:[0] [ROWS] [COLOMONS]")
    print("calibrationWithImages:[1] [ROWS] [COLOMONS]")
    print("\n函数帮助:")
    exec ("help(calibrationWithCamera)")
    exec ("help(calibrationWithImages)")
elif sys.argv.__len__() == 4 and sys.argv[1] == "0":
    print("calibrationWithCamera")
    calibrationWithCamera(int(sys.argv[2]), int(sys.argv[3]))
elif sys.argv.__len__() == 4 and sys.argv[1] == "1":
    print("calibrationWithImages")
    calibrationWithImages(int(sys.argv[2]), int(sys.argv[3]))
else:
    print("Input \"scriptname.py help\" for help information.")
