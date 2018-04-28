# coding=utf-8
import commands
import sys

# 输出帮助信息
if sys.argv.__len__() == 2 and sys.argv[1] == "help":
    print("This script is for recording screen on Linux.")
    print("It depends on 'byzanz' and 'xwininfo' package.")
    print("If you don't have them, you can use 'apt-get install' command to install them.")
else:
    # 执行命令获取捕获窗口坐标
    print("Please click on the window you want to record.")
    res = commands.getoutput('xwininfo')

    # 获取坐标
    num = [int(s) for s in res.split() if s.isdigit()]
    pos_x = num[0]
    pos_y = num[1]
    width = num[4]
    height = num[5]

    # 指定录制时长
    duration = raw_input("Input record duration(press 'Enter' choose 5 sec as default):\n")
    if duration == "":
        duration = 5

    # 指定保存路径和文件名
    save_path = raw_input("Input save gif name(press 'Enter' choose 'record.gif' as default):\n")
    if save_path == "":
        save_path = "record.gif"
    else:
        if not save_path.endswith("gif") or save_path.endswith("GIF"):
            save_path = save_path + ".gif"

    # 输出录制信息以确认
    print("Record Infomation:")
    print("Top-left x:" + pos_x.__str__() + " , " + "Top-left y:" + pos_y.__str__())
    print("Window width:" + width.__str__() + " " + "Window height:" + height.__str__())
    print("Duration:" + duration.__str__())
    print("Save path:" + save_path.__str__() + "\n")

    # 开始录制
    flag = raw_input("---Press 'Enter' to start,'q' to exit---")
    if flag == "":
        print("Recording...")
        com = "byzanz-record" + " -d " + duration.__str__() + " -x " + pos_x.__str__() + " -y " + pos_y.__str__() + " -w " + width.__str__() + " -h " + height.__str__() + " " + save_path.__str__()
        commands.getoutput(com)
        print("Finish")
    elif flag == 'q' or 'Q':
        exit()
