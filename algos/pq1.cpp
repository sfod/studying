#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

long merge(int *A, int anum, int *B, int bnum)
{
    std::vector<int> res;

    long z = 0;

    int n = anum + bnum;
    int i = 0;
    int j = 0;
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
            z += anum - i;
        }
    }

    std::copy(res.data(), res.data() + res.size(), A);

    return z;
}

long count_inv(const int *nums, int num, int *res)
{
    if (num <= 1) {
        if (num == 1) {
            *res = *nums;
        }
        return 0;
    }

    int n = num / 2;
    long x = count_inv(nums, n, res);
    long y = count_inv(nums + n, num - n, res + n);
    long z = merge(res, n, res + n, num - n);

    return x + y + z;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<int> nums;

    const char *filename = argv[1];
    std::ifstream infile(filename);

    std::string line;
    while (std::getline(infile, line)) {
        nums.push_back(std::stoi(line));
    }

    int *res = new int[nums.size()];
    long ci = count_inv(nums.data(), nums.size(), res);
    std::cout << "invariants " << ci << std::endl;

    for (size_t i = 0; i < nums.size(); ++i) {
        // std::cout << res[i] << std::endl;
    }
    delete[] res;

    return EXIT_SUCCESS;
}
