/*
 * nih -- Implementation of commonly used data-structures and snippets
 * Copyright (c) 2019, 2020 Angel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <nih/list.h>
#include <stdlib.h> /* *alloc(), free() */

int list_create(struct list *listp, size_t initial_cap)
{
    if (!initial_cap)
        initial_cap = 2;
    listp->data = malloc(initial_cap * sizeof(void *));
    if (!listp->data)
        return -1;
    listp->cap = initial_cap;
    listp->len = 0;
    return 0;
}

int list_insert(struct list *listp, void *ptr)
{
    if (listp->cap == listp->len) {
        listp->data = realloc(listp->data, (2 * listp->cap) * sizeof(void *));
        if (!listp->data)
            return -1;
        listp->cap *= 2;
    }
    list_at(void *, listp, listp->len) = ptr;
    listp->len++;
    return 0;
}

int list_free(struct list *listp)
{
    listp->len = listp->cap = 0;
    if (listp->data)
        free(listp->data);
    listp->data = NULL;
    return 0;
}

int list_clone(struct list *dest, const struct list *src)
{
    if (list_create(dest, src->cap) == -1)
        return -1;
    dest->len = src->len;
    memcpy(dest->data, src->data, src->cap * sizeof(void *));
    return 0;
}
