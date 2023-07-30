./sam-ba -p usb -b sama5d27-som1-ek1 -a qspiflash -c erase
./sam-ba -p usb -b sama5d27-som1-ek1 -a qspiflash -c writeboot:images/BOOT.BIN -c verifyboot:images/BOOT.BIN
./sam-ba -p usb -b sama5d27-som1-ek1 -a qspiflash -c write:images/u-boot.bin:0x20000
./sam-ba -p usb -b sama5d27-som1-ek1 -a qspiflash -c write:images/a5d2x-rugged_board.dtb:0xA0000
./sam-ba -p usb -b sama5d27-som1-ek1 -a qspiflash -c write:images/zImage:0xB0000
./sam-ba -p usb -b sama5d27-som1-ek1 -a qspiflash -c write:images/rb-nor-core-image-minimal-rugged-board-a5d2x.squashfs:0x5B0000
./sam-ba -p usb -b sama5d27-som1-ek1 -a qspiflash -c write:images/data-image-rootfs.jffs2:0x01BB0000
./sam-ba -p usb -b sama5d27-som1-ek1 -a bootconfig -c writecfg:bscr:valid,bureg0
./sam-ba -p usb -b sama5d27-som1-ek1 -a bootconfig -c writecfg:bureg0:ext_mem_boot,sdmmc1,sdmmc0_disabled,nfc_disabled,spi1_disabled,spi0_disabled,qspi1_ioset2,qspi0_disabled
