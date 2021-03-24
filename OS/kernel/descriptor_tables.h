#ifndef OS_IDT_H
#define OS_IDT_H

//
// Descriptor Tables
//
// SOURCE: http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
//

#include <types.h>

void init_descriptor_tables(); 

/*---------------------- GLOBAL DESCRIPTOR TABLE ----------------------------*/

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t; 

struct gdt_ptr_struct
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t; 

extern void gdt_flush(uint32_t);

// Internal function prototypes.
static void init_gdt();
static void gdt_set_gate(int32_t,uint32_t,uint32_t,uint8_t,uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

/*---------------------- ITERRUPT DESCRIPTOR TABLE ----------------------------*/

//
// Assembly ISR Handlers
//
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

//
// Struct describing an interrupt gate.
//
struct idt_entry_struct
{
    uint16_t base_low;  // Lower 16 bits of the address to jump to when interrupt fires.
    uint16_t selector;  // Kernel segment selector
    uint8_t always_0;   // This must always be zero (WHY?)
    uint8_t flags;      // More flags.
    uint16_t base_high; // Upper 16 bits of address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

//
// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for 'lidt'.
//
struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;   // The address of the first element in idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

//
// IDT and Functions
//
#define IDT_SIZE 256

idt_entry_t idt_entries[IDT_SIZE];
idt_ptr_t   idt_ptr;

extern void idt_flush
(
    uint32_t idt_ptr
);

void init_idt();
static void idt_set_gate
(
    uint8_t num,
    uint32_t base,
    uint16_t sel, 
    uint8_t flags
);


#endif