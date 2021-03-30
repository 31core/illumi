struct file
{
	int inode;
	int seek;
};

void CreateFile(struct file*, char*); //创建文件
int OpenFile(struct file *file, char*); //打开文件
void WriteFile(struct file*, char*, int); //写入文件
int ReadFile(struct file*, char*, int); //读取文件