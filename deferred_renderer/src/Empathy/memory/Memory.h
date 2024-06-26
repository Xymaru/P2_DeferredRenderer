#pragma once
#include <cstring>

typedef char sbyte;

namespace EM {
	class Memory {
	private:
		sbyte* m_MemoryBlock;
		size_t m_MemorySize;
		size_t m_PointIndex;
	public:
		Memory() : m_MemoryBlock(nullptr), m_MemorySize(0), m_PointIndex(0) {}

		Memory(size_t size) : m_MemoryBlock(new sbyte[size]), m_MemorySize(size), m_PointIndex(0) {}

		Memory(sbyte* block, size_t size) : m_MemoryBlock(block), m_MemorySize(size), m_PointIndex(0){}

		~Memory() {
			delete[] m_MemoryBlock;
		}

		bool IsEmpty() { return m_MemoryBlock == nullptr; }

		sbyte* getBlock() { return m_MemoryBlock; }

		// De-allocs previous memory and allocs new memory with size
		void Alloc(size_t size){
			delete[] m_MemoryBlock;

			m_MemorySize = size;
			m_PointIndex = 0;

			m_MemoryBlock = new sbyte[size];
		}

		void Write(void* data, size_t size) {
			memcpy(m_MemoryBlock + size, data, size);
		}

		void Read(void* out, size_t size) {
			memcpy(out, m_MemoryBlock + m_PointIndex, size);

			m_PointIndex += size;
		}

		void Seek(size_t index) {
			m_PointIndex = index;
		}

		size_t size() { return m_MemorySize; }
	};
}