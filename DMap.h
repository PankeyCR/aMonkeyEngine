
#ifndef DMap_h
#define DMap_h

template <class T>
class DMap {
	public:
		virtual void vector(int dimention,int pos);
		virtual void add(T t);
		virtual void remove();
		virtual T get();
		virtual int getDPos(int dimention);
		virtual int size();
    
	private:
};

#endif 