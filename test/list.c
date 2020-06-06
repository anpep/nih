#define _NIH_IMPL

#include <nih/list.h>
#include <nih/minunit.h>

MU_TEST(test_alloc)
{
    struct list l;
    const size_t cap = 4;

    mu_check(list_create(&l, cap) == 0);
    mu_check(l.data != 0);
    mu_check(l.cap == 4);
    mu_check(l.len == 0);

    mu_check(list_free(&l) == 0);
    mu_check(l.data == 0);
    mu_check(l.cap == 0);
    mu_check(l.len == 0);

    mu_check(list_free(&l) == 0);
}

MU_TEST(test_insert)
{
    struct list l;
    int dead = 0xdeadbeef;

    mu_check(list_create(&l, 0) == 0);

    for (int i = 0; i < 0xff; i++) {
        mu_check(list_insert(&l, &dead) == 0);
        mu_check(*list_at(int *, &l, i) == dead);
    }

    mu_check(l.len == 0xff);
    mu_check(l.cap >= l.len);
    mu_check(list_free(&l) == 0);
}

MU_TEST(test_clone)
{
    int i;
    struct list src;
    struct list dest;

    mu_check(list_create(&src, 0) == 0);
    for (i = 0; i < 0xff; i++)
        mu_check(list_insert(&src, &i) == 0);

    mu_check(list_clone(&dest, &src) == 0);
    mu_check(dest.data != 0);
    mu_check(dest.data != src.data);
    mu_check(dest.cap == src.cap);
    mu_check(dest.len == src.len);

    for (i = 0; i < 0xff; i++)
        mu_check(list_at(int, &src, i) == list_at(int, &dest, i));

    mu_check(list_free(&src) == 0);
    mu_check(list_free(&dest) == 0);
}

MU_TEST_SUITE(list)
{
    MU_RUN_TEST(test_alloc);
    MU_RUN_TEST(test_insert);
    MU_RUN_TEST(test_clone);
}

int main(void)
{
    MU_RUN_SUITE(list);
    MU_REPORT();
    return MU_EXIT_CODE;
}