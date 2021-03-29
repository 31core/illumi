struct file
{
	int index;
	int seek;
};

void CreateFile(struct file *file, char*); //创建文件