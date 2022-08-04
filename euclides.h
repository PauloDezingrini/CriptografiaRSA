#ifndef EUCLIDES_H
#define EUCLIDES_H
#include <iostream>
 long long euclides( long long a,  long long b)
{
    if (b == 0)
        return a;
    else
        return euclides(b, a % b);
}

 long long euclidesEstendidoxxxxx( long long a,  long long b,
                                      long long &s,  long long &t)
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
        q = ( long long)r / r1;
        rs = r;
        ss = s;
        ts = t;
        r = r1;
        s = s1;
        t = t1;
        // if (r % r1 == 0)
        //     return r1;
        r1 = rs - q * r1;
        s1 = ss - q * s;
        t1 = ts - q * t1;
        std::cout << "RRR " << r << "\n";
    }
    
    return r;
}
 long long euclidesEstendido( long long n1,  long long n2,  long long &s,  long long &t)
{
    s = 1;
    t = 0;

     long long newS = 0, newT = 1;
     long long aux, q;

    do
    {
        q = ( long long)n1 / n2;

        aux = s - (newS * q);
        s = newS;
        newS = aux;

        aux = t - (newT * q);
        t = newT;
        newT = aux;

        aux = n1 % n2;

        if (aux == 0)
            return n2;

        n1 = n2;
        n2 = aux;

    } while (true);
}

#endif