# coding=utf-8
import cv2
import numpy as np
import sys


def background(input, output):
    """
    # 利用简单背景建模法提取背景(均值模型)

    :param input: 输入视频的路径
    :param output: 输出图片的路径
    :return: 空
    """

    cap = cv2.VideoCapture(input)

    # 获取视频宽高以及总帧数
    frames = int(cap.get(7))
    width = int(cap.get(3))
    height = int(cap.get(4))

    counter = 0

    # 注意数据类型对应的范围
    # 由于各帧相加会得到很大的数，因此先使用int64类型
    average = np.zeros((height, width, 3), np.uint64)

    while 1:
        ret, frame = cap.read()
        if frame is None:
            break
        else:
            # 对每一帧进行累加
            average += frame
            counter += 1
            print(counter.__str__() + "/" + frames.__str__())

    # 将累加结果除以总帧数
    average = np.uint64(average / counter)
    cv2.imwrite(output, average)
    cap.release()
    print("Saved " + output)


if sys.argv.__len__() == 2 and sys.argv[1] == "help":
    print("利用简单背景建模法提取背景(均值模型)\n")
    print("脚本启动命令格式：")
    print("scriptname.py:[video_path] [out_path]")
    print("\n函数帮助:")
    exec ("help(background)")
elif sys.argv.__len__() == 3:
    background(sys.argv[1], sys.argv[2])
else:
    print("Input \"scriptname.py help\" for help information.")
