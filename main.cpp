#include <stdio.h>


#include <vector>
#include <deque>
#include <iostream>
#include <assert.h>

template <class T>
class MVector
{
    std::deque<T> m_vec;
public:

    void size(void ) const
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

};

int main(int argc, const char * argv[])
{
    using namespace std;
    printf("Hello\n");

    std::vector<int> xx;
    
    xx.push_back(10);
    cout << xx.size() << endl;
    xx.clear();
    cout << xx.size() << endl;

    MVector<double> v;


    return 0;
}
