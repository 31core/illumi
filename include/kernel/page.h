extern unsigned int *kernel_page_dir;
extern unsigned int *page_dirs[];

void page_init(void);
unsigned int* page_alloc(void);
void page_free(void*);
void page_enable(void);
void page_disable(void);
void page_set_table(unsigned int*, short, short, unsigned int);
void page_set_dir(unsigned int*, short, unsigned int);
void page_set(unsigned int*, unsigned int, unsigned int);
void* page_add(unsigned int*, unsigned int);
void page_unset(unsigned int*, unsigned int);
void page_switch(void*);
void set_cr3(void*);