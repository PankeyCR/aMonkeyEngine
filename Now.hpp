
#ifndef Now_hpp
#define Now_hpp
#define Now_AVAILABLE

#include "TimeCheck.hpp"

namespace ame{

class Now {
    public:
		static bool is(TimeCheck check,float time,float isNow,float offset){
			if(check == TimeCheck::Equal){
				return time == isNow;
			}
			if(check == TimeCheck::LessThan){
				return time < isNow;
			}
			if(check == TimeCheck::GreaterThan){
				return time > isNow;
			}
			if(check == TimeCheck::GreaterEqualThan){
				return time >= isNow;
			}
			if(check == TimeCheck::LessEqualThan){
				return time <= isNow;
			}
			if(check == TimeCheck::InBetween){
				return isNow<=time+offset && isNow>=time-offset; 
			} 
			return false;
		}
		
		static bool is(TimeCheck check,long time,long isNow,long offset){
			if(check == TimeCheck::Equal){
				return time == isNow;
			}
			if(check == TimeCheck::LessThan){
				return time < isNow;
			}
			if(check == TimeCheck::GreaterThan){
				return time > isNow;
			}
			if(check == TimeCheck::GreaterEqualThan){
				return time >= isNow;
			}
			if(check == TimeCheck::LessEqualThan){
				return time <= isNow;
			}
			if(check == TimeCheck::InBetween){
				return isNow<=time+offset && isNow>=time-offset; 
			} 
			return false;
		}
};

}

#endif