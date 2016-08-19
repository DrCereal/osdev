#ifndef FD
#define FD

//If I move the DMA, this crap will follow too :^)
enum DMA
{
	//Slave = 0, Master = 1
	FF0 = 0x0c,
	FF1 = 0xd8,

	//Channel2 address and count registers.
	CH2_A = 0x4,
	CH2_C = 0x5,

	MASK = 0xa,
	MODE = 0xb,
	PAGE = 0x80
};

enum FDC0_REG
{
	DOR0 = 0x3f2,
	MSR0 = 0x3f4,
	DATA0 = 0x3f5,
	CTRL0 = 0x3f7
};

enum FDC1_REF
{
	DOR1 = 0x372,
	MSR1 = 0x374,
	DATA1 = 0x375,
	CTRL1 = 0x377
};

enum FLPY_GAP3
{
	GAP_STD = 42,
	GAP_5_14 = 31,
	GAP_3_5 = 27
};

enum SECTOR_SIZE
{
	S_128 = 0,
	S_256 = 1,
	S_512 = 2,
	S_1024 = 4
};

void fd_init();
void fd_read_sec(char drive, char head, char track, char sector, char nsectors);

#endif
