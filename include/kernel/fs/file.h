struct file
{
	int inode;
	int seek;
};

typedef struct file ST_FILE;

int file_create(ST_FILE*, char*);
int file_open(ST_FILE*, char*);
void file_write(ST_FILE*, char*, int);
int file_read(ST_FILE*, char*, int);
void file_remove(char*);
void file_get_name_by_inode(char*, int);
int file_get_size(ST_FILE);
