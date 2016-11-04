import signal
import sys
import os
import time
import base64
import string
import random
from math import sin

def myh(s):
    assert(len(s) < 2**30)
    mask = 0xFFFFFFFF
    def G(X,Y,Z):
        return ((~X & Z) | (~Z & Y)) & mask
    def H(X,Y,Z):
        return (X ^ Y ^ Z & ~X) & mask
    def I(X,Y,Z):
        return (Y ^ (~Z | X) ^ Z) & mask
    def J(X,Y,Z):
        return ((~X & Z) | (~X & Z ^ ~Y)) & mask
    def K(X,Y,Z):
        return ((X ^ ~Z) | (~X & Y)) & mask
    def L(X,Y,Z):
        return ((~X & Y ^ Z) | (X & Y)) & mask
    def M(X,Y):
        return (X << Y | X >> (32 - Y)) & mask

    A = 0x7309A654
    B = 0xBC10CF74
    C = 0x3C6EF372
    D = 0x764FF52B
    E = 0x580A543F
    F = 0x9B05688C
    X = [int((mask-1) * sin(i)) & mask for i in xrange(256)]

    s_size = len(s)
    s += chr(0xb0)
    if len(s) % 72 > 64:
        while len(s) % 72 != 0: s += chr(0)
    while len(s) % 72 < 64: s += chr(0)
    s += hex(s_size * 8)[2:].rjust(16, '0').decode('hex')
    #print(len(s))
    #print(s)
    #print(s=="passwdpasswdpass||cx2mweSPDZFoCrTCJ8D6g7WbP4YPgecV||00000000000\xb0\x00\x00\x00\x00\x00\x00\x01\xf8")
    for i, ch in enumerate(s):
        k, l = ord(ch), i & 0x1f
        A = (B + M(A + G(B,C,D) + X[k], l)) & mask
        B = (C + M(B + H(C,D,E) + X[k], l)) & mask 
        C = (D + M(C + I(D,E,F) + X[k], l)) & mask
        D = (E + M(D + J(E,F,A) + X[k], l)) & mask
        E = (F + M(E + K(F,A,B) + X[k], l)) & mask
        F = (A + M(F + L(A,B,C) + X[k], l)) & mask
    return ''.join(map(lambda x : hex(x)[2:].strip('L').rjust(8, '0'), [F, A, E, D, C, B]))
def myhash(s,ss):
    assert(len(s) < 2**30)
    mask = 0xFFFFFFFF
    def G(X,Y,Z):
        return ((~X & Z) | (~Z & Y)) & mask
    def H(X,Y,Z):
        return (X ^ Y ^ Z & ~X) & mask
    def I(X,Y,Z):
        return (Y ^ (~Z | X) ^ Z) & mask
    def J(X,Y,Z):
        return ((~X & Z) | (~X & Z ^ ~Y)) & mask
    def K(X,Y,Z):
        return ((X ^ ~Z) | (~X & Y)) & mask
    def L(X,Y,Z):
        return ((~X & Y ^ Z) | (X & Y)) & mask
    def M(X,Y):
        return (X << Y | X >> (32 - Y)) & mask
    F, A, E, D, C, B=eval(sys.argv[1]),eval(sys.argv[2]),eval(sys.argv[3]),eval(sys.argv[4]),eval(sys.argv[5]),eval(sys.argv[6])
    X = [int((mask-1) * sin(i)) & mask for i in xrange(256)]
    
    s_size = len(s)
    s += chr(0xb0)
    if len(s) % 72 > 64:
        while len(s) % 72 != 0: s += chr(0)
    while len(s) % 72 < 64: s += chr(0)
    s += hex(s_size * 8)[2:].rjust(16, '0').decode('hex')
    
    ss_size = len(ss)
    ss += chr(0xb0)
    if len(ss) % 72 > 64:
        while len(ss) % 72 != 0: ss += chr(0)
    while len(ss) % 72 < 64: ss += chr(0)
    ss += hex(ss_size * 8)[2:].rjust(16, '0').decode('hex')
    #print(len(s),len(ss))
    for i in range(len(s),len(ss)):
        k, l = ord(ss[i]), i & 0x1f
        A = (B + M(A + G(B,C,D) + X[k], l)) & mask
        B = (C + M(B + H(C,D,E) + X[k], l)) & mask 
        C = (D + M(C + I(D,E,F) + X[k], l)) & mask
        D = (E + M(D + J(E,F,A) + X[k], l)) & mask
        E = (F + M(E + K(F,A,B) + X[k], l)) & mask
        F = (A + M(F + L(A,B,C) + X[k], l)) & mask
    #print(s)
    #print(ss)
    return ''.join(map(lambda x : hex(x)[2:].strip('L').rjust(8, '0'), [F, A, E, D, C, B]))
#print(myh("passwdpasswdpass||n6L93jB1n58ElGlTbH0iQ5q1BuKk0uBW||00000000000"))
#print(myh("passwdpasswdpass||n6L93jB1n58ElGlTbH0iQ5q1BuKk0uBW||00000000000\xb0\x00\x00\x00\x00\x00\x00\x01\xf8||user"))
s="||xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx||00000000000"
ss="||xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx||00000000000\xb0\x00\x00\x00\x00\x00\x00\x01\xf8||Iamroot"
for i in range(eval(sys.argv[7])):
    s="0"+s
    ss="0"+ss
print(myhash(s,ss))

