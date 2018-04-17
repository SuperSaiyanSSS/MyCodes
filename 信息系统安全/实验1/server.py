# coding:utf-8
from __future__ import print_function, unicode_literals
import socket
import hashlib
import random

port = 5555
# 监听来自任何客户端的请求
host = ""

LOG_FILE = "log.txt"


# 日志记录用户活动
def log_user_action(client_name, success_flag):
    with open(LOG_FILE, "a") as f:
        import time
        time_string = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
        if success_flag:
            f.write(client_name + " " + "success" + " " + time_string + "\n")
        else:
            f.write(client_name + " " + "fail" + " " + time_string + "\n")


def produce_seed():
    seed = str(random.randint(1, 200))
    # 补全到3位
    seed = seed.zfill(3)
    return seed


def produce_m():
    m = random.randint(2, 3)
    return str(m)


def hash_private_kai_of_m(private_kai, m):
    m = int(m)
    while m != 0:
        # 创建的md5加密对象
        hash_object = hashlib.md5()
        hash_object.update(private_kai.encode(encoding='utf-8'))
        private_kai = hash_object.hexdigest()
        m -= 1
        print("aaa", private_kai)
    return private_kai


def resume_info(client_name):
    """
    当m减到0时，重新计数
    :param client_name:用户名
    :return: 用户名所在行的所有信息 含换行符
    """
    target_info = ""
    with open("resume_info.txt", 'r') as f:
        info_list = f.readlines()
        for info in info_list:
            if info.split(" ")[0] == client_name:
                target_info = info
                break
    with open("user_info.txt", 'r') as f:
        info_list = f.readlines()
    with open("user_info.txt", 'w') as f:
        for index, info in enumerate(info_list):
            if info.split(" ")[0] == client_name:
                info_list[index] = target_info
        f.writelines(info_list)


def server_process():
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.bind((host, port))
    # 只接受1个客户端的请求，如果有更多的请求，则处于等待状态
    s.listen(1)

    print("Server is running on port %d,press CTRL-C to terminate" % port)
    success_flag = True
    end = 1
    while end:
        # 如果有客户端请求，accept返回一个socket和客户端address
        clientsocket, clientaddr = s.accept()
        # 打印收到的客户端的地址
        print(str(clientaddr))
        # 使用文件方式
        clientfile = clientsocket.makefile("rw", 0)
        line = clientfile.readline().strip()
        # 打印收到的客户端的用户名(可能含有f标志)
        client_name = line
        print("当前客户端的用户名为", client_name)

        # 判断是否为首次登陆  如果是，则在使用户得到种子和迭代次数M，并再得到回复时在库中创建条目
        if line.split('_')[0] == 'f':
            print("当前用户为初次登陆")
            client_name = client_name.split("_")[1]
            seed = produce_seed()
            m = produce_m()
            clientfile.write("S/Key "+seed+" "+m+"\n")
            first_hashed_result = clientfile.readline().strip()
            print("收到了用户初次发来的md5值", first_hashed_result)
            with open("user_info.txt", 'a') as f:
                f.write(client_name+" "+seed+" "+str(m)+" "+first_hashed_result+"\n")
            with open("resume_info.txt", 'a') as f:
                f.write(client_name+" "+seed+" "+str(m)+" "+first_hashed_result+"\n")
        else:
            print("当前用户已经注册，即将验证真伪")
            is_find = False
            with open("user_info.txt", 'r') as f:
                info_list = f.readlines()
            for info in info_list:
                if info.split(" ")[0] == client_name:
                    seed = info.split(" ")[1]
                    m = info.split(" ")[2]
                    last_hashed_result = info.split(" ")[3].split("\n")[0]
                    is_find = True
                    break
            if not is_find:
                print("用户欺骗，明明不在数据库中")
            else:
                # 如果M值为1，那么重置M值
                if int(m) == 1:
                    resume_info(client_name)
                    with open("user_info.txt", 'r') as f:
                        info_list = f.readlines()
                    for info in info_list:
                        if info.split(" ")[0] == client_name:
                            seed = info.split(" ")[1]
                            m = info.split(" ")[2]
                            last_hashed_result = info.split(" ")[3].split("\n")[0]
                            is_find = True
                            break
                m = str(int(m)-1)
                clientfile.write("S/Key " + seed + " " + m + "\r\n")
                now_hashed_result = clientfile.readline().split("\r\n")[0].strip()
                print("收到了用户发来的不知道真伪的md5值", now_hashed_result)
                now_hashed_result = now_hashed_result.split("\r\n")[0]
                # a = list(now_hashed_result)
                # print(a)
                # print("jixu")
                # print(list(last_hashed_result))
                test_hashed_result = hash_private_kai_of_m(now_hashed_result, 1)
                print("计算之后的md5值",  test_hashed_result)
                if test_hashed_result == last_hashed_result:
                    print("用户登陆成功")
                    success_flag = True
                    clientfile.write("success"+"\r\n")
                else:
                    print("傻逼")
                    success_flag = False
                    clientfile.write("fail" + "\r\n")

                # 暂存更新m值后的列表
                for index, info in enumerate(info_list):
                    if info.split(" ")[0] == client_name:
                        info_list[index] = info.split(" ")[0]+" "+info.split(" ")[1]+" "+str(m)+" "+now_hashed_result+"\n"
                        break

                with open("user_info.txt", 'w') as f:
                    for i in info_list:
                        f.write(i)
                    print("更新完毕！")

        # clientfile.write("Welcome," + str(clientaddr) + "\n")
        # 如果输入空字符串则服务程序退出
        line = clientfile.readline().strip()
        if len(line) == 0:
            print("当前用户会话结束，退出")
            end = 0
            # 日志记录用户活动
            log_user_action(client_name, success_flag)
            # 文件必须关闭，socket.close不会负责关闭创建的文件
        clientfile.close()
        clientsocket.close()

if __name__ == '__main__':
    while 1:
        server_process()