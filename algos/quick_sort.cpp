#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>


static int m1 = 0;
static int m2 = 0;

void swap(int *a, int *b)
{
    if (a == b) {
        return;
    }

    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(std::vector<int> &a, int l, int r)
{
    int p = a[l];
    int i = l + 1;

    for (int j = l + 1; j <= r; ++j) {
        if (a[j] < p) {
            swap(&a[i], &a[j]);
            ++i;
        }
    }
    swap(&a[l], &a[i - 1]);

    return i - 1;
}

// left: 162085
// right: 164123
// median: 138382
int choose_pivot(std::vector<int> &a, int l, int r)
{
    int mi = (r + l) / 2;
    int ln = a[l];
    int mn = a[mi];
    int rn = a[r];

    // std::cout << "array: ";
    for (int i = l; i <= r; ++i) {
        // std::cout << a[i] << " ";
    }
    // std::cout << std::endl;

    // std::cout << "elements: " << ln << " " << mn << " " << rn << std::endl;

    if ((ln < mn && mn < rn) || (rn < mn && mn < ln)) {
        // std::cout << "middle element " << a[mi] << ": idx " << mi << std::endl;
        return mi;
    }
    if ((mn < ln && ln < rn) || (rn < ln && ln < mn)) {
        // std::cout << "left element " << a[l] << ": idx " << l << std::endl;
        return l;
    }

    // std::cout << "right element " << a[r] << ": idx " << r << std::endl;
    return r;
}

void quick_sort(std::vector<int> &a, int l, int r)
{
    m1 += r - l;

    if (r <= l) {
        return;
    }

    m2 += r - l;

    int pi = choose_pivot(a, l, r);
    swap(&a[l], &a[pi]);

    pi = partition(a, l, r);
    if (l < pi - 1) {
        quick_sort(a, l, pi - 1);
    }
    if (pi + 1 < r) {
        quick_sort(a, pi + 1, r);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream infile(argv[1]);
    std::vector<int> nums(std::istream_iterator<int>(infile), {});

    quick_sort(nums, 0, nums.size() - 1);
    for (auto n : nums) {
        std::cout << n << std::endl;
    }

    std::cout << "m1 is " << m1 << std::endl;
    std::cout << "m2 is " << m2 << std::endl;

    return EXIT_SUCCESS;
}
