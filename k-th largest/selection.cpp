#include <stdexcept>
#include "selection.h"
using namespace std;

int select(size_t k, const int* list, size_t N) {
    // TODO(student): solve the selection problem
    if (N == 0 || k == 0 || k > N){
        throw invalid_argument("Invalid argument.");
    }
    
    int *copy = new int[N];
    int *sorted = new int[N];

    for (size_t i = 0;i < N; ++i){
        copy[i] = list[i];
    }

    for (size_t i = 0; i < k; ++i){
        int num = copy[0];
        int elim = 0;
        sorted[i] = copy[0];
        for (size_t j = 1; j < N; ++j){
            if (num < copy[j]){
                elim = j;
                num = copy[j];
                sorted[i] = copy[j];
            }
        }
        copy[elim] = -100000000;

    }
    int a = sorted[k-1];
    delete[] copy;
    delete[] sorted;
    return a;
}
 