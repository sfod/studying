#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

void merge(int *A, int anum, int *B, int bnum)
{
    std::vector<int> res;

    int n = anum + bnum;
    int i = 0;
    int j = 0;
    if (0) {
        for (int k = 0; k < n; ++k) {
            if ((j == bnum) || (A[i] < B[j])) {
                res.push_back(A[i]);
                ++i;
            }
            else if ((i == anum) || (B[j] < A[i])) {
                res.push_back(B[j]);
                ++j;
            }
        }
    }
    else {
        for (int k = 0; k < n; ++k) {
            if (i == anum) {
                std::copy(B + j, B + bnum, std::back_inserter(res));
                break;
            }
            else if (j == bnum) {
                std::copy(A + i, A + anum, std::back_inserter(res));
                break;
            }

            if (A[i] < B[j]) {
                res.push_back(A[i]);
                ++i;
            }
            else {
                res.push_back(B[j]);
                ++j;
            }
        }
    }

    std::copy(res.data(), res.data() + res.size(), A);
}

void sort(const int *nums, int num, int *res)
{
    if (num <= 1) {
        if (num == 1) {
            *res = *nums;
        }
        return;
    }

    int n = num / 2;
    sort(nums, n, res);
    sort(nums + n, num - n, res + n);

    merge(res, n, res + n, num - n);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream infile(argv[1]);
    std::vector<int> nums(std::istream_iterator<int>(infile), {});

    int *res = new int[nums.size()];
    sort(nums.data(), nums.size(), res);

    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << res[i] << std::endl;
    }
    delete[] res;

    return EXIT_SUCCESS;
}
