KERNEL = $(KDIR)/kernel
KSTART = $(KDIR)/start.o

# All core kernel objects go here.  Add objects here if you need to.
KOBJS := assert.o main.o raise.o Install_Handler.o Restore_Handler.o exit.o read.o write.o S_Handler.o Load_User.o C_SWI_Handler.o sleep.o init_irq.o init_os_time.o irq_handler.o C_Irq_Handler.o test.o irq_stack_setup.o time.o
KOBJS := $(KOBJS:%=$(KDIR)/%)
ALL_OBJS += $(KOBJS) $(KSTART)
ALL_CLOBBERS += $(KERNEL) $(KERNEL).bin

-include $(KDIR)/arm/kernel.mk

# Put everything needed by the kernel into the final binary.
# KOBJS contains core kernel objects.
# AOBJS contains objects that are ARM dependent.
# UOBJS contains objects that are U-boot dependent.

$(KERNEL): $(KSTART) $(KOBJS) $(AOBJS) $(UOBJS)
	echo LD $(notdir $@)
	$(LD) -static $(LDFLAGS) -o $@ $^ $(LIBGCC)
