## illumi kernel
### 一. 简介
#### 0x0 主要功能
* 内存管理
* 多任务
* 文件系统
* 设备管理 (未实现)
* API系统调用 (未实现)

#### 0x1 目录说明
|  目录  |  说明  |
|-------|--------|
|arch   | 存放cpu架构相关代码.|
|include| 存放头文件.|
|init   | 内核入口点.|
|kernel | 系统内核代码.|
|device | 存放一些设备的驱动代码.|
|lib    | 常用函数库.|
|doc    | 存放了操作系统开发文档.|
|config | 内核编译时的配置文件.|
|tools  | 一些实用工具.|
#### 0x2 内核架构
```
USER MODE:
+-------------------------+
|       Applications      |
+-------------------------+
|   syscall | libs        |
+-------------------------+
KERNEL MODE:
 +-----------------------+
 |      interrupts       |
 +-----------------------+
 |      Kernel           |
 +-----------------------+
 |      Hardware         |
 +-----------------------+
```

### 二. 编译与调试
#### 0x0 编译环境
```shell
$ sudo apt install nasm build-essential qemu-system-x86 #Debian based system
$ sudo yum install nasm make gcc qemu #Redhat based system
```

#### 0x1 命令行选项
```shell
$ make #编译
$ make run #编译并运行
$ make clean #清理输出文件
```
