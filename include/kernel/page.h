void page_init(void);
unsigned int* page_alloc(void);
void page_free(void*);
void page_enable(void);
void page_set_table(unsigned int*, short, short, void*);
void page_set_table_entry(unsigned int*, short, void*);
void page_set(unsigned int*, int);
void set_cr3(void*);