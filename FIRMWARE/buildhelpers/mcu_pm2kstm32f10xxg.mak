#Based on mcu_STM32F10xxE.mak but with 2K flash reserved for partition manager
#and now explicit second ROM bank
MEMMAP_ROMSTART=08000800
MEMMAP_ROMEND=0807FFFF
MEMMAP_RAMSTART=20000000
MEMMAP_RAMEND=20013FFF
MEMMAP_NVMEMSTART=00000000
MEMMAP_NVMEMEND=0000ffff

#default for EWARM < 8; if need be, replace in projfeatures.mak
cpu_variant?=STM32F103xG

MEMMAP_ROMSTART1=08080800
MEMMAP_ROMEND1=080F7777
CPU_ID_STRING :="$(cpu_variant)	ST $(cpu_variant)"

__SLASH__:=\ #Necessary
SEDSLASH:=$(strip $(__SLASH__))$(strip $(__SLASH__))

#IDE Debugger setup; note that there is no replacement since EWARM<8
IAR_FLASHLOADER =$$TOOLKIT_DIR$$$(SEDSLASH)config$(SEDSLASH)flashloader$(SEDSLASH)ST$(SEDSLASH)FlashSTM32F10xxG.board
CCJLinkMultiTarget:=1
OverrideDefFlashBoard=0#stmflash.ide
MemFile=$$TOOLKIT_DIR$$$(SEDSLASH)CONFIG$(SEDSLASH)debugger$(SEDSLASH)ST$(SEDSLASH)$(cpu_variant).ddf
