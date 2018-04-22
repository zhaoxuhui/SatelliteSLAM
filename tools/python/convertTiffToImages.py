# coding=utf-8
import cv2
import os.path
import sys


def findAllImages(root_dir):
    """
    读取root_dir目录下所有图片的路径，返回一个list
    :param root_dir: 图片存放的目录
    :return: 返回两个list，paths为图片的绝对路径，names为图片的文件名(不含扩展名)
    """

    separator = os.path.sep
    paths = []
    names = []
    # 遍历
    for parent, dirname, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith(".tif") or filename.endswith(".tiff") or filename.endswith(
                    ".TIF") or filename.endswith(
                ".TIFF"):
                paths.append(parent + separator + filename)
                names.append(filename[:filename.rfind('.')])
    print(paths.__len__().__str__() + " images loaded.")
    return paths, names


def convertImages(paths, out_dir, names, ext):
    """
    批量修改图片大小并输出
    :param paths: 存放图片的文件夹
    :param out_dir: 输出图片的文件夹
    :param names: 由findAllImages返回的文件名list
    :param ext: 输出文件的扩展名，jpg或png
    :return: 空
    """

    separator = os.path.sep
    for i in range(paths.__len__()):
        img = cv2.imread(paths[i])
        cv2.imwrite(out_dir + separator + names[i] + ext, img)
        print((i + 1).__str__() + "/" + paths.__len__().__str__())
    print("All images are converted.")


if sys.argv.__len__() == 2 and sys.argv[1] == "help":
    print("用于批量转换Tiff图片为jpg或png\n")
    print("脚本启动命令格式：")
    print("scriptname.py:[root_dir] [out_dir] [out_type]")
    print("out_type:0-jpg   1-png")
    print("\n函数帮助:")
    exec ("help(findAllImages)")
    exec ("help(convertImages)")
elif sys.argv.__len__() == 4:
    root_dir = sys.argv[1]
    out_dir = sys.argv[2]
    out_type = sys.argv[3]
    paths, names = findAllImages(root_dir)
    if out_type is '0':
        convertImages(paths, out_dir, names, '.jpg')
    elif out_type is '1':
        convertImages(paths, out_dir, names, '.png')
else:
    print("Input \"scriptname.py help\" for help information.")
