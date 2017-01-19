#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <math.h>
#include "MVector.h"
#include <map>

using namespace std;
double mainFunc(const vector<double>&);

double g_zero_Tol = 0.5;

template <size_t Dim, class scale_t>
class MFunction
{
    scale_t m_domain_h;
    mutable map< MVector<scale_t>, scale_t> m_func_val;
public:

    MFunction(void):
        m_domain_h(1),
        m_func_val()
    {}

    scale_t func(const MVector<scale_t> & x) const
    {

        {
            typedef map< MVector<scale_t>, scale_t> map_t;
            typename map_t::const_iterator itr = m_func_val.find(x);

            if (itr != m_func_val.end())
                return itr->second;

            vector<scale_t> vx;
            for (size_t i = 0; i < x.size(); ++i)
            {
                vx.push_back(x[i]);
            }
            scale_t ret = mainFunc(vx);
            m_func_val[x] = ret;

            return ret;
        }

        //test code
#if 0
        scale_t ret = 0;
        for (size_t i = 0; i != x.size(); ++i)
        {
            ret += x[i]*x[i];
        }
        return ret;
#endif
    }

    scale_t parital_dif(int dir, const MVector<scale_t> & x) const
    {
        MVector<scale_t> rx = x;
        MVector<scale_t> lx = x;
        rx[dir] += m_domain_h;
        lx[dir] -= m_domain_h;

        return (func(rx) - func(lx))/(2*m_domain_h);
    }

    MVector<scale_t> gradient(const MVector<scale_t> & x) const
    {
        MVector<scale_t> ret;
        for (size_t i = 0; i != Dim; ++i)
        {
            ret.push_back(parital_dif(i, x));
        }
        return ret;
    }


};


template <size_t dim>
double gradent_descent_scale(const MVector<double> & init_x)
{
//    #define DEBUG_GD

    int N = 20;
    int g_end_tol = 1;

    MFunction<dim, double> mf;
    MVector<double> x = init_x;
    MVector<double> x_ret;

    double g1 = 0;
    double z0 = 0;

    MVector<double> z;

    int itr_times = 0;
    for (int i = 0; i < N; ++i)
    {
        ++itr_times;
#ifdef DEBUG_GD
        printf("--- frame %d/%d----\n", i, N);
#endif

        g1 = mf.func(x);
        z  = mf.gradient(x);
        z0 = z.norm();

#ifdef DEBUG_GD
        cout << "g1 = " << g1 << endl;
        z.show();
        cout << "grad norm = " << z0 << endl;
#endif


        if (z0 < g_zero_Tol)
        {
#ifdef DEBUG_GD
            cout << "norm(gd) < tol: " << z0 << endl;
#endif
            x_ret = x;
            break;
        }

        //normalize
        z = z/z0;
#ifdef DEBUG_GD
        cout << "grad (normalize) = " << z0 << endl;
        z.show();
#endif

        double extream_val = -1*(1 << 20);
        MVector<double> next_x;
        for (int i = 0; i < 5; ++i)
        {
            const MVector<double> & rx = (x + i*z).roundInt();

#ifdef DEBUG_GD
            cout << "round :" ;
            sx.roundInt().show();
#endif

            double tmp_val = mf.func(rx);

            if (tmp_val > extream_val)
            {
                extream_val = tmp_val;
                next_x = rx;
            }
        }

#ifdef DEBUG_GD
        cout << "next x = ";
        next_x.show();
#endif

        //double next_val = mf.func(next_x);
        double next_val = extream_val;
        double err = abs(next_val - g1);
#ifdef DEBUG_GD
        cout << "err = " << err << endl;
#endif
        if (err < g_end_tol)
        {
#ifdef DEBUG_GD
            cout << "END" << endl;
#endif
            x_ret = x;
            break;
        }
        x = next_x;
    }


    if (itr_times > N - 2)
    {
        printf("over itr times = %d\n", itr_times);
        exit(0);
    }


    cout << "retx = ";
    //x_ret.show();
    cout << x_ret;
//    x_ret.show();
    cout << "val = " << mf.func(x_ret) << endl;
    cout <<"-------------------" << endl;
    return 0;
}

int main(int argc, const char * argv[])
{
    const size_t dim = 5;

    MFunction<dim, double> mf;
    vector<double> hp;

    extern vector<string> g_data;
    string line;
    while (cin >> line)
         g_data.push_back(line);

    int bd = 128;
    int step = 1;

    for (int i1 = -bd; i1 < 0; i1 += step)
    {
        double tva[dim] = {i1, 0, 0, 0, 0};
        MVector<double> mtv(tva, tva + dim);

        printf("i1 = %d ->", i1);
        gradent_descent_scale<dim>(mtv);

    }

    return 0;
}

