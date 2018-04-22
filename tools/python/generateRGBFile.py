# coding=utf-8
import os.path
import sys


def findAllImages(root_dir):
    """
    用于寻找文件夹内所有图片

    :param root_dir: 待搜索文件夹
    :return: 包含文件名的list
    """

    separator = os.path.sep
    names = []
    # 遍历
    for parent, dirname, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith(".jpg") or filename.endswith(".JPG") or filename.endswith(".png") or filename.endswith(
                    ".PNG"):
                names.append(filename)
    names.sort()
    print ("All images loaded.")
    return names


def generateRGBfile(names, out_dir, folder):
    """
    按照TUM数据集的格式来生成RGB索引文件，时间默认从1开始累加

    :param names: findAllImages返回的结果
    :param out_dir: rgb.txt输出位置
    :param folder: out_dir中用于存放图像的文件夹名称
    :return:
    """

    separator = os.path.sep
    f = open(out_dir + separator + "rgb.txt", 'w')
    f.write("# color images\n")
    f.write("file: 'rgb_dataset_images'\n")
    f.write("timestamp filename\n")

    for i in range(names.__len__()):
        f.write(i.__str__() + " " + folder + separator + names[i] + "\n")
    f.close()


if sys.argv.__len__() == 2 and sys.argv[1] == "help":
    print("用于生成符合TUM数据集格式的rgb索引文件，以便传入ORB-SLAM\n")
    print("脚本启动命令格式：")
    print("scriptname.py:[root_dir] [out_dir] [folder]")
    print("\n函数帮助:")
    exec ("help(findAllImages)")
    exec ("help(generateRGBfile)")
elif sys.argv.__len__() == 4:
    root_dir = sys.argv[1]
    out_dir = sys.argv[2]
    folder = sys.argv[3]
    imgs = findAllImages(root_dir)
    generateRGBfile(imgs, out_dir, folder)
else:
    print("Input \"scriptname.py help\" for help information.")
