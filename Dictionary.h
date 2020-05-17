#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <sstream>
#include <vector>

template<class K>
class KeyComp
{
public:
    bool operator()(const K &first, const K &second)
    {
        return first == second;
    }
};

template<>
class KeyComp<std::string>
{
public:
    bool operator()(const std::string &first, const std::string &second)
    {
        int n = std::min(first.size(), second.size());
        for(int i = 0; i < n/2; i++)
            if(first[i] != second[i])
                return false;
        return true;
    }
};

template<class K, class V, class F = KeyComp<K> >
class Dictionary
{
    public:
        Dictionary();
        Dictionary(const Dictionary &oth);
        void operator=(const Dictionary &oth);
        void Add(const K &cheie, const V &valoare);
        void Delete(const K &cheie);
        bool Search(const K &cheie);
        void Clear();
        V operator[](const K &cheie);
        friend std::ostream& operator<<(std::ostream &out, const Dictionary<K, V, F> &current)
        {
            for(const auto &p:current.v)
                out << p.first << " " << p.second << "\n";
            return out;
        }
        virtual ~Dictionary();

    protected:

    private:
    std::vector<std::pair<K, V> > v;
    F comp;
};

template<class K, class V, class F>
inline Dictionary<K, V, F>::Dictionary(const Dictionary& oth)
{
    v = oth.v;
    comp = oth.comp;
}

template<class K, class V, class F>
inline void Dictionary<K, V, F>::operator=(const Dictionary& oth)
{
    v = oth.v;
    comp = oth.comp;
}

template<class K, class V, class F>
void Dictionary<K, V, F>::Add(const K &cheie, const V &valoare)
{
    bool gasit = false;
    for(auto &p:v)
        if(comp(p.first, cheie))
        {
            p.second = valoare;
            gasit = true;
            break;
        }
    if(!gasit)
        v.push_back({cheie, valoare});
}

template<class K, class V, class F>
void Dictionary<K, V, F>::Delete(const K &cheie)
{
    for(auto it = v.begin(); it != v.end(); it++)
        if(comp(it->first, cheie))
        {
            v.erase(it);
            break;
        }
}

template<class K, class V, class F>
bool Dictionary<K, V, F>::Search(const K &cheie)
{
    for(auto it = v.begin(); it != v.end(); it++)
        if(comp(it->first, cheie))
            return true;
    return false;
}

template<class K, class V, class F>
void Dictionary<K, V, F>::Clear()
{
    v.clear();
}

template<class K, class V, class F>
inline V Dictionary<K, V, F>::operator[](const K &cheie)
{
    for(auto it = v.begin(); it != v.end(); it++)
        if(comp(it->first, cheie))
            return it->second;
    return V();
}


template<class K, class V, class F>
Dictionary<K, V, F>::Dictionary()
{

}

template<class K, class V, class F>
Dictionary<K, V, F>::~Dictionary()
{

}

#endif // DICTIONARY_H
