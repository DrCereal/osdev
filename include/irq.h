#ifndef IRQS
#define IRQS

void irq_init();
void set_interrupt_gate(unsigned short i, unsigned int ir);

#endif
