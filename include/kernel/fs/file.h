struct file
{
	int inode;
	int seek;
};

typedef struct file ST_FILE;

int file_create(struct file*, char*);
int file_open(struct file *file, char*);
void file_write(struct file*, char*, int);
int file_read(struct file*, char*, int);
void file_remove(char*);
void file_get_name_by_inode(char*, int);