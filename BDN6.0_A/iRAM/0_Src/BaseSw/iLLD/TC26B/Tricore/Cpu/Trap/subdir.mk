################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/BaseSw/iLLD/TC26B/Tricore/Cpu/Trap/IfxCpu_Trap.c 

OBJS += \
./0_Src/BaseSw/iLLD/TC26B/Tricore/Cpu/Trap/IfxCpu_Trap.o 

C_DEPS += \
./0_Src/BaseSw/iLLD/TC26B/Tricore/Cpu/Trap/IfxCpu_Trap.d 


# Each subdirectory must supply rules for building sources it contributes
0_Src/BaseSw/iLLD/TC26B/Tricore/Cpu/Trap/%.o: ../0_Src/BaseSw/iLLD/TC26B/Tricore/Cpu/Trap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\AppSw" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\AppSw\CpuGeneric" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\AppSw\CpuGeneric\Config" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\AppSw\Tricore" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\AppSw\Tricore\Main" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\_Build" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\_Impl" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\_Lib" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\_Lib\DataHandling" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\_Lib\InternalMux" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\_PinMap" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Asclin" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Asclin\Asc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Asclin\Lin" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Asclin\Spi" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Asclin\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6\Icu" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmBc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmHl" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6\Timer" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Ccu6\TPwm" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cif" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cif\Cam" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cif\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cpu" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cpu\CStart" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cpu\Irq" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cpu\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Cpu\Trap" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dma" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dma\Dma" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dma\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dsadc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dsadc\Dsadc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dsadc\Rdc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dsadc\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dts" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dts\Dts" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Dts\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Emem" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Emem\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Eray" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Eray\Eray" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Eray\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Eth" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Eth\Phy_Pef7071" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Eth\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Fce" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Fce\Crc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Fce\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Fft" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Fft\Fft" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Fft\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Flash" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Flash\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gpt12" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gpt12\IncrEnc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gpt12\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Pwm" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\PwmHl" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Timer" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim\In" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Pwm" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\PwmHl" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Timer" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Gtm\Trig" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Hssl" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Hssl\Hssl" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Hssl\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\I2c" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\I2c\I2c" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\I2c\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Iom" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Iom\Driver" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Iom\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Msc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Msc\Msc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Msc\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Mtu" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Mtu\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Multican" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Multican\Can" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Multican\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Port" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Port\Io" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Port\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Psi5" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Psi5\Psi5" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Psi5\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Psi5s" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Psi5s\Psi5s" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Psi5s\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Qspi" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiMaster" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiSlave" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Qspi\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Scu" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Scu\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Sent" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Sent\Sent" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Sent\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Smu" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Smu\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Src" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Src\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Stm" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Stm\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Stm\Timer" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Vadc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Vadc\Adc" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\iLLD\TC26B\Tricore\Vadc\Std" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Infra" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Infra\Platform" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Infra\Platform\Tricore" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Infra\Platform\Tricore\Compilers" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Infra\Sfr" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Infra\Sfr\TC26B" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Infra\Sfr\TC26B\_Reg" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\_Utilities" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\If" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\If\Ccu6If" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\StdIf" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\SysSe" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\SysSe\Bsp" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\SysSe\Comm" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\SysSe\General" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\SysSe\Math" -I"E:\AURIX\TC264\10demoHightec\Hightec_TC264_ASCLIN_ASC\0_Src\BaseSw\Service\CpuGeneric\SysSe\Time" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -DAPPKIT_TC265B -fshort-double -mcpu=tc26xx -mversion-info -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


