# coding: utf-8
from __future__ import print_function
from __future__ import unicode_literals
import random
import sys
reload(sys)
sys.setdefaultencoding('utf-8')


def gcd(a, b):
    while 1:
        if a < b:
            temp = a
            a = b
            b = temp
        if b == 0:
            return a
        c = a % b
        a = b
        b = c


def get_random_b(fai_n):
    while True:
        b = random.randint(1, fai_n)
        print(b)
        if gcd(fai_n, b) == 1:
            print(gcd(fai_n, b))
            break
    return b


def extgcd(a, b, x_list, y_list):
    if b==0:
        x_list[0] = 1
        y_list[0] = 0
        return a
    else:
        extgcd(b, a%b, y_list, x_list)
        y_list[0] -= (a/b) * x_list[0]


def get_inverse(t, p):
    print("开始寻找元素的逆。。")
    print(p)
    inverse = 1
    count = p
    while count!=0:
        if (t*count) % p == 1:
            inverse = count
            break
        count -= 1
    # for i in range(p)[1:]:
    #     if (t*i) % p == 1:
    #         inverse = i
    #         break
    print(t, "的乘法逆为", inverse)
    return inverse


# 快速指数算法
def fast_exponentiation_algorithm(x, e, m):
    y = 1
    while True:
        if e%2==1:
            y = x*y%m
            e -= 1
        else:
            x = x*x%m
            e /= 2
        if e==0:
            return y


def encrypt(plaintext, b, n):
    return fast_exponentiation_algorithm(plaintext, b, n)


def decrypt(encryptedtext, a, n):
    return fast_exponentiation_algorithm(encryptedtext, a, n)


# 素数检测 146页 Miller-Rabin算法
def pseudo_prime_test(n):
    t = n-1
    count = 0
    m = 1
    while True:
        if t%2!=0:
            m = t
            break
        else:
            t /= 2
            count += 1
    k = count
    a = random.randint(1, n-1)

    b = fast_exponentiation_algorithm(a, m, n)
    #b = a**m % n
    if b % n == 1:
        return True
    for i in range(k):
        if b % n == -1:
            return True
        else:
            b = b**2 % n
    return False


def main():

    plaintext = int(raw_input("请输入要加密的数字明文:"))

    while True:
        big_number = random.randint(10000000000000000, 90000000000000000)
        if big_number % 2 == 1:
            print("p:", big_number)
            if pseudo_prime_test(big_number):
                break
    p = big_number
    while True:
        big_number = random.randint(10000000000000000, 90000000000000000)
        if big_number % 2 == 1:
            print("q:", big_number)
            if pseudo_prime_test(big_number):
                break
    q = big_number

    n = p*q
    fai_n = (p-1)*(q-1)
    b = get_random_b(fai_n)
    a_list = [1]
    x_list = [1]
    extgcd(b, fai_n, a_list , x_list)
    a = a_list[0]
    if a < 0:
        a += fai_n
    print("公钥为 (", str(n), str(b), ")")
    print("私钥为 (", str(p), str(q), str(a), ")")

    aa = encrypt(plaintext, b, n)
    bb = decrypt(aa, a, n)

    print("经过RSA算法后， 密文为", str(aa))
    print("经过RSA算法后， 明文为", str(bb))


if __name__ == '__main__':
    """
    @ author: 150420120
    """
    main()
