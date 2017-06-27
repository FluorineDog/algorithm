#ifndef DOG_NTT_H 
#define DOG_NTT_H

#include <vector>
using ull = unsigned long long;
using TimeDomain = std::vector<ull>;
using FreqDomain = std::vector<ull>;

TimeDomain init(const std::vector<int>& number);
void regular(TimeDomain& td);
FreqDomain fft(const TimeDomain& td);
TimeDomain rfft(const FreqDomain& fd);
FreqDomain multiply(const FreqDomain &fd1, const FreqDomain &fd2);
#endif // DOG_NTT_H 