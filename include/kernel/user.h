struct user
{
	char name[10];
	int uid;
};

void user_init(void);
int user_get_name(char*, int);
int user_get_uid(char*);
