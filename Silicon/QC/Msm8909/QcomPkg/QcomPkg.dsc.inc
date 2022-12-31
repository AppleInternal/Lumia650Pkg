## @file
#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018 - 2019, Bingxing Wang. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

[BuildOptions.common]
  *_GCC5_ARM_CC_FLAGS = -fno-stack-protector
  *_GCC5_ARM_DLINK_FLAGS = -fno-stack-protector
  # Use Clang 11+ actually, some fixes are builtin
  *_CLANG38_ARM_CC_FLAGS = -Wno-unused-const-variable -Wno-sometimes-uninitialized -D CLANG
  *_CLANG38_ARM_DLINK_FLAGS = 
  *_*_*_CC_FLAGS = -D DISABLE_NEW_DEPRECATED_INTERFACES -D HAS_MEMCPY_INTRINSICS

[BuildOptions.common.EDKII.DXE_CORE,BuildOptions.common.EDKII.DXE_DRIVER,BuildOptions.common.EDKII.UEFI_DRIVER,BuildOptions.common.EDKII.UEFI_APPLICATION]
  *_*_*_DLINK_FLAGS = -z common-page-size=0x1000

[BuildOptions.common.EDKII.DXE_RUNTIME_DRIVER]
  *_*_ARM_DLINK_FLAGS = -z common-page-size=0x1000
  *_*_AARCH64_DLINK_FLAGS = -z common-page-size=0x10000

[PcdsFeatureFlag.common]
  gQcomPkgTokenSpaceGuid.PcdIsLkBuild|FALSE

  gQcomTokenSpaceGuid.PcdMmcHs200Caps|FALSE

[PcdsFixedAtBuild.common]
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000         # Starting address
  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x80C40000
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|19200000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|18
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|19
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x0b000000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x0b002000

  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemRevision|0x00008909
  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x80C00000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000      # 256K stack
  gEmbeddedTokenSpaceGuid.PcdInterruptBaseAddress|0x0b000000
  gEmbeddedTokenSpaceGuid.PcdPrePiCpuIoSize|16

  gLumiaFamilyPkgTokenSpaceGuid.PcdSmbiosProcessorModel|"Snapdragon (TM) 210 @ 1.10 GHz"
  gLumiaFamilyPkgTokenSpaceGuid.PcdSmbiosProcessorRetailModel|"MSM8909"
  gArmPlatformTokenSpaceGuid.PcdCoreCount|4
  gArmPlatformTokenSpaceGuid.PcdClusterCount|1
  #gQcomPkgTokenSpaceGuid.PsciCpuSuspendAddress|0x6c03aa8

  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000         # 2GB Base

  # UART
  gLumiaFamilyPkgTokenSpaceGuid.PcdUartSerialBase|0x078AF000

  gQcomPkgTokenSpaceGuid.PcdUefiMemPoolSize|0x7800000
  gQcomPkgTokenSpaceGuid.PcdPreAllocatedMemorySize|0x20000000  # Start here

  # SoC Drivers GPIO TLMM
  gQcomTokenSpaceGuid.PcdGpioTlmmBaseAddress|0x1000000
  gQcomTokenSpaceGuid.PcdGpioTlmmSummaryIrq|240
  gQcomTokenSpaceGuid.PcdGpioTlmmIoOffset|0x1004
  gQcomTokenSpaceGuid.PcdGpioTlmmIoElementSize|0x10
  gQcomTokenSpaceGuid.PcdGpioTlmmCtlOffset|0x1000
  gQcomTokenSpaceGuid.PcdGpioTlmmCtlElementSize|0x10
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrCfgOffset|0x1008
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrCfgElementSize|0x10
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrStatusOffset|0x100c
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrStatusElementSize|0x10
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrTargetOffset|0x1008
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrTargetElementSize|0x10
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrEnableBit|0
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrStatusBit|0
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrAckHigh|FALSE
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrTargetBit|5
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrTargetKpssValue|4
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrRawStatusBit|4
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrPolarityBit|1
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrDetectionBit|2
  gQcomTokenSpaceGuid.PcdGpioTlmmIntrDetectionWidth|2
  gQcomTokenSpaceGuid.PcdGpioTlmmInBit|0
  gQcomTokenSpaceGuid.PcdGpioTlmmOutBit|1
  gQcomTokenSpaceGuid.PcdGpioTlmmOeBit|9
  gQcomTokenSpaceGuid.PcdGpioTlmmMuxBit|2
  gQcomTokenSpaceGuid.PcdGpioTlmmDrvBit|6
  gQcomTokenSpaceGuid.PcdGpioTlmmPullBit|0
  gQcomTokenSpaceGuid.PcdGpioTlmmNumFunctions|12

  # SoC Drivers SPMI
  gQcomTokenSpaceGuid.PcdSpmiBaseAddress|0x02000000

  # SoC Drivers MMC
  gQcomTokenSpaceGuid.PcdSdccMciHcMode|0x00000078
  gQcomTokenSpaceGuid.PcdSdccHcPwrctlStatusReg|0x000000DC
  gQcomTokenSpaceGuid.PcdSdccHcPwrctlMaskReg|0x000000E0
  gQcomTokenSpaceGuid.PcdSdccHcPwrctlClearReg|0x000000E4
  gQcomTokenSpaceGuid.PcdSdccHcPwrctlCtlReg|0x000000E8
  gQcomTokenSpaceGuid.PcdMmcSdhciDdrCfgVal|0x80040870 # DDR_CFG_DLY_VAL
  gQcomTokenSpaceGuid.PcdMmcSdc1HdrvPullCtlOffset|0x00002044
  gQcomTokenSpaceGuid.PcdMmcSdc2HdrvPullCtlOffset|0x00002048

  # SoC Drivers Misc
  gQcomTokenSpaceGuid.PcdGicSpiStart|32

  # SoC Drivers UARTDM
  gQcomTokenSpaceGuid.PcdUartDmClkRxTxBitRate|0xCC

  # SoC Drivers I2C
  gQcomTokenSpaceGuid.PcdGicSpiStart|32

  # Device Driver Synaptics 3202
  gQcomPkgTokenSpaceGuid.SynapticsCtlrAddress|0x4b
  gQcomPkgTokenSpaceGuid.SynapticsCtlrResetPin|38
  gQcomPkgTokenSpaceGuid.SynapticsCtlrIntPin|77
  gQcomPkgTokenSpaceGuid.SynapticsCtlrI2cDevice|5

  # RPM
  gQcomTokenSpaceGuid.PcdApcsAlias0IpcInterrupt|0xB011008
  gQcomTokenSpaceGuid.PcdSmdIrq|200

  # SMEM
  gQcomTokenSpaceGuid.PcdMsmSharedBase|0x87D00000
  gQcomTokenSpaceGuid.PcdMsmSharedSize|0x00200000

  # Variable Services
  # Each Size of 0xA0000
  # gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase|0x80000000
  # gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize|0x000A0000
  # gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase|0x800A0000
  # gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareSize|0x000A0000
  # gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase|0x80140000
  # gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize|0x000A0000
  # gQcomPkgTokenSpaceGuid.PcdNvStorageVolatileStorageBase|0x801E0000

  # eMMC should have block size of 512 bytes. (Assert)
  # Allocate 640KB (less than provisioned) so 500 blocks
  # And times 3 for other regions
  # And it starts at the beginning of the logical partition of "uefi_vars"
  # Synchronize the change in LK when the size changes
  # gQcomPkgTokenSpaceGuid.PcdNvStorageVariableBlockCount|3840
  # gQcomPkgTokenSpaceGuid.PcdNvStorageVariableBlockSize|512
  # gQcomPkgTokenSpaceGuid.PcdNvStorageVariableBlockLba|0
  # gQcomPkgTokenSpaceGuid.PcdNvStorageScratchAddress|0x90000000

  # Timer
  gQcomTokenSpaceGuid.PcdIntDebugTimerExp|41
  gQcomTokenSpaceGuid.PcdQTimerBase|0xF9021000

[LibraryClasses.common]
  PlatformMemoryMapLib|QcomPkg/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf
  PlatformPeiLib|QcomPkg/PlatformPei/PlatformPeiLib.inf
  PlatformPrePiLib|QcomPkg/Library/PlatformPrePiLib/PlatformPrePiLib.inf
  AslUpdateLib|LumiaFamilyPkg/Library/DxeAslUpdateLib/DxeAslUpdateLib.inf

  AcpiPlatformUpdateLib|QcomPkg/Library/AcpiPlatformUpdateLib/AcpiPlatformUpdateLib.inf
  PlatformThemeLib|QcomPkg/Library/PlatformThemeLib/PlatformThemeLib.inf

  # SoC Drivers
  InterruptsLib|QcomPkg/Library/InterruptsLib/InterruptsLib.inf
  MallocLib|QcomPkg/Library/MallocLib/MallocLib.inf
  KeypadDeviceHelperLib|QcomPkg/Library/KeypadDeviceHelperLib/KeypadDeviceHelperLib.inf
  KeypadDeviceImplLib|QcomPkg/Library/KeypadDeviceImplLib/KeypadDeviceImplLib.inf
  DloadUtilLib|QcomPkg/Library/DloadUtilLib/DloadUtilLib.inf
  QcomPlatformClockInitLib|QcomPkg/Library/QcomPlatformClockInitLib/QcomPlatformClockInitLib.inf
  QcomPlatformMmcLib|QcomPkg/Library/PlatformMmcLib/QcomPlatformMmcLib.inf
  QcomPlatformMmcClockOverrideLib|QcomPkg/Library/QcomPlatformMmcClockOverrideLib/QcomPlatformMmcClockOverrideLib.inf
  QcomTargetMmcSdhciLib|QcomPkg/Library/TargetMmcSdhciLib/QcomTargetMmcSdhciLib.inf
  LcmLib|QcomPkg/Library/LcmLib/LcmLib.inf
  MicroLibC|MicroLibC/MicroLibC.inf
  StrLib|QcomPkg/Library/StrLib/StrLib.inf
  QcomPlatformI2cQupLib|QcomPkg/Library/StaticQcomPlatformI2cQupLib/StaticQcomPlatformI2cQupLib.inf
  SmemLib|QcomPkg/Driver/SmemDxe/SmemImplLib.inf
  SmemPtableLib|QcomPkg/Driver/SmemPtableDxe/SmemPtableImplLib.inf
  PTableLib|QcomPkg/Library/PTableLib/PTableLib.inf
  SsbiLib|QcomPkg/Driver/SsbiDxe/SsbiImplLib.inf
  BoardLib|QcomPkg/Driver/BoardDxe/BoardImplLib.inf
  QcomTargetBoardLib|QcomPkg/Library/QcomTargetBoardLib/QcomTargetBoardLib.inf
  PlatformIdLib|QcomPkg/Library/PlatformIdLib/PlatformIdLib.inf
  QTimerLib|QcomPkg/Library/QTimerLib/QTimerLib.inf

  # RTC Private
  Pm8x41LibRtcPrivate|QcomPkg/Driver/Pm8x41Dxe/Pm8x41ImplLib.inf
  SpmiLib|QcomPkg/Driver/SpmiDxe/SpmiImplLib.inf
  Pm8x41Lib|QcomPkg/Driver/Pm8x41Dxe/Pm8x41ImplLib.inf

  # System Reset
  ArmHvcLib|ArmPkg/Library/ArmHvcLib/ArmHvcLib.inf
  EfiResetSystemLib|QcomPkg/Library/QcomPmicResetSystemLib/QcomPmicResetSystemLib.inf
  RuntimeSpmiLib|QcomPkg/Library/RuntimeSpmiLib/RuntimeSpmiLib.inf
  RuntimeSpmiMemoryConfiguratorLib|QcomPkg/Library/RuntimeSpmiMemoryConfiguratorLib/RuntimeSpmiMemoryConfiguratorLib.inf

  # PCI Express Dependencies
  QcomPlatformClock2Lib|QcomPkg/Library/QcomPlatformClock2Lib/QcomPlatformClock2Lib.inf

[LibraryClasses.common.SEC]
  # SoC Drivers
  GpioTlmmLib|QcomPkg/GPLDriver/GpioTlmmDxe/GpioTlmmImplLib.inf
  SpmiLib|QcomPkg/Driver/SpmiDxe/SpmiImplLib.inf
  Pm8x41Lib|QcomPkg/Driver/Pm8x41Dxe/Pm8x41ImplLib.inf
  ClockLib|QcomPkg/Driver/ClockDxe/ClockImplLib.inf
  SmemLib|QcomPkg/Driver/SmemDxe/SmemImplLib.inf
  SmemPtableLib|QcomPkg/Driver/SmemPtableDxe/SmemPtableImplLib.inf
  PTableLib|QcomPkg/Library/PTableLib/PTableLib.inf
  RpmLib|QcomPkg/Driver/SmdRpmDxe/RpmLib.inf
  SsbiLib|QcomPkg/Driver/SsbiDxe/SsbiImplLib.inf
  BoardLib|QcomPkg/Driver/BoardDxe/BoardImplLib.inf
  QcomTargetBoardLib|QcomPkg/Library/QcomTargetBoardLib/QcomTargetBoardLib.inf
  PlatformIdLib|QcomPkg/Library/PlatformIdLib/PlatformIdLib.inf

[LibraryClasses.common.DXE_DRIVER]
  # SoC Drivers
  GpioTlmmLib|QcomPkg/GPLDriver/GpioTlmmDxe/GpioTlmmLib.inf
  SpmiLib|QcomPkg/Driver/SpmiDxe/SpmiImplLib.inf
  Pm8x41Lib|QcomPkg/Driver/Pm8x41Dxe/Pm8x41ImplLib.inf
  ClockLib|QcomPkg/Driver/ClockDxe/ClockLib.inf
  I2cQupLib|QcomPkg/Driver/I2cQupDxe/I2cQupLib.inf
  SmemLib|QcomPkg/Driver/SmemDxe/SmemImplLib.inf
  SmemPtableLib|QcomPkg/Driver/SmemPtableDxe/SmemPtableImplLib.inf
  PTableLib|QcomPkg/Library/PTableLib/PTableLib.inf
  RpmLib|QcomPkg/Driver/SmdRpmDxe/RpmLib.inf
  SsbiLib|QcomPkg/Driver/SsbiDxe/SsbiImplLib.inf
  BoardLib|QcomPkg/Driver/BoardDxe/BoardImplLib.inf
  QcomTargetBoardLib|QcomPkg/Library/QcomTargetBoardLib/QcomTargetBoardLib.inf
  PlatformIdLib|QcomPkg/Library/PlatformIdLib/PlatformIdLib.inf
  QcomDxeTimerLib|QcomPkg/Library/QTimerLib/QcomQTimerDxeTimerLib.inf

[LibraryClasses.common.UEFI_APPLICATION]
  # SoC Drivers
  GpioTlmmLib|QcomPkg/GPLDriver/GpioTlmmDxe/GpioTlmmLib.inf
  SpmiLib|QcomPkg/Driver/SpmiDxe/SpmiImplLib.inf
  Pm8x41Lib|QcomPkg/Driver/Pm8x41Dxe/Pm8x41ImplLib.inf
  ClockLib|QcomPkg/Driver/ClockDxe/ClockLib.inf
  SmemLib|QcomPkg/Driver/SmemDxe/SmemImplLib.inf
  SmemPtableLib|QcomPkg/Driver/SmemPtableDxe/SmemPtableImplLib.inf
  PTableLib|QcomPkg/Library/PTableLib/PTableLib.inf
  RpmLib|QcomPkg/Driver/SmdRpmDxe/RpmLib.inf
  SsbiLib|QcomPkg/Driver/SsbiDxe/SsbiImplLib.inf
  BoardLib|QcomPkg/Driver/BoardDxe/BoardImplLib.inf
  QcomTargetBoardLib|QcomPkg/Library/QcomTargetBoardLib/QcomTargetBoardLib.inf
  PlatformIdLib|QcomPkg/Library/PlatformIdLib/PlatformIdLib.inf

[LibraryClasses.common.DXE_RUNTIME_DRIVER]
  # System Reset
  ArmHvcLib|ArmPkg/Library/ArmHvcLib/ArmHvcLib.inf
  EfiResetSystemLib|QcomPkg/Library/QcomPmicResetSystemLib/QcomPmicResetSystemLib.inf
  HwResetSystemLib|ArmPkg/Library/ArmSmcPsciResetSystemLib/ArmSmcPsciResetSystemLib.inf

[Components.common]
  # SoC Drivers (Cross-referenced from EFIDroid)
  QcomPkg/Driver/BamDxe/BamDxe.inf
  QcomPkg/GPLDriver/GpioTlmmDxe/GpioTlmmDxe.inf
  QcomPkg/GPLDriver/GpioTlmmInterruptDxe/GpioTlmmInterruptDxe.inf
  QcomPkg/Driver/SpmiDxe/SpmiDxe.inf
  QcomPkg/Driver/Pm8x41Dxe/Pm8x41Dxe.inf
  QcomPkg/Driver/GenericKeypadDeviceDxe/GenericKeypadDeviceDxe.inf
  QcomPkg/Driver/KeypadDxe/KeypadDxe.inf
  QcomPkg/Driver/ClockDxe/ClockDxe.inf
  QcomPkg/Driver/SdhciMMCHSDxe/SdhciMMCHS.inf
  QcomPkg/Driver/I2cQupDxe/I2cQupDxe.inf
  QcomPkg/Driver/SmemDxe/SmemDxe.inf
  QcomPkg/Driver/SmemPtableDxe/SmemPtableDxe.inf
  QcomPkg/Driver/SmdRpmDxe/RpmDxe.inf
  QcomPkg/Driver/SsbiDxe/SsbiDxe.inf
  QcomPkg/Driver/BoardDxe/BoardDxe.inf
  QcomPkg/Driver/RuntimeMemoryConfigDxe/RuntimeMemoryConfigDxe.inf
  QcomPkg/Driver/TimerDxe/TimerDxe.inf

  # Device Drivers
  QcomPkg/Driver/SynapticsTouchDxe/SynapticsTouchDevice.inf
  QcomPkg/Driver/SynapticsTouchDxe/SynapticsTouchDxe.inf


  # Graphics Driver
  LumiaFamilyPkg/Driver/SimpleFbDxe/SimpleFbDxe.inf

  QcomPkg/GPLDriver/QupSpiDxe/QupSpiDxe.inf

  LumiaFamilyPkg/Driver/SmBiosTableDxe/SmBiosTableDxe.inf

  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf

  LumiaFamilyPkg/Driver/GpioButtons/GpioButtons.inf