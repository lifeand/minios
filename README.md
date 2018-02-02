## miniOS

记录一下自己写微型内核的过程

Sun Jan 28 18:42:43 CST 2018 
### gcc 内联汇编
```
   asm ( assembler template
	        
	   : output operands               (optional)
	        
	   : input operands                (optional)
	        
	   : list of clobbered registers   
	       (optional)
	            
       );
```
如
```
{
int a=10, b;
asm ("movl %1, %%eax;
		         
movl %%eax, %0;"
:"=r"(b)  /* output */    
:"r"(a)       /* input */
:"%eax"); /* clobbered register */
}
```
常见约束
寄存器约束 r 
a %eax
b %ebx
c %ecx
d %edx
S %esi
D %edi
内存操作数约束 m 
匹配（数字) 约束 

### Multiboot
```
uint32_t magic
uint32_t flags
uint32_t checksum
uint32_t header_addr
uint32_t load_addr
uint32_t load_end_addr
uint32_t bss_end_addr
uint32_t entry_addr
uint32_t mode_type
uint32_t width
uint32_t height
uint32_t depth
```

magic: 0x1BADB002
flags: 0位表示 所有引导模块按页(4kb) 对齐
       1位表示 	必须通过multiboot 信息结构
       16位 物理地址开启
checksum: magic + flags

Multiboot 头的地址域
flags 的第16位开启后的地址域都是物理地址
head\_addr 即multiboot 开始的位置
load\_addr 从OS 映像文件中的多大偏移开始载入由头位置的偏移量定义，相减(header\_addr - load\_addr) 
load\_end\_endr load\_end\_addr - load\_addr 指出引导程序要载入多少数据，，这暗示了text 和data 段必须在OS 映像中连续
bss\_end\_addr 包含bss 段结束处的物理地址，如果为0，引导程序假定没有bss 段
entry\_addr 操作系统入口点

当引导程序启动后，在内核入口点，机器状态如下
eax = 0x2BADB002
ebx 指向multiboot 的信息结构
ds,es,fs,gs,ss 未确定值
a20 开启

multiboot 信息格式

```
uint32_t flags
uint32_t mem_lower    
uint32_t mem_uppper   
uint32_t boot_device  
uint32_t cmdline      


```







## 打印到屏幕

显存地址位于0xB8000 ,每个记录占16位
16   12,11      8,7    0
|backcolor|Forecolor|Character|

|value|Color|value|Color|
|0|Black|8|black grey|
|1|blue | 9| LIGHT BLUE|
|2|GREEN|10|LIGHT GREEN|
|3|cyan|11|light cyan|
|4|red|12|light red|
|5|magenta|13|light magenta|
|6|brown|14|light brown|
|7|light grey|15|white|

设置VGA 控制器,通过0x3D4 端口来设置寄存器， 0x3D5 来设置该寄存器的值
14号和15号寄存器对应显存的一个单位的高地址和低地址

```
outb(0x3d4, 14)
outb(0x3d5, value)
outb(0x3d4, 15)
outb(0x3d5, value)

```




段描述符 
struct gdt_entry_t {
    uint16_t limit_low; // 段限长
    uint16_t base_low; // 段基址
    uint8_t base_middle; // 段基址
    uint8_t access; // P|DPL|S|Type
    uint8_t granularity; // G|D/B|L/AVL/Seg.Limit
    uint8_t base_high; // 段基址
} __attribute__((packed)) gdt_entry_t; 
    
GDTR
0-15 全局描述符表边界
16-47 全局描述表基址

CR0 寄存器
0 号位 表示CPU 的运行状态， 0 为实模式， 1 为保护模式




multiboot: http://blog.csdn.net/uframer/article/details/373900
http://article.yeeyan.org/view/197439/167363


http://wiki.ubuntu.com.cn/%E8%B7%9F%E6%88%91%E4%B8%80%E8%B5%B7%E5%86%99Makefile:%E4%B9%A6%E5%86%99%E8%A7%84%E5%88%99#.E4.BC.AA.E7.9B.AE.E6.A0.87

https://www.ibm.com/developerworks/cn/linux/sdk/assemble/inline/


