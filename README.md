# OS-Exp
本仓库用于记录北京工业大学操作系统实验，仅用于熟悉、了解Linux系统、进程、线程、通信。

不同的exp文件夹对应的不同的实验序号。

分别是C源代码和Unix下的可执行文件（Linux和MacOS
下均可直接执行）

## exp2 进程创建和管道通信

### exp2
    进程并发。一个父进程创建两个子进程。父进程输出1000个a，两个子进程分别输出1000个b和1000个c。没有用信号量进行管理。

### exp2_pipe
    进程间的管道通信。这里是父子进程用匿名管道进行通信，最基本的生产者消费者模型。父进程写操作，子进程读操作。

## exp3 线程管理

### exp3
    最基本的线程创建和退出。两个线程，一个输出一个字符，一个输出一个整型数。

### exp3_extra
    两个进程，分别对同一个数组排序。一个从大到小输出，一个从小到大输出。（排序采用的递归快排，倒序排序直接把顺序反过来存放了，懒orz...）

## exp4 信号量实现线程互斥与同步

    1.dat和2.dat分别存十个数。两个线程reader1，reader2分别从1.dat和2.dat中读数，还有两个线程用于专做加法和乘法。

### exp4
    reader1和reader2抢占读，往一个长度为2的buffer里放。只要buffer满了，所有读线程停止读，运算线程开始抢占算。操作数来自于buffer中，第一操作数和第二操作数不一定非要来在1.dat和2.dat。

### exp4_ex
    同上，但是第一操作数必须来自1.dat，第二操作数必须来自2.dat。加法、乘法必须轮流做。

## exp5 基于消息队列和共享内存的进程间通信

### exp5_msg
    读进程和写进程，通过消息队列传递。写进程从键盘中读输入，如果是exit则退出。读进程负责输出写入的字符串。

### exp5_shm
    读进程和写进程，通过共享内存来访问。同一块内存，写进程写，读进程读，输出输入数的平方。

## exp6 使用信号量进行通信

### exp6
    自定义了SIGINT和SIGUSR1的信号量，输入 Ctrl + C 时，程序不会中断，会输出用户自己定义的内容。