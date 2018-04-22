# coding=utf-8
import cv2
import os.path
import sys


def findAllImages(root_dir):
    """
    读取root_dir目录下所有图片的路径，返回一个list

    :param root_dir: 图片存放的目录
    :return: 返回两个list，paths为图片的绝对路径，names为图片的文件名
    """

    separator = os.path.sep
    paths = []
    names = []
    # 遍历
    for parent, dirname, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith(".jpg") or filename.endswith(".JPG") or filename.endswith(".png") or filename.endswith(
                    ".PNG"):
                paths.append(parent + separator + filename)
                names.append(filename)
    print ("All images loaded.")
    return paths, names


def resizeImages(paths, out_dir, names, ratio):
    """
    批量修改图片大小并输出

    :param paths: 存放图片的文件夹
    :param out_dir: 输出图片的文件夹
    :param names: 由findAllImages返回的文件名list
    :param ratio: 缩放比例
    :return: 空
    """

    separator = os.path.sep
    for i in range(paths.__len__()):
        img = cv2.imread(paths[i])
        res = cv2.resize(img, None, fx=ratio, fy=ratio, interpolation=cv2.INTER_CUBIC)
        cv2.imwrite(out_dir + separator + names[i], res)
        print ((i + 1).__str__() + "/" + paths.__len__().__str__())
    print ("All images are resized.")


if sys.argv.__len__() == 2 and sys.argv[1] == "help":
    print("用于批量修改图片的大小\n")
    print("脚本启动命令格式：")
    print("scriptname.py:[root_dir] [out_dir] [ratio]")
    print("\n函数帮助:")
    exec ("help(findAllImages)")
    exec ("help(resizeImages)")
elif sys.argv.__len__() == 4:
    root_dir = sys.argv[1]
    out_dir = sys.argv[2]
    ratio = float(sys.argv[3])
    paths, names = findAllImages(root_dir)
    resizeImages(paths, out_dir, names, ratio)
else:
    print("Input \"scriptname.py help\" for help information.")
