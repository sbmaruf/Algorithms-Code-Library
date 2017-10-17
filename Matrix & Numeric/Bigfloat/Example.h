#include "bigfloat.h"

int driver(int argc, char**argv)
{
    for (int i=-100; i<=100; ++i)
    {
        BigFloat aa(i);
        aa.Div(100);
        BigFloat bb(aa);
		bb.Exp().Ln().Sub(aa);
        BigFloat cc(aa);
		cc.ATan().Tan().Sub(aa);
        BigFloat dd(aa);
		dd.ASin().Sin().Sub(aa);
        BigFloat ee(aa);
		ee.ACos().Cos().Sub(aa);
        printf("%f  %g  %g  %g  %g\n",
               aa.ToDouble(),
               bb.ToDouble(),
               cc.ToDouble(),
               dd.ToDouble(),
               ee.ToDouble());
    }
    
    // find what degree formula to generate
    ASSERT(argc == 2, "usage: multistep 5, to get 11th degree (5*2+1=11)\n");
    int halfDegree;
    sscanf(argv[1], "%d", &halfDegree);
    ASSERT(halfDegree > 0, "half degree must be at least 1");
    int degree = 2*halfDegree+1;

    // build polynomials of the appropriate degree, and second derivative
    BigFloat *p2 = new BigFloat[3*degree];  // position: poly of degree
    BigFloat *p = &p2[degree];
    BigFloat *a2 = new BigFloat[3*degree];  // acceleration: poly of degree-2
    BigFloat *a = &a2[degree];
    for (int i=0; i<3*degree; ++i)
    {
        BigFloat x(1);
        BigFloat c(i-degree);
        for (int j=0; j<degree-3; ++j)
            x.Mult(c);
        a2[i].Copy(x);
        a2[i].Mult((degree-1)*(degree-2));
        x.Mult((i-degree)*(i-degree));
        p2[i].Copy(x);
    }

    // allocate the matrix
    BigFloat **m = new BigFloat*[halfDegree]();
    for (int i=0; i<halfDegree; ++i)
        m[i] = new BigFloat[halfDegree+1];

    // fill in the matrix using the appropriate polynomials
    // p-3 - p-2 - p2 + p3 == c0*(a1 + a1) + c1*(a-2 + a2)
    // c0, c1 are what we are solving for
    for (int i=0; i<halfDegree; ++i)
    {
        for (int j=0; j<halfDegree; ++j)
        {
            m[i][j].Copy(a[i-j-1]);
            m[i][j].Add(a[i+j+1]);
        }
        m[i][halfDegree].Copy(p[i-1-halfDegree]);
        m[i][halfDegree].Sub(p[i-halfDegree]);
        m[i][halfDegree].Sub(p[i+halfDegree]);
        m[i][halfDegree].Add(p[i+1+halfDegree]);
    }

    // Solve for the coefficients
    BigFloat::GaussianElimination(m, halfDegree, halfDegree);

    // report the coefficients
    for (int i=0; i<halfDegree; ++i)
    {
        BigFloat num;
        BigFloat denom;
        m[i][halfDegree].ToFraction(num, denom);
        num.PrintHex();
        printf(" / ");
        denom.PrintHex();
        printf("\n");
    }
    return 0;
}


int main(int argc, char**argv)
{
    try
    {
        return driver(argc, argv);
    }
    catch( const std::exception & ex )
    {
        fprintf(stderr, "%s\n", ex.what());
        return 1;
    }
}
