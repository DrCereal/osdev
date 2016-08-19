#include <asm/io.h>
#include <fd.h>
#include <irq.h>

//TODO: Revamp this driver COMPLETELY. It's unoraginzed-hacked together code
//that looks like absolute trash.

extern void fd_interrupt();
volatile char fd_irq_handled = 0;
extern volatile unsigned long count;

//THE FDC IS ALWAYS IN DMA MODE!
//Who knows, maybe I'll move the dma garbage to it's own place?

static void wait_for_irq();
static void set_ccr(char val);
static void set_drive_data(char stepr, char loadt, char unloadt, char dma);
char fd_calibrate(char drive);
static void check_int(int* st0, int* cyl);

static void set_dor(char val)
{
	outb(DOR0, val);
}

static void fd_reset()
{
	int st0, cyl;
	
	set_dor(0);
	set_dor(0xc);

	wait_for_irq();

	for(int i = 0; i < 4; i++)
		check_int(&st0, &cyl);

	set_ccr(0);

	set_drive_data(3, 16, 240, 1);

	//TODO: Maybe floppy drive detection here or something?
	for(char i = 0; i < 4; i++)
		fd_calibrate(i);
}

void fd_init()
{
	//Mask channel 2.
	outb(MASK, 0x6);
	//Reset master flip flop
	outb(FF1, 0xff);
	//Set channel 2 address to 0x1000
	outb(CH2_A, 0x0);
	outb(CH2_A, 0x10);
	//Reset master flip flop
	outb(FF1, 0xff);
	//Set channel 2 count to 0x23ff (18 sectors * 512 bytes per sector = 9216 bytes)
	outb(CH2_C, 0xff);
	outb(CH2_C, 0x23);
	//Page register = 0
	outb(PAGE, 0x0);
	//Unmask channel 2
	outb(MASK, 0x2);

	fd_reset();
}

static void wait_for_irq()
{
	unsigned long lCount = count;
	while(!fd_irq_handled && (count - lCount) < 10);
	fd_irq_handled = 0;
}

static const char driveT[] = {0, 1, 2, 4};
static void toggle_motor(char state, unsigned char drive)
{
	if(drive >= 4 || state > 1)
		return;

	outb(DOR0, 0xc | driveT[drive] << 4);
	for(int i = 0; i < 10000; i++);
}

static void send_command(char cmd)
{
	for(int i = 0; i < 500; i++)
	{
		if(inb(MSR0) & 0x80)
			return outb(DATA0, cmd);
	}
}

static char read_data()
{
	for(int i = 0; i < 500; i++)
	{
		if(inb(MSR0) & 0x80)
			return inb(DATA0);
	}
	return -1;
}

static void set_ccr(char val)
{
	outb(CTRL0, val);
}

static void set_drive_data(char stepr, char loadt, char unloadt, char dma)
{
	int data = 0;

	send_command(0x3);
	
	data = (stepr << 4 | (unloadt & 0xf));
	send_command(data);

	data = loadt << 1 | (dma & 0x1);
	send_command(data);
}

static void check_int(int* st0, int* cyl)
{
	send_command(0x8);
	
	*st0 = read_data();
	*cyl = read_data();
}

char fd_calibrate(char drive)
{
	int st0, cyl;
	
	if(drive >= 4)
		return -2;

	toggle_motor(1, drive);

	for(int i = 0; i < 10; i++)
	{
		send_command(0x7);
		send_command(drive);

		wait_for_irq();
		check_int(&st0, &cyl);

		if(!cyl)
		{
			toggle_motor(0, drive);
			return 0;
		}
	}

	toggle_motor(0, drive);
	return -1;
}

char fd_seek(char drive, char cyl, char head)
{
	int st0, cyl0;
	
	if(drive >= 4)
		return -2;

	for(int i = 0; i < 10; i++)
	{
		send_command(0xf);
		send_command(head << 2 | drive);
		send_command(cyl);

		wait_for_irq();
		check_int(&st0, &cyl0);

		if(cyl == cyl0)
			return 0;
	}

	return -1;
}

//Turns on and selects drive.

static void select_drive(unsigned char drive)
{
	if(drive >= 4)
		return;

	set_dor(0xc | drive | driveT[drive]);
	for(int i = 0; i < 10000; i++);
}

void fd_read_sec(char drive, char head, char track, char sector, char nsectors)
{
	//Set DMA for READ mode.
	outb(MASK, 0x6);
	outb(MODE, 0x56);
	outb(MASK, 0x2);
	
	select_drive(drive);

	fd_seek(drive, track, 0);

	int st0, cyl;

	//Send command to read (m, s, d)
	send_command(0xe6);
	//Send parameters
	send_command((head & 1) << 2 | drive);
	send_command(track);
	send_command(head);
	send_command(sector);
	send_command(S_512);
	send_command((nsectors + 1 >= 18) ? 18 : nsectors + 1);
	send_command(GAP_3_5);
	send_command(0xff);

	wait_for_irq();

	//Do something useful with this eventually!
	for(int i = 0; i < 7; i++)
		read_data();

	check_int(&st0, &cyl);
	toggle_motor(0, drive);
}
