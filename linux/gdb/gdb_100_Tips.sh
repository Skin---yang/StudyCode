#
# 这是GDB一些小技巧和窍门
#

1. 查看函数的名字
    info functions 
        这样会列出所有可执行文件中的所有函数名称
    
    info functions regex xx*  
        这样的情况则会显示xx*名称的函数 带有正则表达式

    demain: https://sourceware.org/gdb/onlinedocs/gdb/Symbols.html

2. 提示过程中是否进入带有调试信息的函数
    step(s)
        这样可以直接进入带有调试信息的函数中，如果不需要进入，直接n即可

    set step-mode on
        执行该语句可以进入没有调试信息的函数
        
    demain: https://sourceware.org/gdb/onlinedocs/gdb/Continuing-and-Stepping.html

3. 如果想要执行函数
        call + functionnanme
        print + functionname
            以上两条语句均可以做到


4. 打印函数的堆栈
    info(s) frame
        
    demain: https://sourceware.org/gdb/onlinedocs/gdb/Frame-Info.html

5. 打印尾调用堆栈帧信息
    当一个函数最后一条指令是调用另外一个函数时，开启优化选项的编译器常常以最后被调用的函数返回值作为调用者的返回值，这称之为“尾调用（Tail call）
        可以通过设置    debug entry-values 的值为非0值而查看
        example: set debug entry-values 1 

    demain: https://sourceware.org/gdb/onlinedocs/gdb/Tail-Call-Frames.html


6. 当使用bt查看堆栈的时候，对于第几层的数据可以使用
    frame(f) n 来查看代码

    ########################################################
    (gdb) bt
    #0  func1 (a=10) at test.c:5
    #1  0x0000000000400560 in func2 (a=10) at test.c:11
    #2  0x0000000000400586 in func3 (a=10) at test.c:18
    #3  0x000000000040059e in main () at test.c:24
    (gdb) frame 2
    #2  0x0000000000400586 in func3 (a=10) at test.c:18
    18              c = 2 * func2(a);
    ########################################################

    可以用 "up n"或"down n"命令向上或向下选择函数堆栈帧，其中n是层数

    demain: https://sourceware.org/gdb/onlinedocs/gdb/Selection.html#Selection



