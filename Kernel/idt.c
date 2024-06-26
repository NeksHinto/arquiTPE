#include <stdint.h>
#include <idt.h>
#include <defs.h>
#include <interrupts.h>

/** ================================== */
/**        IDT ENTRY DESCRIPTOR        */
/** ================================== */

/** Backup current alignment */
#pragma pack(push)
/** Change alignment to 1-byte for packing the struct */
#pragma pack (1)

/* Interruption descriptor */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} idt_entry;

/** Restore alignment */
#pragma pack(pop)
/** ================================== */

/** IDT of 256 entries  */
idt_entry * idt = (idt_entry *) 0;

static void setup_IDT_entry (int index, uint64_t offset);

void load_idt() {

  _cli();

  setup_IDT_entry (0x20, (uint64_t)&_irq00Handler);      // Timer Tick (8254)
  setup_IDT_entry (0x21, (uint64_t)&_irq01Handler);      // Keyboard
  setup_IDT_entry (0x00, (uint64_t)&_exception0Handler); // Division by zero
  setup_IDT_entry (0x06, (uint64_t)&_exception6Handler); // Invalid opcode
  setup_IDT_entry (0x80, (uint64_t)&_syscallHandler);

  // TimerTick interruptions only
  picMasterMask(0xFC);
  picSlaveMask(0xFF);

  _sti();
}

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}
