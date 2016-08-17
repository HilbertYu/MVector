#include <stdio.h>


#include <vector>
#include <deque>
#include <iostream>
#include <assert.h>
#include <math.h>

template <typename T>
class MVector
{
    typedef std::deque<T> vector_t;

    vector_t m_vec;
public:

    MVector(void):
        m_vec()
    {

    }

    template <typename SrcT>
    MVector(SrcT itr,  SrcT end):
        m_vec()
    {
        attach(itr, end);
    }

    template <typename SrcT>
    MVector(SrcT x):
        m_vec()
    {
        attach(x.begin(), x.end());
    }


    size_t size(void ) const
    {
        return m_vec.size();
    }

    bool empty(void) const
    {
        return m_vec.empty();
    }

    void clear(void) const
    {
        m_vec.clear();
    }

    void push_back(const T & v)
    {
        m_vec.push_back(v);
    }

    void push_front(const T & v)
    {
        m_vec.push_front(v);
    }

    T pop_back(void)
    {
        assert(!empty());
        const T & ret = m_vec.back();
        m_vec.pop_back();
        return ret;
    }

    T pop_front(const T & v)
    {
        assert(!empty());
        const T & ret = m_vec.back();
        m_vec.pop_front();
        return ret;
    }
    //=====================

    T sum(void) const
    {
        assert(!empty());
        T ret = 0;
        typename vector_t::const_iterator itr = m_vec.begin();
        for (; itr != m_vec.end(); ++itr)
            ret += *itr;
        return ret;
    }

    T mean(void) const
    {
        assert(!empty());
        return sum()/size();
    }

    T var(int nl = 0) const
    {
        assert(size() - nl > 0);
        T ret = 0;

        typename vector_t::const_iterator itr = m_vec.begin();
        T m = mean();
        for (; itr != m_vec.end(); ++itr)
            ret += pow(*itr - m, 2);
        return ret/(size()-nl);
    }

    T stddev(int nl = 0) const
    {
        assert(!empty());
        T v = var(nl);
        return sqrt(v);
    }

    void eachPower(int n)
    {
        assert(n >= 0);

        typename vector_t::iterator itr = m_vec.begin();
        for (; itr != m_vec.end(); ++itr)
        {
            *itr = pow(*itr, n);
        }

    }

    //======operators===========

    T &operator[](int idx)
    {
        return m_vec.at(idx);
    }

    const T &operator[](int idx) const
    {
        return m_vec.at(idx);
    }

    MVector<T> operator+(const MVector & v) const
    {
        assert(v.size() == m_vec.size());
        MVector<double> ret;

        for (int i = 0; i < v.size(); ++i)
        {
            ret.push_back(m_vec[i] + v[i]);
        }

        return ret;
    }

    template <class scale_t>
    MVector<T> operator+(const scale_t & x) const
    {
        assert(!empty());
        MVector<double> ret;

        for (int i = 0; i < m_vec.size(); ++i)
        {
            ret.push_back(m_vec[i] + x);
        }

        return ret;
    }


    MVector<T> operator-(const MVector & v) const
    {
        assert(v.size() == m_vec.size());
        MVector<double> ret;

        for (int i = 0; i < v.size(); ++i)
        {
            ret.push_back(m_vec[i] - v[i]);
        }

        return ret;
    }

    template <class scale_t>
    MVector<T> operator-(const scale_t & x) const
    {
        assert(!empty());
        MVector<double> ret;

        for (int i = 0; i < m_vec.size(); ++i)
        {
            ret.push_back(m_vec[i] - x);
        }

        return ret;
    }

    //---------control============

    template <typename SrcT>
    void attach(SrcT itr,  SrcT end)
    {
        m_vec.clear();
        while (itr != end)
            m_vec.push_back(*itr++);
    }

    //==============staic
    static T pow(T x, int n)
    {
        assert(n >= 0);
        T ret = 1;

        for (int i = 0; i < n; ++i)
            ret *= x;
        return ret;
    }


    //================= test
    void show(void) const
    {
        using namespace std;
        typename vector_t::const_iterator itr = m_vec.begin();
        for (; itr != m_vec.end(); ++itr)
            cout << *itr << " ";

        cout << endl;
    }

};



int main(int argc, const char * argv[])
{
    using namespace std;

    MVector<double> v;

    for (int i = 1; i <= 10; ++i)
    {
        v.push_back(i);
    }

    v[2] = 200;

    cout << v.sum() << endl;
    cout << v.mean() << endl;
    cout << v.stddev() << endl;
    cout << v.var(1) << endl;

    cout << MVector<double>::pow(2,0) << endl;

    v.show();
    v.eachPower(2);
    v.show();

    int ca[] = {1, 2, 3};

    v.attach(ca, ca + 3);
    v.show();

    vector<double> sv;
    sv.push_back(100);
    sv.push_back(200);
    sv.push_back(300);

    v.attach(sv.begin(), sv.end());
    v.show();

    MVector<double> v2(ca, ca+3);

    MVector<double> ret = v - 100;
    ret.show();

    return 0;
}
