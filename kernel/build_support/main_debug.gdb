set disassembly-flavor att

tui enable
tui new-layout example {-horizontal src 1 asm 1} 2 status 0 cmd 1
layout example 

file /usr/local/osdev/versions/v/build/versionv.bin
directory /usr/local/osdev/versions/v/kernel

target remote localhost:5894

define qq
  set confirm off
  quit
end

#break _asm_kernel_start
#break stage5
#break interrupts.c:107 if interrupt_num == 0x30
#break interrupts.c:107 if interrupt_num == 0x31 
#break *0x0010aaaa
break debug.cpp:30
break debug.cpp:39
break kernel.c:83