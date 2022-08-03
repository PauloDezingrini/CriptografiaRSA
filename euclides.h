#ifndef EUCLIDES_H
#define EUCLIDES_H

unsigned long long euclides(unsigned long long a, unsigned long long b)
{
    if (b == 0)
        return a;
    else
        return euclides(b, a % b);
}

void euclidesEstendido(unsigned long long a, unsigned long long b, unsigned long long &s, unsigned long long &t)
{
    unsigned long long r = a;
    unsigned long long r1 = b;
    unsigned long long s1 = 0;
    unsigned long long t1 = 1;
    s = 1;
    t = 0;

    unsigned long long rs, ss, ts, q;

    while (r1 != 0)
    {
        q = (unsigned long long)r / r1;
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
}

#endif