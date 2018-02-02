#include "gdt.h"
#include "string.h"


#define GDT_LENGTH 5

gdt_entry_t gdt_entries[GDT_LENGTH];

// GDTR
gdt_ptr_t gdt_ptr; 

static void gdt_set_gate(int32_t num, uint32_t base, \
	uint32_t limit, uint8_t access, uint8_t gran);

// 声明内核栈地址
extern uint32_t stack; 

void init_gdt()
{
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH -1;
    gdt_ptr.base = (uint32_t)&gdt_entries; 

    gdt_set_gate(0,0,0,0,0); // 按照 Intel 文档要求，第一个描述符必须全0
    gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf); // 代码段
    gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf); // 数据段
    gdt_set_gate(3, 0, 0xffffffff, 0xfa, 0xcf); // 用户模式代码段
    gdt_set_gate(4, 0, 0xffffffff, 0xf2, 0xcf); // 用户模式数据段

    gdt_flush((uint32_t)&gdt_ptr); // set GDTR
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xffff); 
    gdt_entries[num].base_middle = (base >> 16) & 0xff; 
    gdt_entries[num].base_high = (base >> 24) & 0xff; 

    gdt_entries[num].limit_low = (limit & 0xffff); 
    gdt_entries[num].granularity = (limit >> 16) & 0x0f; 

    gdt_entries[num].granularity |= gran & 0xf0; 
    gdt_entries[num].access = access; 
}
