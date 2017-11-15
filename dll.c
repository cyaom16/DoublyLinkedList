#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

/* One of the lessons here is to see that if we want to use a function to malloc something that
 * is a POINTER in the CALLER of the function, then we must send in the ADDRESS of the POINTER
 * to that function.
 * 
 * Recap: if we want to use a function to modify a VARIABLE in the caller
 *        then the CALLER needs to send in the ADDRESS of the VARIABLE
 *
 * Similarly: if we want to use a function to modify a POINTER in the caller
 *            then the CALLER needs to send in the ADDRESS of the POINTER
 *
 * In the code below, ll_add_to_head and ll_add_to_tail are dynamically creating new
 * nodes to be added to the linked list. Any dynamic creation of a node must be via
 * malloc.
 */

int dll_add_to_head(dllnode **head, int val)
{
    if (head == NULL)
        return -1;
    
    dllnode *old_head;
    old_head = *head;
    
    *head = (dllnode *)malloc(sizeof(dllnode));
    (*head)->val = val;
    (*head)->next = old_head;
    (*head)->prev = NULL;
    if (old_head != NULL)
        old_head->prev = *head;
    
    return 0;
}

int dll_add_to_tail(dllnode **head, int val)
{
    if (head == NULL)
        return -1;
    
    if (*head == NULL)
        return dll_add_to_head(head, val);
    
    if ((*head)->next == NULL)
    {
        (*head)->next = (dllnode *)malloc(sizeof(dllnode));
        (*head)->next->val = val;
        (*head)->next->next = NULL;
        (*head)->next->prev = *head;
        
        return 0;
    }
    else
        return dll_add_to_tail(&((*head)->next), val);
}

int dll_print(dllnode *p)
{
    if (p == NULL)
      return 0;
    else
    {
        printf("val = %d\n",p->val);
        return dll_print(p->next);
    }
}

int dll_free(dllnode *p)
{
    if (p == NULL)
        return -1;
   else
   {
        dllnode *f = p->next;
        free(p);
        return dll_free(f);
   }
}

int dll_find_by_value(dllnode *p_list, int val)
{
    if (p_list == NULL)
        return -1;
    
    dllnode *cursor = p_list;
    while (cursor != NULL)
    {
        if (cursor->val == val)
        {
            printf("Found it!\n");
            return 0;
        }
        cursor = cursor->next;
    }
    return -1;

}

int dll_del_from_tail(dllnode **pp_list)
{
    if (pp_list == NULL || *pp_list == NULL)
        return -1;
    
    dllnode *cursor = *pp_list;
    
    if (cursor->next == NULL && cursor->prev == NULL)
    {
        printf("Only 1 element in the list\n");
        *pp_list = NULL;
        return 0;
    }
    
    if (cursor->next->next == NULL)
    {
        cursor->next = NULL;
        
        free(cursor->next);
        return 0;
    }
    else
        // Recursively finding the next
        return dll_del_from_tail(&(cursor->next));
}

int dll_del_from_head(dllnode **pp_list)
{
    if (pp_list == NULL || *pp_list == NULL )
        return -1;
    
    dllnode *front = *pp_list;

    *pp_list = (*pp_list)->next;
    (*pp_list)->prev = NULL;
    front->next = NULL;
    
    free(front);
    return 0;

}

int dll_del_by_value(dllnode **pp_list, int val)
{
    if (pp_list == NULL || *pp_list == NULL)
        return -1;
    
    dllnode *cursor = *pp_list;
    if (cursor->val == val)
    {
        printf("Found it at the front!\n");
        return dll_del_from_head(pp_list);
    }
    
    if (cursor->next == NULL)
        return -1;
    else if (cursor->next->val == val)
    {
        cursor->next = cursor->next->next;
        cursor->next->next->prev = cursor;
        cursor->next = NULL;
        free(cursor->next);
        return 0;
    }
    else
        return dll_del_by_value(&(cursor->next), val);
}

int dll_insert_in_order(dllnode **pp_list, int val)
{
    if (pp_list == NULL)
        return -1;
    
    dllnode *cursor = *pp_list;

    if (cursor->next == NULL)
        return -1;
    else if (cursor->val <= val && cursor->next->val >= val)
    {
        dllnode *insert = NULL;
        insert = (dllnode *)malloc(sizeof(dllnode));
        insert->val = val;
        insert->next = cursor->next;
        cursor->next = insert;
        return 0;
    }
    else
        return dll_insert_in_order(&(cursor->next), val);

}

int dll_concat(dllnode **p_src_a, dllnode **p_src_b)
{
    if (p_src_a == NULL)
        p_src_a = p_src_b;
    else if (p_src_b == NULL)
        return 0;
    else if (p_src_a == NULL && p_src_b == NULL)
        return -1;

    dllnode *cursor = *p_src_b;
    int r;
        
    while (cursor != NULL)
    {
        r = dll_add_to_tail(p_src_a, cursor->val);
        cursor = cursor->next;
    }
    return 0;
}

int dll_sort(dllnode **pp_list)
{
    if (pp_list == NULL)
        return -1;
    
    dllnode *head = *pp_list;
    dllnode *cursor = head;
    int tmp, swapped = 1;
    
    while (swapped)
    {
        swapped = 0;
        while (cursor->next != NULL)
        {
            if (cursor->val > cursor->next->val)
            {
                tmp = cursor->val;
                cursor->val = cursor->next->val;
                cursor->next->val = tmp;
                swapped = 1;
            }
            cursor = cursor->next;
        }
        // Reset cursor back to the front
        cursor = head;
    }
    return 0;
}