
#ifndef Pair_hpp
#define Pair_hpp
#define Pair_AVAILABLE

namespace ame{

template<class X1,class X2>
class Pair{
    public:
		X1* x1 = nullptr;
		X2* x2 = nullptr;
		
		Pair(){}
		Pair(bool own){
			owner = own;
		}
		Pair(const Pair<X1,X2>& c_pair){
			owner = c_pair.owner;
			x1 = c_pair.x1;
			x2 = c_pair.x2;
		}
		Pair(X1 c_x1, X2 c_x2){
			x1 = new X1(c_x1);
			x2 = new X2(c_x2);
			owner = true;
		}
		Pair(X1* c_x1, X2* c_x2){
			x1 = c_x1;
			x2 = c_x2;
		}
		Pair(X1* c_x1, X2* c_x2, bool own){
			x1 = c_x1;
			x2 = c_x2;
			owner = own;
		}
		~Pair(){
			if(owner){
				delete x1;
				delete x2;
			}
		}
		virtual void operator=(Pair b){
			x1 = b.x1;
			x2 = b.x2;
		}
		virtual bool operator==(Pair b){
			return x1 == b.x1 && x2 == b.x2;
		}
		virtual bool operator!=(Pair b){
			return x1 != b.x1 && x2 != b.x2;
		}
	protected:
		bool owner = false;
};

}

#endif