#ifndef OS_IDT_H
#define OS_IDT_H

#include <stdint.h>

// SOURCE: http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

//
// A struct describing an interrupt gate
//
struct idt_entry_struct
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;

} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.

} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;


idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;


extern void idt_flush(uint32_t);

void init_descriptor_table();

static void init_idt();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

// These extern directives let us access the addresses of our ASM ISR handlers.


#endif