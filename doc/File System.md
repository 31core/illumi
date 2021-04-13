### 1.1块
块(block),是文件系统管理的标准单位,1个块大小为4 kb(8扇区).
### 1.2超级块
磁盘的的一个块为文件系统的超级块,记录了文件系统的信息.  
超级块由以下结构体定义:
```c
struct super_block
{
	unsigned bitmap_block; //引导块编号
	unsigned inode_table[1024 - 1]; //inode块编号
};
```
* bitmap块: 记录了那些块可用.
* inode table块: 记录了inode数据.
### 2.inode
inode(index node)记录了一个文件的基本信息,有一下结构体定义:
```c
struct inode
{
	char name[16]; //inode(文件)名
	int parent_block;
	int index_block; //索引块编号
	int size;
	int type; //inode类型
};
```
* index_block: 索引块,记录了数据块编号
* size: 文件大小
索引块储存了一个数据块编号列表,可以通过遍历列表读取文件内容。