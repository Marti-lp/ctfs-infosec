import webbrowser
import time
import platform
import os
import subprocess
import random


def pop_browsers():
 list = ['mozilla','firefox','netscape','galeon','epiphany','skipstone','kfmclient','konqueror','kfm','mosaic','opera','grail','links','elinks','lynx','w3m','windows-default','macosx','safari','google-chrome','chrome','chromium','chromium-browser']

 for b in list:
  try:
   webbrowser.get(str(b)).open('https://www.google.com')
   webbrowser.get(str(b)).open('https://www.bing.com')
   webbrowser.get(str(b)).open('https://www.duckduckgo.com')
   webbrowser.get(str(b)).open('https://i.kym-cdn.com/photos/images/original/001/742/441/847.jpg')
  except:
   pass
     
            
def create_delete_file():
 pth = str(os.environ['USERPROFILE'])+'\c4tch_m3.asm'
 with open(pth,'w') as f:
  f.write('section   .text  \n  global    _start  \n  _start:  \n  	xor 	  esi, esi  \n  	xor       ebx, ebx  \n  	xor 	  eax, eax \n   xor       ecx, ecx \n   xor       edx, edx	 \n 	mov       ebx, 1 \n 	mov       eax, 8 \n   mov       eax, 4                   \n   mov       ecx, miss             \n   mov       edx, wrap                 \n   int 0x80 \n 	mov       eax, 8	 \n  	xor 	  esi, esi \n 	mov       eax, page \n  	xor 	  eax, eax \n 	mov       ebx, band \n  	xor       ebx, ebx \n   mov       ecx, chin \n  	xor       ecx, ecx \n 	mov       eax, 8 \n   xor       edx, edx	 \n   mov       ebx, 1                   \n   mov       eax, 4 \n   mov       edx, worm	 \n   mov       ecx, worm             \n   mov       edx, wife                  \n   int 0x80 \n  	xor 	  esi, esi \n  	xor 	  eax, eax \n 	mov       eax, 8 \n  	xor       ebx, ebx \n   xor       ecx, ecx \n   xor       edx, edx	 \n   mov       ebx, 1                   \n   mov       eax, 4                   \n   mov       ecx, back             \n   mov       edx, sigh                  \n   int 0x80 \n  	xor 	  esi, esi \n  	xor       ebx, ebx \n 	mov       eax, 8 \n  	xor 	  eax, eax \n   xor       ecx, ecx \n   xor       edx, edx \n 	mov       eax, 8	 \n   mov       ebx, 1                   \n   mov       eax, 4                   \n   mov       ecx, nail             \n   mov       edx, lung                  \n   int 0x80 \n  	xor 	  esi, esi \n  	xor       ebx, ebx \n  	xor 	  eax, eax \n   xor       ecx, ecx \n   xor       edx, edx \n 	mov       eax, 8	 \n   mov       ebx, 1 \n   mov       eax, 4                   \n   mov       ecx, park             \n   mov       edx, arch                  \n   int 0x80             \n 	mov	ebx,0		 \n 	mov	eax,1	 \n 	int	0x80  \n  section   .data  \n   \n  page: db " 0011001 010010 10001 010010 "  \n  lend: db " 01001001 010 10100 10100 0101100 "  \n  bare: db " 001101 01001 00110 1000101 0101 01 01010010 1010 1001"  \n  pick: db " 00010001010 0100101 010010 010 101 101 10 10010010 100101"  \n  fuel: db " 010101 010001 001001 00100101 010101 10010010"  \n  miss:  db "00110011 01110011 00110011 01110100 01011"  \n  wrap: equ $-miss  \n  feel: equ $-wrap  \n  sick: db " 01010 010100010 01010001 01001010 1001010010"  \n  cake: equ $-sick  \n  loud: db "11000 1001001 010101 010010 1000010"  \n  folk: equ $-loud  \n  jest: db " 001010 010001 0101001 010101 0101010"  \n  prey: db " 0001010 1001000 1000101 0100101 010000101001 0100101001 0101010"  \n  back: db " 01011111 01111011 01100010 "  \n  sigh: equ $-back  \n  fool: db " 00101001 0100101 0101001 0101010 010010 100101 010100 1110"  \n  park: db "010 00110100 01010011 01101001 01100011 01011010 01111101"  \n  arch: equ $-park  \n  time: db " 11100010 0101010 10010101 01010 010"  \n  kick: db " 110010 1001001 01001 010100101 0101010 0101001 100101"  \n  cook: equ $-kick  \n  well: db " 010010101 01010101 01010010 1001001 010101001 010100101 0101001"  \n  worm: db "111 01000101 01001011 00110000 00110010 00110010"  \n  wife: equ $-worm  \n  thaw: db " 01010101 000111 01010101 01001010 10010010 1010101 0100101 0100101"  \n  boom: equ $-thaw  \n  palm: db " 0010100101 0101010 1001001 01001010 010010101 010100101 01010101"  \n  nail: db "00110100 01000011 01001011 01110100 01101111 01000"  \n  lung: equ $-nail  \n  pole: db " 01010010 01010011 010010101 01010010 10010101 10100101 0101010 01010101"  \n  chin: db "  10100101 010100101 0101010 100101010 010100101 0101001 0101001 010101 0100101"  \n  band: equ $-chin')
 f.close()
 time.sleep(2)
 os.remove(pth)


def pop_folders():
 flds = os.listdir("C:\\")
 for fld in flds:
  subprocess.Popen('explorer C:\\'+fld)


      
if __name__ == "__main__":
 pop_browsers()
 pop_folders()
 create_delete_file()

