
#include <iostream>
#include "numbers.dat"
// Data - массив
// Size - размер массива

bool* sieve(bool *primes, const size_t size) {
    for (size_t i = 2; i < size; i++) {
        primes[i] = true;
    }
    primes[1] = false;
    primes[0] = false;
    for (size_t i = 2; i < size; i++) {
        if(primes[i]) {
            for (size_t j = 2 * i; j < size; j += i) {
                primes[j] = false;
            }
        }
    }
    return primes;
}


int counter(const int* Data, int Size, int start, int stop, const bool* primes, int primes_size){
    if(start >= stop){
        return 0;
    }
    int answer = 0;
    bool check = false;
    for(int i = 0; i < Size; i++){
        if(Data[i] == start){
            for(int j = i; j < Size; j++){
                if(primes[Data[j]]){
                    answer++;
                }
                if(Data[j] == stop){
                    check = true;
                }
                if(Data[j] > stop){
                    break;
                }
            }
            break;
        }
    }
    if(check){
        return answer;
    }
    return 0;
}
int main(int argc, char* argv[]) {
    const size_t primes_size = (size_t) Data[Size - 1] + 1;
    bool *primes = new bool[primes_size];
    if(argc % 2 != 1 || argc == 1){
        return -1;
    }
    primes = sieve(primes, primes_size);
    for(int i = 1; i < argc; i += 2)
    {
        int start = std::atoi(argv[i]), stop = std::atoi(argv[i + 1]);
        std::cout << counter(Data, Size, start, stop, primes, primes_size) << std::endl;
    }
    delete[] primes;
    return 0;
}