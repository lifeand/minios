#include "console.h"

int kern_entry()
{
    init_debug(); 

    console_clear();

//console_write_color("Hello", rc_black, rc_red);

    printk_color(rc_black, rc_green, "Hello, OS kernel!\n"); 

    panic("test");

   return 0;
}
