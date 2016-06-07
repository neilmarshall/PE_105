#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class SSS {
    private:
        vector<int> s;
        int limit;
        struct reconfig_key {int upper; int lower;} reconfig_key;
    public:
        SSS();
        ~SSS() {};
        SSS(int n);
        SSS(vector<int>);          
        void optimal_SSS(int);
        int derive_key();
        void increment(int&, bool&);
        bool isSpecialSumSet();
        int sum();
        void print();
        void print_setstring();
};