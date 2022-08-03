#ifndef EUCLIDES_H
#define EUCLIDES_H

unsigned int euclides(unsigned int a, unsigned int b)
{
    if (b == 0)
        return a;
    else
        return euclides(b, a % b);
}

unsigned int euclidesEstendidoxxx(unsigned int a, unsigned int b,
                                  unsigned int &s, unsigned int &t)
{
    unsigned int r = a;
    unsigned int r1 = b;
    unsigned int s1 = 0;
    unsigned int t1 = 1;
    s = 1;
    t = 0;

    unsigned int rs, ss, ts, q;

    while (r1 != 0)
    {
        q = (unsigned int)r / r1;
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
    }
    // cout << "bbbbb " << b << endl;
    return r;
}
unsigned int euclidesEstendido(unsigned int n1, unsigned int n2, unsigned int &s, unsigned int &t)
{
    s = 1;
    t = 0;

    unsigned int newS = 0, newT = 1;
    unsigned int aux, q;

    do
    {
        q = (unsigned int)n1 / n2;

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