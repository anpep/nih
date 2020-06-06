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

#pragma once

#include <string.h> /* size_t, memcpy() */

struct list {
    /* list buffer */
    void *data;
    /* capacity */
    size_t cap;
    /* current length */
    size_t len;
};

#define list_at(t, l, i) ((t *) (l)->data)[i]

int list_create(struct list *listp, size_t initial_cap);
int list_insert(struct list *listp, void *ptr);
int list_free(struct list *listp);

int list_clone(struct list *dest, const struct list *src);

#ifdef _NIH_IMPL
#include "../src/list.c"
#endif /* NIH_IMPL */