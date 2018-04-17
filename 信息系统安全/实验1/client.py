# coding:utf-8
from __future__ import print_function, unicode_literals
import socket
import hashlib

PROT = 5555
HOST = "localhost"



# 预处理
def pre_treat(private_key, seed):
    result = private_key+seed
    return result


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


def client_process():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PROT))

    is_first = raw_input("是否为第一次登陆？")
    if is_first.lower() == "y":
        client_name = raw_input("请输入用户名!")
        # 绑定socket与fd
        fd = s.makefile("rw", 0)
        fd.write("f_"+client_name + "\r\n")
        while 1:
            buf = fd.readline()
            if not len(buf):
                break
            print("收到了 "+buf)
            if buf.split(" ")[0] == "S/Key":
                seed = buf.split(" ")[1]
                m = buf.split(" ")[2].split('\n')[0]
                print("my seed "+seed)
                print(m)
                private_key = raw_input("请输入要创建的私钥，牢记！")
                private_kai = pre_treat(private_key, seed)
                first_hashed_result = hash_private_kai_of_m(private_kai, m)
                # 发送第一次hash之后的值
                fd.write(first_hashed_result+"\r\n")
                # 结束标志
                fd.write("\r\n")
            else:
                # 如果没收到S/Key开头的则断言错误
                assert NameError

        fd.close()

    elif is_first.lower() == "n":
        client_name = raw_input("请输入用户名!")
        # 绑定socket与fd
        fd = s.makefile("rw", 0)
        fd.write(client_name + "\r\n")
        while 1:
            buf = fd.readline()
            if not len(buf):
                break
            print("收到了 "+buf)
            if buf.split(" ")[0] == "S/Key":
                seed = buf.split(" ")[1]
                m = buf.split(" ")[2].split('\n')[0]
                print("my seed "+seed)
                print(m)
                private_key = raw_input("请输入之前记住的私钥！")
                private_kai = pre_treat(private_key, seed)
                now_hashed_result = hash_private_kai_of_m(private_kai, m)
                # 发送输入的密钥预处理hash之后的值
                fd.write(now_hashed_result+"\r\n")
                test_success = fd.readline()
                if test_success[0] == "s":
                    print("恭喜老铁 ，登陆成功")
                elif test_success[0] == "f":
                    print("输错密钥了老铁，耻辱下播！")
                else:
                    print("什么臭鱼烂虾")
                # 结束标志
                fd.write("\r\n")
                break
            else:
                # 如果没收到S/Key开头的则断言错误
                assert NameError
        fd.close()
    else:
        print("输入非法")
    s.close()

if __name__ == '__main__':
    client_process()