#ifndef EUCLIDES_H
#define EUCLIDES_H
#include <iostream>
long long euclides(long long a, long long b)
{
    if (b == 0)
        return a;
    else
        return euclides(b, a % b);
}

long long euclidesEstendido(long long a, long long b,
                            long long &s, long long &t)
{
    long long r = a;
    long long r1 = b;
    long long s1 = 0;
    long long t1 = 1;
    s = 1;
    t = 0;

    long long rs, ss, ts, q;

    while (r1 != 0)
    {
        q = (long long)r / r1;
        rs = r;
        ss = s;
        ts = t;
        r = r1;
        s = s1;
        t = t1;
        r1 = rs - q * r1;
        s1 = ss - q * s;
        t1 = ts - q * t1;
    }

    return r;
}
#endif