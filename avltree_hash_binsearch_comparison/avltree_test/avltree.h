#ifndef AVL_HEAD_H_2024_04_11
#define AVL_HEAD_H_2024_04_11

#include "../memory_manager/mm.h"

namespace lab618 {

template<class T, int(*Compare)(const T *pElement, const T *pElement2)>
class CAVLTree {
 private:
    struct leaf {
        T *pData = nullptr;
        leaf *pLeft = nullptr;
        leaf *pRight = nullptr;
        int balanceFactor = 0;
    };

    int getBalance(leaf *p) {
        return p == nullptr ? 0 : p->balanceFactor;
    }

    int getBalanceDifference(leaf *p) {
        return getBalance(p->pRight) - getBalance(p->pLeft);
    }
    void changeBalance(leaf *p) {
        p->balanceFactor = std::max(getBalance(p->pRight), getBalance(p->pLeft)) + 1;
    }

    leaf *pRightRotate(leaf *p) {
        leaf *q = p->pLeft;
        p->pLeft = q->pRight;
        q->pRight = p;
        changeBalance(p);
        changeBalance(q);
        return q;
    }

    leaf *pLeftRotate(leaf *p) {
        leaf *q = p->pRight;
        p->pRight = q->pLeft;
        q->pLeft = p;
        changeBalance(p);
        changeBalance(q);
        return q;
    }

    leaf *balance(leaf *p) {
        changeBalance(p);
        if (getBalanceDifference(p) == 2) {
            if (getBalanceDifference(p->pRight) < 0) {
                p->pRight = pRightRotate(p->pRight);
            }
            return pLeftRotate(p);
        }
        if (getBalanceDifference(p) == -2) {
            if (getBalanceDifference(p->pLeft) > 0) {
                p->pLeft = pLeftRotate(p->pLeft);
            }
            return pRightRotate(p);
        }
        return p;
    }

    leaf *addLeaf(leaf *p, T *pData) {
        if (p == nullptr) {
            leaf *new_leaf = m_Memory.newObject();
            new_leaf->pData = pData;
            return new_leaf;
        }
        if (Compare(pData, p->pData) < 0) {
            p->pLeft = addLeaf(p->pLeft, pData);
        } else {
            p->pRight = addLeaf(p->pRight, pData);
        }
        return balance(p);
    }

    leaf *findLeaf(leaf *p, const T *pData) {
        if (pData != nullptr && p != nullptr) {
            if (Compare(pData, p->pData) < 0) {
                return findLeaf(p->pLeft, pData);
            }
            if (Compare(pData, p->pData) == 0) {
                return p;
            }
            return findLeaf(p->pRight, pData);
        }
        return nullptr;
    }

    leaf *eraseLeaf(leaf *p, const T *pData) {
        if (p != nullptr) {

            if (Compare(pData, p->pData) < 0) {
                p->pLeft = eraseLeaf(p->pLeft, pData);
            }

            if (Compare(pData, p->pData) > 0) {
                p->pRight = eraseLeaf(p->pRight, pData);
            }

            if (Compare(pData, p->pData) == 0) {
                if (p->pLeft == nullptr && p->pRight == nullptr) {
                    m_Memory.deleteObject(p);
                    p = nullptr;
                    return nullptr;
                } else if (p->pLeft == nullptr) {
                    leaf *ret = p->pRight;
                    m_Memory.deleteObject(p);
                    p = nullptr;
                    return ret;
                } else if (p->pRight == nullptr) {
                    leaf *ret = p->pLeft;
                    m_Memory.deleteObject(p);
                    p = nullptr;
                    return ret;
                } else {
                    leaf *curr = p->pRight;
                    while (curr->pLeft != nullptr) {
                        curr = curr->pLeft;
                    }
                    p->pData = curr->pData;
                    p->pRight = eraseLeaf(p->pRight, curr->pData);
                }
            }

            return balance(p);
        }
        return nullptr;
    }

 public:
    class CException {
     public:
        CException() {
        }
    };

 public:
    CAVLTree(int defaultBlockSize) : m_Memory(defaultBlockSize, true) {
    }

    virtual ~CAVLTree() {
        clear();
    }

    bool add(T *pElement) {
        leaf *elem_leaf = findLeaf(m_pRoot, pElement);
        if (elem_leaf != nullptr) {
            return false;
        } else {
            m_pRoot = addLeaf(m_pRoot, pElement);
            return true;
        }
    }

    bool update(T *pElement) {
        leaf *elem_leaf = findLeaf(m_pRoot, pElement);
        if (elem_leaf == nullptr) {
            add(pElement);
            return false;
        } else {
            elem_leaf->pData = pElement;
            return true;
        }
    }

    T *find(const T &pElement) {
        leaf *elem_leaf = findLeaf(m_pRoot, &pElement);
        return elem_leaf == nullptr ? nullptr : elem_leaf->pData;
    }

    bool remove(const T &element) {
        leaf *elem_leaf = findLeaf(m_pRoot, &element);
        if (elem_leaf == nullptr) {
            return false;
        } else {
            m_pRoot = eraseLeaf(m_pRoot, &element);
            return true;
        }
    }

    void clear() {
        m_Memory.clear();
        m_pRoot = nullptr;
    }

 private:
    leaf *m_pRoot = nullptr;
    CMemoryManager<leaf> m_Memory;
};

}; // namespace templates

#endif // #define AVL_HEAD_H_2024_04_11