from struct import pack  
import binascii  
import string  
crc32 = lambda s: binascii.crc32(s) & 0xFFFFFFFF  
   
  
  
  
chunkname={'IHDR','cHRM','gAMA','sBIT','PLTE','bKGD','hIST',  
           'tRNS','oFFs','pHYs','sCAL','IDAT','tIME','tEXt','zTXt','fRAc',  
           'gIFg','gIFt','gIFx','IEND'}  
  
file_object = open('c.png','rb')  
text = file_object.read()  
  
  
for each in chunkname:  
    pos=0  
    while (text.find(each,pos+1)!=-1):  
        pos = text.find(each,pos+1)  
        if (pos != -1):  
            print "%s:0x%x" % (each,pos)  
        if (each=='IHDR'):  
            print " Length:0x%s" % (binascii.b2a_hex(text[pos-4:pos]))  
            print " Chunk:0x%s" % (binascii.b2a_hex(text[pos:pos+4]))  
            print " Width:0x%s" % (binascii.b2a_hex(text[pos+4:pos+8]))  
            print " Height:0x%s" % (binascii.b2a_hex(text[pos+8:pos+12]))  
            print " BitDepth:0x%s" % (binascii.b2a_hex(text[pos+12:pos+13]))  
            print " ColorType:0x%s" % (binascii.b2a_hex(text[pos+13:pos+14]))  
            print " ComdivssionMethod:0x%s" % (binascii.b2a_hex(text[pos+14:pos+15]))  
            print " FilterMethod:0x%s" % (binascii.b2a_hex(text[pos+15:pos+16]))  
            print " InterlaceMethod:0x%s" % (binascii.b2a_hex(text[pos+16:pos+17]))  
            print " CRC:0x%s" % (binascii.b2a_hex(text[pos+17:pos+21]))  
            #print  (crc32(text[pos:pos+17]))  
        if (each=='IDAT'):  
            print " Length:0x%s" % (binascii.b2a_hex(text[pos-4:pos]))  
        if (each=='PLET'):  
            print " Length:0x%s" % (binascii.b2a_hex(text[pos-4:pos]))
        if (each=='tEXt'):  
            print " Length:0x%s" % (binascii.b2a_hex(text[pos-4:pos]))  
            length = int(binascii.b2a_hex(text[pos-4:pos]),16)  
            print " Context:%s" % (text[pos+4:pos+length+4]) 