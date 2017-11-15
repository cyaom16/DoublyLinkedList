struct dllnode
{
    int val;                
    struct dllnode *next;
    struct dllnode *prev;
};
typedef struct dllnode dllnode;

int dll_add_to_head(dllnode **head, int val);
int dll_add_to_tail(dllnode **head, int val);
int dll_print(dllnode *p);
int dll_free(dllnode *p);

int dll_find_by_value(dllnode *p_list, int val);
int dll_del_from_tail(dllnode **pp_list);
int dll_del_from_head(dllnode **pp_list);
int dll_del_by_value(dllnode **pp_list, int val);
int dll_insert_in_order(dllnode **pp_list, int val);
int dll_concat(dllnode **p_src_a, dllnode **p_src_b);
int dll_sort(dllnode **pp_list);
