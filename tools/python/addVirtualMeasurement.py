# coding=utf-8
import os.path
import sys
import cv2


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
    paths.sort()
    names.sort()
    print ("All images loaded.")
    return paths, names


def addVirtualMeasurement(root_dir, paths):
    """
    增加反向观测序列用于形成观测闭环

    :param root_dir: 帧影像的存放目录
    :param paths: 由findAllImages函数返回的各帧影像的路径
    :return: 空
    """

    separator = os.path.sep
    file_type = paths[0][paths[0].rfind(separator):][paths[0][paths[0].rfind(separator):].rfind('.'):]
    paths.reverse()
    for i in range(paths.__len__()):
        img = cv2.imread(paths[i])
        cv2.imwrite(root_dir + separator + "v_" + (i + 1).__str__().zfill(4) + file_type, img)
        print((i + 1).__str__() + "/" + paths.__len__().__str__())


if sys.argv.__len__() == 2:
    if sys.argv[1] == "help":
        print("对视频帧序列增加虚拟观测(反向观测序列)\n")
        print("脚本启动命令格式：")
        print("scriptname.py:[root_dir]")
        print("\n函数帮助:")
        exec ("help(findAllImages)")
        exec ("help(addVirtualMeasurement)")
    else:
        paths, names = findAllImages(sys.argv[1])
        addVirtualMeasurement(sys.argv[1], paths)
else:
    print("Input \"scriptname.py help\" for help information.")
