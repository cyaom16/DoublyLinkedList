#include <stdio.h>
#include "dll.h"

int main(void) {
   dllnode *root = NULL;
   int r = 0;

   r = dll_add_to_tail(&root, 100);
   r = dll_add_to_tail(&root, 200);
   r = dll_add_to_tail(&root, 300);
//   r = dll_print(root);
   
//   r = dll_find_by_value(root, 100);
//   
//   r = dll_del_from_tail(&root);
   
//   r = dll_del_from_head(&root);

//   
   r = dll_del_by_value(&root, 300);
   
//   r = dll_insert_in_order(&root, 50);
   
//   dllnode *new_root = NULL;
//   r = dll_add_to_tail(&new_root, 10);
//   r = dll_add_to_tail(&new_root, 20);
//   r = dll_add_to_tail(&new_root, 30);
//   r = dll_print(new_root);
   
//   r = dll_concat(&root, &new_root);
//   r = dll_sort(&root);
   
   printf("Status: %d\n", r);
   r = dll_print(root);
   r = dll_free(root);
   
   return 0;
}
