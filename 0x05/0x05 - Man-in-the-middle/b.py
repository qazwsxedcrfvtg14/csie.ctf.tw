import signal, sys, os, time
import hashlib
print(eval(sys.argv[1])^int(hashlib.sha512(sys.argv[2]).hexdigest(), 16))


