#include "SSS.hpp"

SSS::SSS() {
    s.resize(0);
}

SSS::SSS(int n) {
    limit = n - 2;
    for (int i = 0; i < n; ++i) {
        s.push_back(limit + i);
    }
}

SSS::SSS(vector<int> v) {s = v;}

void SSS::optimal_SSS(int n) {

    // return the vector {1} if n = 1
    if(n == 1) {s.push_back(1); return;}

    // recursively generate prior optimal special sum sets
    optimal_SSS(n - 1);

    // calculate minimal first element
    int key = derive_key();

    // calculate maximal value for optimal special sum set
    s.push_back(0);
    int max_sum = 0;
    for (int i = 1; i < n; ++i) {
        s[i] = s[i  -1] + key;
        s[0] = key;
    }
    max_sum = sum();

    // re-set s to be empty then populate with n elements, key, key + 1, ..., key + n - 1
    s.clear();
    for (int i = 0; i < n; ++i) {
        s.push_back(key + i);
    }

    // generate and test each possible SSS
    bool canIncrement = true;
    vector<int> sOptimal;
    while (canIncrement) {
        if (sum() <= max_sum) {
            if (isSpecialSumSet()) {
                max_sum = sum();
                sOptimal = s;
            }
        }
        increment(max_sum, canIncrement);
    }
    s = sOptimal;
}

int SSS::derive_key() {
    int dMax = 0;
    for (int i = 1; i < s.size(); ++i) {
        int d = 0;
        int l = 0;
        int u = 0;
        for (int j = 0; j < i; ++j) {
            l += s[j];
            u += s[s.size() - 1 - j];
        }
        d = u - l;
        if (d > dMax) dMax  = d;
    }
    return dMax + 1;
}

void SSS::increment(int& limit, bool& canIncrement) {
    int position;
    if (sum() < limit) {
        position = s.size() - 1;
    }
    else {
        position = s.size() - 1;
        do {
            --position;
            if (position < 0) {
                canIncrement = false;
                break;
            }
        } while ((s[position + 1] - s[position]) == 1);
    }
    ++s[position];
    for (int i = position + 1; i < s.size(); ++i) {
        s[i] = s[i - 1] + 1;
    }
}
  
bool SSS::isSpecialSumSet() {
    int bigSum;
    int littleSum;
    for (int p = 1; p < s.size(); ++p) {
        bigSum = 0;
        littleSum = 0;
        for (int i = p; i < s.size(); ++i) {
            littleSum += s[i];
        }
        for (int i = 0; i <= (s.size() - p); ++i) {
            bigSum += s[i];
        }
        if (littleSum > bigSum) return false;
    }
    vector<int> sums;
    sums.push_back(s[0]);
    for (int i = 1; i < s.size(); ++i) {
        int sumsize = sums.size();
        for (int j = 0; j < sumsize; ++j) {
            sums.push_back(s[i] + sums[j]);
        }
        sums.push_back(s[i]);
    }
    sort(sums.begin(), sums.end());
    for (int i = 0; i < sums.size() - 1; ++i) {
        if (sums[i] == sums[i + 1]) return false;
    }
    return true;
}

int SSS::sum() {
    int sum = 0;
    for (int i = 0; i < s.size(); ++i) {
        sum += s[i];
    }
    return sum;
}

void SSS::print() {
    for (int i = 0; i < s.size(); ++i) {
        cout << s[i] << ", ";
    }
    cout << endl;
}

void SSS::print_setstring() {
    string elem = "";
    string elems = "";
    for (int i = 0; i < s.size(); ++i) {
        elem = to_string(s[i]);
        elems += elem;
    }
    cout << elems << '\n';
}
