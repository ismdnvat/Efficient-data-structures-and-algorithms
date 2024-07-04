#ifndef TEMPLATES_LIST_2024_02_12
#define TEMPLATES_LIST_2024_02_12

namespace lab618 {
template<class T>
class CSingleLinkedList {
 private:
    struct leaf
    {
        // Данные
        T data;
        // Указатель на следующий лист списка
        leaf *pNext;
        leaf(T &_data, leaf *_pNext) : data(_data), pNext(_pNext) {}
    };
 public:
    class CIterator
    {
     public:
        CIterator() : m_pCurrent(nullptr), m_pBegin(nullptr) {}

        CIterator(leaf *p) : m_pCurrent(p), m_pBegin(nullptr) {}

        CIterator(const CIterator &src) : m_pCurrent(src.m_pCurrent), m_pBegin(src.m_pBegin) {}

        ~CIterator() = default;

        CIterator& operator=(const CIterator& src) = default;

        bool operator!=(const CIterator& it) const
        {
            return !((m_pCurrent == it.m_pCurrent) && (m_pBegin == it.m_pBegin));
        }

        void operator++()
        {
            if (m_pCurrent)
            {
                m_pCurrent = m_pCurrent->pNext;
            } else if (m_pBegin)
            {
                m_pCurrent = m_pBegin;
                m_pBegin = nullptr;
            }
        }

        T &getData()
        {
            return m_pCurrent->data;
        }

        T &operator*()
        {
            return m_pCurrent->data;
        }

        leaf* getLeaf()
        {
            return m_pCurrent;
        }

        void setLeaf(leaf *p)
        {
            m_pCurrent = p;
        }

        void setLeafPreBegin(leaf *p)
        {
            m_pBegin = p;
            m_pCurrent = nullptr;
        }

        bool isValid()
        {
            return ((m_pCurrent != nullptr) || (m_pBegin != nullptr));
        }

     private:
        //храним голову списка, если мы находимся перед началом
        leaf* m_pBegin;
        // храним текущее положение
        leaf* m_pCurrent;
    };

 public:

    CSingleLinkedList() : m_pBegin(nullptr), m_pEnd(nullptr) {};

    virtual ~CSingleLinkedList()
    {
        clear();
    }

    void pushBack(T &data)
    {
        leaf *new_leaf = new leaf(data, nullptr);
        if (!m_pBegin)
        {
            m_pBegin = new_leaf;
        } else
        {
            m_pEnd->pNext = new_leaf;
        }
        m_pEnd = new_leaf;
    }

    void pushFront(T &data)
    {
        leaf *new_leaf = new leaf(data, nullptr);
        if (m_pBegin == nullptr)
        {
            m_pEnd = new_leaf;
        } else
        {
            new_leaf->pNext = m_pBegin;
        }
        m_pBegin = new_leaf;
    }

    T popFront() {
        T data = m_pBegin->data;
        leaf *tmp = m_pBegin;
        m_pBegin = m_pBegin->pNext;
        delete tmp;
        return data;
    }

    void erase(CIterator &it) {
        leaf *tmp = it.getLeaf();
        if (m_pBegin == m_pEnd) {
            delete tmp;
            m_pBegin = nullptr;
            it.setLeafPreBegin(nullptr);
        } else if (tmp == m_pBegin) {
            m_pBegin = tmp->pNext;
            it.setLeafPreBegin(m_pBegin);
            delete tmp;
        } else {
            leaf *prev = nullptr;
            CIterator tmpIt = CIterator(m_pBegin);
            while (tmpIt.getLeaf() != tmp) {
                prev = tmpIt.getLeaf();
                ++tmpIt;
            }
            prev->pNext = tmp->pNext;
            it.setLeaf(prev);
            if (tmp == m_pEnd) {
                m_pEnd = prev;
            }
            delete tmp;
        }
    }


    int getSize()
    {
        int size = 0;
        leaf *curr = m_pBegin;
        while (curr)
        {
            ++size;
            curr = curr->pNext;
        }
        return size;
    }

    void clear()
    {
        leaf *curr = m_pBegin;
        while (curr)
        {
            leaf *tmp = curr;
            curr = curr->pNext;
            delete tmp;
        }
        m_pBegin = m_pEnd = nullptr;
    }

    CIterator begin()
    {
        return CIterator(m_pBegin);
    }
 private:
    //храним голову и хвост списка
    leaf *m_pBegin, *m_pEnd;
};


template<class T>
class CDualLinkedList
{
 private:
    struct leaf
    {
        // Данные
        T data;
        // Указатель на предыдущий / следующий лист списка
        leaf* pNext, * pPrev;
        leaf(T& _data, leaf* _pPrev, leaf* _pNext) : data(_data), pNext(_pNext), pPrev(_pPrev)
        {
        }
    };
 public:
    class CIterator
    {
     public:
        CIterator() : m_pBegin(nullptr), m_pCurrent(nullptr), m_pEnd(nullptr) 
        {
        }

        CIterator(leaf* p) : m_pCurrent(p)
        {
        }

        CIterator(const CIterator& src) : m_pCurrent(src.m_pCurrent), m_pBegin(src.m_pBegin), m_pEnd(src.m_pEnd)
        {
        }

        ~CIterator() = default;

        CIterator& operator= (const CIterator& src) = default;

        bool operator!=(const CIterator& it) const
        {
            return !((m_pCurrent == it.m_pCurrent) && (m_pBegin == it.m_pBegin) && (m_pEnd == it.m_pEnd));
        }
        
        void operator++()
        {
            if (m_pCurrent && m_pCurrent->pNext)
            {
                m_pCurrent = m_pCurrent->pNext;
            } else if (m_pCurrent && !m_pCurrent->pNext)
            {
                m_pCurrent = nullptr;
            } else if (m_pBegin) {
                m_pCurrent = m_pBegin;
            } else {
                m_pCurrent = nullptr;
            }
            m_pEnd = nullptr;
            m_pBegin = nullptr;
        }

        void operator--()
        {
            if (m_pCurrent) {
                m_pCurrent = m_pCurrent->pPrev;
            } else if (m_pEnd) {
                m_pCurrent = m_pEnd;
                m_pBegin = nullptr;
                m_pEnd = nullptr;
            } else {
                m_pCurrent = nullptr;
                m_pBegin = nullptr;
                m_pEnd = nullptr;
            }
        }

        T& getData()
        {
            return m_pCurrent->data;
        }

        T& operator* ()
        {
            return m_pCurrent->data;
        }

        leaf* getLeaf()
        {
            return m_pCurrent;
        }

        // применяется в erase и eraseAndNext
        void setLeaf(leaf* p)
        {
            m_pCurrent = p;
        }

        // применяется в erase и eraseAndNext
        void setLeafPreBegin(leaf* p)
        {
            m_pBegin = p;
            m_pCurrent = nullptr;
            m_pEnd = nullptr;
        }

        // применяется в erase и eraseAndNext
        void setLeafPostEnd(leaf* p)
        {
            m_pEnd = p;
            m_pCurrent = nullptr;
            m_pBegin = nullptr;
        }

        bool isValid() {
            return ((m_pCurrent != nullptr) || (m_pBegin != nullptr));
            return false;
        }

     private:
        //храним голову списка, если мы находимся перед началом
        leaf* m_pBegin = nullptr;
        // храним текущее положение
        leaf* m_pCurrent = nullptr;
        //храним конец списка, если мы находимся после конца
        leaf* m_pEnd = nullptr;
    };

 public:

    CDualLinkedList() : m_pBegin(nullptr), m_pEnd(nullptr)
    {
        
    };

    virtual ~CDualLinkedList()
    {
        clear();
    };

    void pushBack(T& data)
    {
        leaf *new_leaf = new leaf(data, nullptr, nullptr);
        if (!m_pBegin)
        {
            m_pBegin = new_leaf;
        } else
        {
            m_pEnd->pNext = new_leaf;
            new_leaf->pPrev = m_pEnd;
        }
        m_pEnd = new_leaf;
    }

    T popBack()
    {
        leaf* old_end = m_pEnd;
        T data = m_pEnd->data;
        if (m_pEnd == m_pBegin)
        {
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        } else
        {
            m_pEnd = old_end->pPrev;
            m_pEnd->pNext = nullptr;
        }
        delete old_end;
        old_end = nullptr;
        return data;
    }
    
    void pushFront(T& data)
    {
        leaf *new_leaf = new leaf(data, nullptr, nullptr);
        if (!m_pBegin)
        {
            m_pEnd = new_leaf;
        } else
        {
            m_pBegin->pPrev = new_leaf;
            new_leaf->pNext = m_pBegin;
        }
        m_pBegin = new_leaf;
    }

    T popFront()
    {
        leaf* old_begin = m_pBegin;
        T data = m_pBegin->data;
        if (m_pEnd == m_pBegin)
        {
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        } else
        {
            m_pBegin = old_begin->pNext;
            m_pEnd->pPrev = nullptr;
        }
        delete old_begin;
        old_begin = nullptr;
        return data;
    }

    // изменяет состояние итератора. выставляет предыдущую позицию.
    void erase(CIterator& it)
    {
        leaf *tmp = it.getLeaf();
        if (m_pBegin == m_pEnd) {
            m_pBegin = nullptr;
            it.setLeafPreBegin(nullptr);
        } else if (tmp == m_pBegin)
        {
            m_pBegin = tmp->pNext;
            m_pBegin->pPrev = nullptr;
            it.setLeafPreBegin(m_pBegin);
        } else if (tmp == m_pEnd)
        {
            tmp->pPrev->pNext = tmp->pNext;
            m_pEnd = tmp->pPrev;
            it.setLeaf(tmp->pPrev);
        } else {
            leaf *prev = tmp->pPrev;
            tmp->pPrev->pNext = tmp->pNext;
            tmp->pNext->pPrev = tmp->pPrev;
            it.setLeaf(tmp->pPrev);
        }
        delete tmp;
        tmp = nullptr;
    }

    // изменяет состояние итератора. выставляет следующую позицию.
    void eraseAndNext(CIterator& it)
    {
        leaf *tmp = it.getLeaf();
        if (m_pBegin == m_pEnd) {
            m_pBegin = nullptr;
            m_pEnd = nullptr;
            it.setLeafPostEnd(nullptr);
        } else if (tmp == m_pBegin)
        {
            tmp->pNext->pPrev = tmp->pPrev;
            m_pBegin = tmp->pNext;
            it.setLeaf(tmp->pNext);
        } else if (tmp == m_pEnd)
        {
            m_pEnd = tmp->pPrev;
            m_pEnd->pNext = nullptr;
            it.setLeafPostEnd(m_pEnd);
        } else
        {
            leaf *next = tmp->pNext;
            tmp->pNext->pPrev = tmp->pPrev;
            tmp->pPrev->pNext = tmp->pNext;
            it.setLeaf(tmp->pNext);
        }
        delete tmp;
        tmp = nullptr;
    }

    int getSize()
    {
        int size = 0;
        leaf *curr = m_pBegin;
        while (curr)
        {
            ++size;
            curr = curr->pNext;
        }
        return size;
    }

    void clear()
    {
        leaf *curr = m_pBegin;
        while (curr)
        {
            leaf *tmp = curr;
            curr = curr->pNext;
            delete tmp;
        }
        m_pBegin = nullptr;
        m_pEnd = nullptr;
    }

    CIterator begin()
    {
        return CIterator(m_pBegin);
    }

    CIterator end()
    {
        return CIterator(m_pEnd);
    }

 private:
    //храним голову и хвост списка
    leaf* m_pBegin, * m_pEnd;
};
};
#endif //#ifndef TEMPLATES_LIST_2024_02_12
