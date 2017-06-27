#ifndef DOG_NTT_H 
#define DOG_NTT_H

#include <vector>
#include <bitset>
using ll = long long;
using TimeDomain = std::vector<ll>;
using FreqDomain = std::vector<ll>;

TimeDomain init(const std::vector<bool>& number);
void regular(TimeDomain& td);
FreqDomain ftt(const TimeDomain& td);
TimeDomain rfft(const FreqDomain& fd);
FreqDomain multiply(const FreqDomain &fd1, const FreqDomain &fd2);
#endif // DOG_NTT_H 