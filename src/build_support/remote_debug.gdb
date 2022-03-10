set disassembly-flavor att



define qq
  set confirm off
  quit
end

#break _asm_kernel_start
#break stage5
#break interrupts.c:107 if interrupt_num == 0x30
#break interrupts.c:107 if interrupt_num == 0x31 
#break interrupts.c:107 if interrupt_num == 0x32 
#break interrupts.c:131