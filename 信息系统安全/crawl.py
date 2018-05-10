# coding: utf-8
from __future__ import print_function, unicode_literals
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
import execjs
import cfscrape
from requests.adapters import HTTPAdapter
import hashlib
import pymysql


# MySQL数据库连接信息
HOST = "localhost"
USER = "root"
PASSWORD = "123456"
DB_TASK = "softwaresystem"
TEACHER_TABLE = "teacher"
STUDENT_TABLE = "student"


def hash_private_kai_of_m(private_kai, m):
    m = int(m)
    while m != 0:
        # 创建的md5加密对象
        hash_object = hashlib.md5()
        hash_object.update(private_kai.encode(encoding='utf-8'))
        private_kai = hash_object.hexdigest()
        m -= 1
    return private_kai


class Parser(object):


    def __init__(self):

        self._md5_list = []
        self.info_dict = {}

        from requests.adapters import HTTPAdapter

        self.client = cfscrape.create_scraper()
        self.client.mount('http://', HTTPAdapter(max_retries=3))
        self.client.mount('https://', HTTPAdapter(max_retries=3))
        self.detect_ip()
        self.parse_enter_page()

    def parse_enter_page(self):
        a = self.client.get("http://www.hitsz.edu.cn/teacher/id-14.html").content

    def insert_student(self):
        db = pymysql.connect(host=HOST, user=USER, password=PASSWORD, db=DB_TASK, port=3306, charset="utf8")
        cur = db.cursor()
        name_list = ["张大川", "李毅", "王景昊", "韩立", "李昌东"]
        id_list = ["117", "118", "119", "120", "121"]
        degree_list = [3, 4, 5, 6, 1]
        sex_list = ["男" for i in range(5)]
        age_list = [18, 19, 19, 19, 16]
        email_list = [i+"@stu.hit.edu.cn" for i in id_list]
        type_list = [1 for i in range(5)]
        password_list = [hash_private_kai_of_m(str(id).zfill(5), 1) for id in id_list]

        for name, id, degree, sex, age, email, type, password in zip(name_list, id_list, degree_list, sex_list, age_list, email_list, type_list, password_list):
            sql_insert_student = '''insert into `%s`(student_id, degree, info, sex, age, email, name, type, password) values("%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s")''' % (STUDENT_TABLE, int(id), int(department_id), name, type, email, address, research_area, info, sex, password)

    def detect_ip(self):
        # 2395
        # 2114
        # http://faculty.ecnu.edu.cn/s/2114/main.jspy
        # 396
        db = pymysql.connect(host=HOST, user=USER, password=PASSWORD, db=DB_TASK, port=3306, charset="utf8")
        cur = db.cursor()

        computer_id_list = [396, 242, 492, 237, 238]
        information_id_list = [262, 478]
        economy_id_list = [1764, 456]
        literature_id_list = [1308]
        sum_id_list = []
        sum_id_list.extend(computer_id_list)
        sum_id_list.extend(information_id_list)
        sum_id_list.extend(economy_id_list)
        sum_id_list.extend(literature_id_list)

        for id in sum_id_list:
            a = self.client.get("http://www.hitsz.edu.cn/teacher/view/id-"+str(id)+".html").content

            import re
            address_pattern = re.compile(r'通讯地址：\s*?(\S*?)\s*?<br')
            address_match = address_pattern.findall(unicode(a))
            email_pattern = re.compile(r'电子邮件：<a href="#">\s*?([\S\s]*?)<')
            email_match = email_pattern.findall(unicode(a))
            info_pattern = re.compile(r'个人简介[\S\s]*?<div>([\s\S]*?)<')
            info_match = info_pattern.findall(unicode(a))
            research_pattern = re.compile(r'研究方向\S*?\s*?<div>([\s\S]*?)<')
            researh_match = research_pattern.findall(unicode(a))
            name_pattern = re.compile(r'title">([\s\S]*?)<')
            name_match = name_pattern.findall(unicode(a))
            print(id)
            address = address_match[0].strip()
            email = email_match[0].strip()
            info = info_match[0].strip()
            research_area = researh_match[0].strip()
            name = name_match[0].strip()
            sex = '男'
            type = 2
            print(address)
            print(email)
            print(info)
            print(research_area)
            print(name)
            id_string = "t1001"+str(id).zfill(5)
            password = hash_private_kai_of_m(str(id).zfill(5), 1)
            print(id_string)
            print(password)
            if id in computer_id_list:
                department_id = "100101"
            elif id in information_id_list:
                department_id = "100102"
            elif id in economy_id_list:
                department_id = "100103"
            elif id in literature_id_list:
                department_id = "100104"

            sql_insert_teacher = "insert into "+TEACHER_TABLE+" ('teacher_id', 'department_id', 'name', 'type', " \
                                                              "'email', 'address', 'research_area', 'info', 'sex', " \
                                                              "'password') values("
            # sql_insert_teacher = '''insert into `%s`(teacher_id, department_id, name, type, email, address, research_area, info, sex, password) values("%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s")''' %(TEACHER_TABLE, id_string, department_id, name, type, email, address, research_area, info, sex, research_area)
            sql_insert_teacher = '''insert into `%s`(teacher_id, department_id, name, type, email, address, research_area, info, sex, password) values("%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s")''' %(TEACHER_TABLE, int(id), int(department_id), name, type, email, address, research_area, info, sex, password)
            cur.execute(sql_insert_teacher)
            db.commit()
            print(">>")
        # import requests
        # a = requests.get('http://www.hitsz.edu.cn/teacher/id-14.html')
        # print(a.content)
        # name_pattern = re.compile(r'danwei">\s*?(\S*?)\s*?</div')
        # name_match = name_pattern.findall(unicode(a))
        # print(name_match[0])
        # name_pattern = re.compile(r'd="yjfx">[\s\S]*?d><p>\s*?(\S*?)\s*?</p>')
        # name_match = name_pattern.findall(unicode(a))
        # print(name_match[0])
        # name_pattern = re.compile(r'id="shjz">[\s\S]*?font size="2">\s*?(\S*?)\s*?</font></')
        # name_match = name_pattern.findall(unicode(a))
        # print(name_match[0])
        #print(html_data)
Parser()