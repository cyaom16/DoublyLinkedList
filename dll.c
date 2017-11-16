#include <stdio.h>
#include <stdlib.h>
#include "dll.h"


int dll_add_to_head(dllnode **head, int val)
{
    if (head == NULL)
        return -1;
    if (*head == NULL)
    {
        *head = (dllnode *)malloc(sizeof(dllnode));
        (*head)->val = val;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return 0;
    }
    
    dllnode *old_head = *head;
    *head = (dllnode *)malloc(sizeof(dllnode));
    (*head)->val = val;
    (*head)->next = old_head;
    (*head)->prev = NULL;
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
            return 0;
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
        *pp_list = NULL;
        return 0;
    }
    if (cursor->next == NULL)
    {
        cursor->prev->next = NULL;
        free(cursor);
        return 0;
    }
    else
        return dll_del_from_tail(&(cursor->next));
}

int dll_del_from_head(dllnode **pp_list)
{
    if (pp_list == NULL || *pp_list == NULL )
        return -1;
    if ((*pp_list)->next == NULL && (*pp_list)->prev == NULL)
    {
        *pp_list = NULL;
        return 0;
    }
    
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
    if (cursor->val == val && cursor->prev == NULL)
        return dll_del_from_head(&cursor);
    if (cursor->next == NULL)
    {
        if (cursor->val != val)
            return -1;
        else
        {
            cursor->prev->next = NULL;
            free(cursor);
            return 0;
        }
    }
    else if (cursor->val == val)
    {
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;
        free(cursor);
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
    if (cursor->next == NULL && cursor->prev == NULL && cursor->val >= val)
        return dll_add_to_head(&cursor, val);
    if (cursor->next == NULL && cursor->val <= val)
        return dll_add_to_tail(&cursor, val);
    else if (cursor->val <= val && cursor->next->val >= val)
    {
        dllnode *insert = NULL;
        insert = (dllnode *)malloc(sizeof(dllnode));
        insert->val = val;
        insert->next = cursor->next;
        cursor->next = insert;
        insert->prev = cursor;
        cursor->next->prev = insert;
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
        cursor = head;
    }
    return 0;
}