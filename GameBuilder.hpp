
#ifndef GameBuilder_hpp
#define GameBuilder_hpp
#define GameBuilder_AVAILABLE

namespace ame{

template <class Building>
class GameBuilder {
	public:
		virtual Building* build();
};

}

#endif