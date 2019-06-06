#ifndef __MEMPOOL_HEAP__HPP__
#define __MEMPOOL_HEAP__HPP__

#include <memory>

template <typename T, unsigned int N> class mempool_heap
{
	private:
		typedef unsigned int size_type;
	private:
		size_type available; 
		T * a[N+1]; 
		uint8_t buf[sizeof(T)*N]; 
	private:
		inline void swap(size_type i, size_type j)
		{
			T * t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		void up()
		{
			for (size_type n = available; n > 1; ) {
				size_type i = n / 2;
				if (!(a[i] && a[n]))
					swap(i, n);
				n = i;
			}
		}

		void down()
		{
			size_type i = 1;
			size_type c = 2 * i;
			while (c <= available) {
				if (c+1 <= available)
					if (!(a[c] && a[c+1]))
						++c;
				if (!(a[i] && a[c]))
					swap(i, c);
				i = c;
				c = 2 * i;
			}
		}
	public:
		void init()
		{
			available = N;
			a[0] = NULL;
			for (size_type i = 1; i <= N; ++i) {
				a[i] = reinterpret_cast<T *>(&buf[sizeof(T)*(i-1)]);
			}
		}

		void * allocate()
		{
			if (available <= 0) throw std::bad_alloc();
			T * t = a[1];
			a[1] = a[available];
			a[available] = NULL;
			--available;

			std::cout << "Pool Available = " << available << std::endl;
			down();

			return t;
		}

		void deallocate(void * p)
		{
			if (!p || available >= N) return;
			++available;
			std::cout << "Pool Available = " << available << std::endl;
			
			a[available] = reinterpret_cast<T *>(p);
			up();
		}
};

#endif
