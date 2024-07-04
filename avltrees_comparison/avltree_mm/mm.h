#ifndef MEMORY_MANAGER_HEAD_H_2024_03_07
#define MEMORY_MANAGER_HEAD_H_2024_03_07

#include <cstring>
#include <map>

namespace lab618 {

template<class T>
class CMemoryManager {
 private:
    struct block {
        T* pdata;
        block* pnext;
        int32_t firstFreeIndex;
        int32_t usedCount;

        block(T* _pdata, block* _pnext, int32_t _firstFreeIndex, int32_t _usedCount)
            : pdata(_pdata),
              pnext(_pnext),
              firstFreeIndex(_firstFreeIndex),
              usedCount(_usedCount) {}
    };

 public:
    class CException {
     public:
        CException() {}
    };

 public:
    CMemoryManager(int32_t _default_block_size, bool isDeleteElementsOnDestruct = false)
        : m_blkSize(_default_block_size), m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct),
          m_pBlocks(nullptr), m_pCurrentBlk(nullptr) {}

    virtual ~CMemoryManager() {
        clear();
    }

    T* newObject() {
        if (m_pBlocks == nullptr || m_pCurrentBlk == nullptr || m_pCurrentBlk->usedCount == m_blkSize) {
            block* new_block = newBlock();
            if (m_pBlocks == nullptr) {
                m_pBlocks = new_block; // Если нет блоков, устанавливаем новый блок как начальный
            }
            if (m_pCurrentBlk != nullptr) {
                m_pCurrentBlk->pnext = new_block;
            }
            m_pCurrentBlk = new_block;
            m_blockMap[new_block->pdata] = new_block;
        }

        int next_free = *(reinterpret_cast<int*>(m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex));
        T* new_object = new((m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex)) T();
        ++m_pCurrentBlk->usedCount;
        m_pCurrentBlk->firstFreeIndex = next_free;
        return new_object;
    }

    bool deleteObject(T* p) {
        auto it = m_blockMap.upper_bound(p);
        if (it == m_blockMap.begin()) {
            return false;
        }
        --it;
        block* target_block = it->second;

        if (p < target_block->pdata || p > (target_block->pdata + m_blkSize)) {
            return false;
        }

        int32_t p_index = p - target_block->pdata;
        if (m_isDeleteElementsOnDestruct) {
            p->~T();
        }
        *(reinterpret_cast<int32_t*>(p)) = target_block->firstFreeIndex;
        target_block->firstFreeIndex = p_index;
        --target_block->usedCount;

        return true;
    }

    void clear() {
        for (auto& pair : m_blockMap) {
            block* target_block = pair.second;
            if (m_isDeleteElementsOnDestruct) {
                for (int32_t i = 0; i < target_block->usedCount; ++i) {
                    T* p = target_block->pdata + i;
                    p->~T();
                }
            }
            delete[] reinterpret_cast<char*>(pair.first);
            delete pair.second;
        }
        m_blockMap.clear();
        m_pBlocks = nullptr;
        m_pCurrentBlk = nullptr;
    }

 private:
    block* newBlock() {
        T* data = reinterpret_cast<T*>(new char[sizeof(T) * m_blkSize]);
        for (int32_t i = 0; i < m_blkSize - 1; ++i) {
            *(reinterpret_cast<int32_t*>(data + i)) = i + 1;
        }
        *(reinterpret_cast<int32_t*>(data + m_blkSize - 1)) = -1;
        block* new_block = new block(data, nullptr, 0, 0);
        return new_block;
    }

    int32_t m_blkSize;
    block* m_pBlocks;
    block* m_pCurrentBlk;
    bool m_isDeleteElementsOnDestruct;
    std::map<T*, block*> m_blockMap;
};

}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2024_03_07
