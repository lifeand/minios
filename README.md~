# miniOS

记录一下自己写微型内核的过程

Sun Jan 28 18:42:43 CST 2018 

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


http://article.yeeyan.org/view/197439/167363


http://wiki.ubuntu.com.cn/%E8%B7%9F%E6%88%91%E4%B8%80%E8%B5%B7%E5%86%99Makefile:%E4%B9%A6%E5%86%99%E8%A7%84%E5%88%99#.E4.BC.AA.E7.9B.AE.E6.A0.87
