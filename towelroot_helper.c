#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <asm/unistd.h>
#include <asm/page.h>
#include <linux/syscalls.h>

#define SYS_CALL_TABLE          /* deleted from source */
#define NR_SYS_UNUSED           223

//Pointers to re-mapped writable pages
unsigned int** sct;
int g_len=0;
int g_stack=0;

// this system call is only added to make the task easier.
// no need to analyze/exploit this function. just use it as an helper for real-world exploit.
asmlinkage long sys_unknown(int n){
        char buf[4096];
        int i=0;
        for(i=0; i<4096; i++){
                buf[i] = n;
        }
        buf[4095]=0;
        g_len=strlen(buf);
        g_stack=&buf;
        while(1){
                schedule();
        }
        return 0;
}

static int __init initmodule(void ){
        sct = (unsigned int**)SYS_CALL_TABLE;
        sct[NR_SYS_UNUSED] = sys_unknown;       // it's vanilla kernel, no kernel hardning what so ever.
        printk("sys_unknown(syscall number : 223) is added(this is NOT for pwning)\n");
        return 0;
}

static void __exit exitmodule(void ){
        return;
}

module_init( initmodule );
module_exit( exitmodule );
MODULE_LICENSE("GPL");

