# coding: utf-8
from __future__ import print_function
from __future__ import unicode_literals
import random

def gcd(a, b):
    if a < b:
        temp = a
        a = b
        b = temp
    if b == 0:
        return a
    c = a % b
    return gcd(b, c)


def get_random_b(fai_n):
    while True:
        b = random.randint(1, fai_n)
        print(b)
        if gcd(fai_n, b) == 1:
            print(gcd(fai_n, b))
            break
    return b


def get_inverse(t, p):
    inverse = 1
    for i in range(p)[1:]:
        if (t*i) % p == 1:
            inverse = i
            break
    print(t, "的逆为", inverse)
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
    b = a**m % n
    if b % n == 1:
        return True
    for i in range(k):
        if b % n == -1 or b % n == n-1:
            return True
        else:
            b = b**2 % n
    return False



def main():

    plaintext = int(raw_input("请输入要加密的明文:"))

    # 生成大素数
    while True:
        big_number = random.randint(1000, 2000)
        if big_number%2==1:
            if pseudo_prime_test(big_number):
                break
    p = big_number
    while True:
        big_number = random.randint(1000, 2000)
        if big_number%2==1:
            if pseudo_prime_test(big_number):
                break
    q = big_number

    n = p*q
    fai_n = (p-1)*(q-1)
    b = get_random_b(fai_n)
    a = get_inverse(b, fai_n)
    print("公钥为 (", str(n), str(b), ")")
    print("私钥为 (", str(p), str(q), str(a), ")")


    aa = encrypt(plaintext
                 , b, n)
    bb = decrypt(aa, a, n)


    print("经过RSA算法后， 密文为", str(aa))
    print("经过RSA算法后， 明文为", str(bb))


if __name__ == '__main__':
    main()