# coding=utf-8
import cv2
import sys


def captureVideo(root_dir):
    """
    用于通过摄像头捕获视频并将其保存成一帧帧影像

    :param root_dir: 保存图片的文件夹
    :return: 空
    """

    counter = 1
    # 新建一个VideoCapture对象，指定第0个相机进行视频捕获
    cap = cv2.VideoCapture(0)

    # 一直循环捕获，直到手动退出
    while 1:
        # 返回两个值，ret表示读取是否成功，frame为读取的帧内容
        ret, frame = cap.read()
        # 判断传入的帧是否为空，为空则退出
        if frame is None:
            break
        else:
            # 调用OpenCV图像显示函数显示每一帧
            cv2.imshow("video", frame)
            str = root_dir + counter.__str__().zfill(4) + ".jpg"
            cv2.imwrite(str, frame)
            print str
            counter += 1
            # 用于进行退出条件的判断，这里与0xFF进行了与运算，取输入的低八位
            k = cv2.waitKey(1) & 0xFF
            # 27是ESC键，表示如果按ESC键则退出
            if k == 27:
                break

    # 释放VideoCapture对象
    cap.release()


if sys.argv.__len__() == 2:
    if sys.argv[1] == "help":
        print("用于通过摄像头捕获视频，并将数据保存成一帧帧图片\n")
        print("脚本启动命令格式：")
        print("scriptname.py:[root_dir]")
        print("\n函数帮助:")
        exec "help(captureVideo)"
    else:
        captureVideo(sys.argv[1])
else:
    print("Input \"scriptname.py help\" for help information.")
