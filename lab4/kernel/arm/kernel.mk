ARM_OBJS := reg.o psr.o C_Irq_Handler.o C_SWI_Handler.o init_irq.o init_os_time.o Install_Handler.o irq_handler.o irq_stack_setup.o Load_User.o Restore_Handler.o S_Handler.o
ARM_OBJS := $(ARM_OBJS:%=$(KDIR)/arm/%)

KOBJS += $(ARM_OBJS)
