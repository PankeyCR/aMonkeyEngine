
#ifndef FastMonkeyMath_cpp
#define FastMonkeyMath_cpp

#include "FastMonkeyMath.h"

    // FastMonkeyMath::FastMonkeyMath(){}

    int FastMonkeyMath::randomSize = 100;
    RealRandom *FastMonkeyMath::realRandom = nullptr;
	
    float FastMonkeyMath::Random(){
		if(realRandom == nullptr){
			realRandom = new RealRandom();
			realRandom->setSeed(524);
		}
		realRandom->setMax(randomSize);
		return realRandom->getRandom();
	}
    void FastMonkeyMath::setRandomSize(int size){
		randomSize = size;
	}

    bool FastMonkeyMath::isPowerOfTwo(int number) {
        return (number > 0) && (number & (number - 1)) == 0;
    }
	
    int FastMonkeyMath::nearestPowerOfTwo(int number) {
        number--;
        number |= number >> 1;
        number |= number >> 2;
        number |= number >> 4;
        number |= number >> 8;
    //    number |= number >> 16;
        number++;
        number += (number == 0) ? 1 : 0;
        return number;
    }

    float FastMonkeyMath::interpolateLinear(float scale, float startValue, float endValue) {
        if (startValue == endValue) {
            return startValue;
        }
        if (scale <= 0.0f) {
            return startValue;
        }
        if (scale >= 1.0f) {
            return endValue;
        }
        return ((1.0f - scale) * startValue) + (scale * endValue);
    }
	
    Vector3f FastMonkeyMath::interpolateLinear(float scale, Vector3f startValue, Vector3f endValue) {
		Vector3f store;
        store.x = interpolateLinear(scale, startValue.x, endValue.x);
        store.y = interpolateLinear(scale, startValue.y, endValue.y);
        store.z = interpolateLinear(scale, startValue.z, endValue.z);
        return store;
    }
	
	
    float FastMonkeyMath::extrapolateLinear(float scale, float startValue, float endValue) {
    //    if (scale <= 0.0f) {
    //        return startValue;
    //    }
        return ((1.0f - scale) * startValue) + (scale * endValue);
    }
	
    Vector3f FastMonkeyMath::extrapolateLinear(float scale, Vector3f startValue, Vector3f endValue) {
        if (scale <= 1.0f) {
            return interpolateLinear(scale, startValue, endValue);
        }
        Vector3f store;
        store.x = extrapolateLinear(scale, startValue.x, endValue.x);
        store.y = extrapolateLinear(scale, startValue.y, endValue.y);
        store.z = extrapolateLinear(scale, startValue.z, endValue.z);
        return store;
    }
	
	
    float FastMonkeyMath::interpolateCatmullRom(float u, float T, float p0, float p1, float p2, float p3) {
        float c1, c2, c3, c4;
        c1 = p1;
        c2 = -1.0f * T * p0 + T * p2;
        c3 = 2 * T * p0 + (T - 3) * p1 + (3 - 2 * T) * p2 + -T * p3;
        c4 = -T * p0 + (2 - T) * p1 + (T - 2) * p2 + T * p3;

        return (float) (((c4 * u + c3) * u + c2) * u + c1);
    }
	
    Vector3f FastMonkeyMath::interpolateCatmullRom(float u, float T, Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3) {
        Vector3f store;
        store.x = interpolateCatmullRom(u, T, p0.x, p1.x, p2.x, p3.x);
        store.y = interpolateCatmullRom(u, T, p0.y, p1.y, p2.y, p3.y);
        store.z = interpolateCatmullRom(u, T, p0.z, p1.z, p2.z, p3.z);
        return store;
    }
	
    float FastMonkeyMath::interpolateBezier(float u, float p0, float p1, float p2, float p3) {
        float oneMinusU = 1.0f - u;
        float oneMinusU2 = oneMinusU * oneMinusU;
        float u2 = u * u;
        return p0 * oneMinusU2 * oneMinusU
                + 3.0f * p1 * u * oneMinusU2
                + 3.0f * p2 * u2 * oneMinusU
                + p3 * u2 * u;
    }
	
    Vector3f FastMonkeyMath::interpolateBezier(float u, Vector3f p0, Vector3f p1, 
									Vector3f p2, Vector3f p3) {
        Vector3f store;
        store.x = interpolateBezier(u, p0.x, p1.x, p2.x, p3.x);
        store.y = interpolateBezier(u, p0.y, p1.y, p2.y, p3.y);
        store.z = interpolateBezier(u, p0.z, p1.z, p2.z, p3.z);
        return store;
    }
	
    float FastMonkeyMath::getCatmullRomP1toP2Length(Vector3f p0, Vector3f p1, 
			Vector3f p2, Vector3f p3, float startRange, float endRange, float curveTension) {

        float epsilon = 0.001f;
        float middleValue = (startRange + endRange) * 0.5f;
        Vector3f start = Vector3f( p1.getX(),p1.getY(),p1.getZ() );
        if (startRange != 0) {
            start = FastMonkeyMath::interpolateCatmullRom(startRange, curveTension, p0, p1, p2, p3);
        }
        Vector3f end = Vector3f( p2.getX(),p2.getY(),p2.getZ() );
        if (endRange != 1) {
            end = FastMonkeyMath::interpolateCatmullRom(endRange, curveTension, p0, p1, p2, p3);
        }
        Vector3f middle = FastMonkeyMath::interpolateCatmullRom(middleValue, curveTension, p0, p1, p2, p3);
        float l = end.subtract(start).length();
        float l1 = middle.subtract(start).length();
        float l2 = end.subtract(middle).length();
        float len = l1 + l2;
        if (l + epsilon < len) {
            l1 = getCatmullRomP1toP2Length(p0, p1, p2, p3, startRange, middleValue, curveTension);
            l2 = getCatmullRomP1toP2Length(p0, p1, p2, p3, middleValue, endRange, curveTension);
        }
        l = l1 + l2;
        return l;
    }
	
    float FastMonkeyMath::getBezierP1toP2Length(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3) {
        float delta = 0.02f, t = 0.0f, result = 0.0f;
        Vector3f v1 = p0;
        Vector3f v2;
        while (t <= 1.0f) {
            v2 = FastMonkeyMath::interpolateBezier(t, p0, p1, p2, p3);
            result += v1.subtractLocal(v2).length();
            v1.set(v2);
            t += delta;
        }
        return result;
    }
	
    float FastMonkeyMath::acos(float fValue) {
        if (-1.0f < fValue) {
            if (fValue < 1.0f) {
                return (float) acos(fValue);
            }

            return 0.0f;
        }

        return PI;
    }
	
    float FastMonkeyMath::asin(float fValue) {
        if (-1.0f < fValue) {
            if (fValue < 1.0f) {
                return (float) asin(fValue);
            }

            return HALF_PI;
        }

        return -HALF_PI;
    }
	
    // float FastMonkeyMath::atan(float fValue) {
        // return (float) atan(fValue);
    // }
	
    // float FastMonkeyMath::atan2(float fY, float fX) {
        // return (float) atan2(fY, fX);
    // }
	
    // float FastMonkeyMath::ceil(float fValue) {
        // return (float) Math.ceil(fValue);
    // }
	
    // float FastMonkeyMath::cos(float v) {
        // return (float) Math.cos(v);
    // }
	
    // float FastMonkeyMath::sin(float v) {
        // return (float) Math.sin(v);
    // }
	
    // float FastMonkeyMath::exp(float fValue) {
        // return (float) Math.exp(fValue);
    // }
	
    // float FastMonkeyMath::abs(float fValue) {
        // if (fValue < 0) {
            // return -fValue;
        // }
        // return fValue;
    // }
	
    // float FastMonkeyMath::floor(float fValue) {
        // return (float) Math.floor(fValue);
    // }
	
    float FastMonkeyMath::invSqrt(float fValue) {
        return (float) (1.0f / sqrt(fValue));
    }

    float FastMonkeyMath::fastInvSqrt(float x) {
        float xhalf = 0.5f * x;
        int i = FastMonkeyMath::floatToIntBits(x); // get bits for floating value
        i = 0x5f375a86 - (i >> 1); // gives initial guess y0
        x = FastMonkeyMath::intBitsToFloat(i); // convert bits back to float
        x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
        return x;
    }
	
	float FastMonkeyMath::intBitsToFloat(int x){
		union {
		   float f;  // assuming 32-bit IEEE 754 single-precision
		   int i;    // assuming 32-bit 2's complement int
		} u;
        
		u.i = x;
		return u.f;
	}
	
	float FastMonkeyMath::floatToIntBits(float x){
		float y;
		memcpy(&y, &x, 4);
		return y;
	}
	
    // float FastMonkeyMath::log(float fValue) {
        // return (float) Math.log(fValue);
    // }
	
    // float FastMonkeyMath::log(float value, float base) {
        // return (float) (log(value) / log(base));
    // }
	
    // float FastMonkeyMath::pow(float fBase, float fExponent) {
        // return (float) pow(fBase, fExponent);
    // }
	
    float FastMonkeyMath::sqr(float fValue) {
        return fValue * fValue;
    }
	
    // float FastMonkeyMath::sqrt(float fValue) {
        // return (float) Math.sqrt(fValue);
    // }
	
    // float FastMonkeyMath::tan(float fValue) {
        // return (float) Math.tan(fValue);
    // }
	
    int FastMonkeyMath::sign(int iValue) {
        if (iValue > 0) {
            return 1;
        }
        if (iValue < 0) {
            return -1;
        }
        return 0;
    }
	
    // float FastMonkeyMath::sign(float fValue) {
        // return Math.signum(fValue);
    // }
	
    int FastMonkeyMath::counterClockwise(Vector2f p0, Vector2f p1, Vector2f p2) {
        float dx1, dx2, dy1, dy2;
        dx1 = p1.x - p0.x;
        dy1 = p1.y - p0.y;
        dx2 = p2.x - p0.x;
        dy2 = p2.y - p0.y;
        if (dx1 * dy2 > dy1 * dx2) {
            return 1;
        }
        if (dx1 * dy2 < dy1 * dx2) {
            return -1;
        }
        if ((dx1 * dx2 < 0) || (dy1 * dy2 < 0)) {
            return -1;
        }
        if ((dx1 * dx1 + dy1 * dy1) < (dx2 * dx2 + dy2 * dy2)) {
            return 1;
        }
        return 0;
    }
	
    int FastMonkeyMath::pointInsideTriangle(Vector2f t0, Vector2f t1, Vector2f t2, Vector2f p) {
        int val1 = counterClockwise(t0, t1, p);
        if (val1 == 0) {
            return 1;
        }
        int val2 = counterClockwise(t1, t2, p);
        if (val2 == 0) {
            return 1;
        }
        if (val2 != val1) {
            return 0;
        }
        int val3 = counterClockwise(t2, t0, p);
        if (val3 == 0) {
            return 1;
        }
        if (val3 != val1) {
            return 0;
        }
        return val3;
    }
	
    Vector3f FastMonkeyMath::computeNormal(Vector3f v1, Vector3f v2, Vector3f v3) {
        Vector3f a1 = v1.subtract(v2);
        Vector3f a2 = v3.subtract(v2);
        return a2.crossLocal(a1).normalizeLocal();
    }
	
    float FastMonkeyMath::determinant(double m00, double m01, double m02,
            double m03, double m10, double m11, double m12, double m13,
            double m20, double m21, double m22, double m23, double m30,
            double m31, double m32, double m33) {

        double det01 = m20 * m31 - m21 * m30;
        double det02 = m20 * m32 - m22 * m30;
        double det03 = m20 * m33 - m23 * m30;
        double det12 = m21 * m32 - m22 * m31;
        double det13 = m21 * m33 - m23 * m31;
        double det23 = m22 * m33 - m23 * m32;
        return (float) (m00 * (m11 * det23 - m12 * det13 + m13 * det12) - m01
                * (m10 * det23 - m12 * det03 + m13 * det02) + m02
                * (m10 * det13 - m11 * det03 + m13 * det01) - m03
                * (m10 * det12 - m11 * det02 + m12 * det01));
    }
	
    // float FastMonkeyMath::nextRandomFloat() {
		// if(realRandom == NULL){
			// realRandom = new RealRandom();
			// realRandom->setSeed(524);
		// }
		// realRandom->setMax(randomSize);
		// return realRandom->getRandom();
    // }
	
    // int FastMonkeyMath::nextRandomInt(int min, int max) {
        // return (int) (nextRandomFloat() * (max - min + 1)) + min;
    // }

    // int FastMonkeyMath::nextRandomInt() {
        // return rand.nextInt();
    // }
	
    Vector3f FastMonkeyMath::sphericalToCartesian(Vector3f sphereCoords) {
		Vector3f store;
        store.y = sphereCoords.x * sin(sphereCoords.z);
        float a = sphereCoords.x * cos(sphereCoords.z);
        store.x = a * cos(sphereCoords.y);
        store.z = a * sin(sphereCoords.y);

        return Vector3f(store.x, store.y, store.z );
    }
	
    Vector3f FastMonkeyMath::cartesianToSpherical(Vector3f cartCoords) {
		Vector3f store;
        float x = cartCoords.x;
        if (x == 0) {
            x = FLT_EPSILON;
        }
        store.x = sqrt((x * x)
                + (cartCoords.y * cartCoords.y)
                + (cartCoords.z * cartCoords.z));
        store.y = atan(cartCoords.z / x);
        if (x < 0) {
            store.y += PI;
        }
        store.z = asin(cartCoords.y / store.x);
        return Vector3f(store.x, store.y, store.z );
    }
	
    Vector3f FastMonkeyMath::sphericalToCartesianZ(Vector3f sphereCoords) {
		Vector3f store;
        store.z = sphereCoords.x * sin(sphereCoords.z);
        float a = sphereCoords.x * cos(sphereCoords.z);
        store.x = a * cos(sphereCoords.y);
        store.y = a * sin(sphereCoords.y);

        return Vector3f(store.x, store.y, store.z );
    }
	
    Vector3f FastMonkeyMath::cartesianZToSpherical(Vector3f cartCoords) {
		Vector3f store;
        float x = cartCoords.x;
        if (x == 0) {
            x = FLT_EPSILON;
        }
        store.x = sqrt((x * x)
                + (cartCoords.y * cartCoords.y)
                + (cartCoords.z * cartCoords.z));
        store.z = atan(cartCoords.z / x);
        if (x < 0) {
            store.z += PI;
        }
        store.y = asin(cartCoords.y / store.x);
        return Vector3f(store.x, store.y, store.z );
    }
	
    float FastMonkeyMath::normalize(float val, float min, float max){
        float range = max - min;
        while (val > max) {
            val -= range;
        }
        while (val < min) {
            val += range;
        }
        return val;
    }
	
    float FastMonkeyMath::copysign(float x, float y) {
        if (y >= 0 && x <= -0) {
            return -x;
        } else if (y < 0 && x >= 0) {
            return -x;
        } else {
            return x;
        }
    }
	
    float FastMonkeyMath::clamp(float input, float min, float max) {
        return (input < min) ? min : (input > max) ? max : input;
    }
	
    float FastMonkeyMath::saturate(float input) {
        return clamp(input, 0.0f, 1.0f);
    }
	
    bool FastMonkeyMath::approximateEquals(float a, float b) {
        if (a == b) {
            return true;
        } else {
            return (abs(a - b) / max(abs(a), abs(b))) <= 0.00001f;
        }
    }
	
    float FastMonkeyMath::convertHalfToFloat(short half) {
        switch ((int) half) {
            case 0x0000:
                return 0.0f;
            case 0x8000:
                return -0.0f;
            // TODO: Support for NaN?
            default:
                return (((half & 0x7c00) + 0x1C000) << 13)
                        | ((half & 0x03FF) << 13);
        }
    }
    short FastMonkeyMath::convertFloatToHalf(float flt) {
        if (flt == 0.0f) {
            return (short) 0x0000;
        } else if (flt == -0.0f) {
            return (short) 0x8000;
        } else if (flt > 65504.0f) {
            // max value supported by half float
            return 0x7bff;
        } else if (flt < -65504.0f) {
            return (short) (0x7bff | 0x8000);
        } else if (flt > 0.0f && flt < 3.054738E-5f) {
            return 0x0001;
        } else if (flt < 0.0f && flt > -3.054738E-5f) {
            return (short) 0x8001;
        }
        int32_t f = (float)flt;
        return (short) (((f >> 16) & 0x8000)
                | ((((f & 0x7f800000) - 0x38000000) >> 13) & 0x7c00)
                | ((f >> 13) & 0x03ff));
    }

#endif 
