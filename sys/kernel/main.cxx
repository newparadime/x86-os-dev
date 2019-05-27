#include "console-vga-text.hxx"
#include "multiboot.h"
#include <stdint.h>
#include "mem_mgr.h"


extern "C" 
{

void kernel_main(uint32_t multiboot_magic, uint32_t multiboot_info_ptr) 
{
    /* Initialize terminal interface */
	//terminal_t terminal = terminal_create(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    //Terminal term(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_t term_p = terminal_create(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    printf("test write with printf!");
    terminal_writestring(term_p,i32tos(17,10)); terminal_putchar(term_p,'\n');
    
    if(multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        printf("Invalid magic number\n");
        return;
    }
    
    multiboot_info_t* const mbi = (multiboot_info_t*) multiboot_info_ptr;
    
    printf("MULTIBOOT_FLAGS: 0x%@x\n", mbi->flags);
    terminal_writestring(term_p,u32tos(mbi->flags, 16)); terminal_putchar(term_p,'\n');    
    if(mbi->flags & MULTIBOOT_MEMORY_INFO)
    {
        printf("mem_lower=0x%x, mem_upper=0x%x\n",
        
           mbi->mem_lower,
           mbi->mem_upper);
    }
 
    if((mbi->flags & MULTIBOOT_INFO_AOUT_SYMS) && (mbi->flags & MULTIBOOT_INFO_ELF_SHDR))
    {
        printf("MULTIBOOT_INFO_AOUT_SYMS and\n");
        printf("  MULTIBOOT_INFO_ELF_SHDR, both set.\n");
    }
    
    if(mbi->flags & MULTIBOOT_INFO_ELF_SHDR)
    {
        multiboot_elf_section_header_table_t* multiboot_elf_sec = &mbi->u.elf_sec;
        printf("multiboot_elf_section_header: num = %u, size = 0x%x,"
               " addr = 0x%x, shndx = 0x%x\n",
               (unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size, 
               (unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
    }
 
    if(mbi->flags & MULTIBOOT_INFO_MEM_MAP)
    {
        multiboot_mmap_t* mmap = (multiboot_mmap_t*)mbi->mmap_addr;
        printf("mmap_addr = 0x%x, mmap_length = %d(0x%x)\n",
                (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length, (unsigned) mbi->mmap_length);
        mem_mgr_init(mmap, mbi->mmap_length);
    }
    else
    {
        printf("MULTIBOOT MEMORY MAP UNAVAILABLE!\n");
    }
    
}
}

