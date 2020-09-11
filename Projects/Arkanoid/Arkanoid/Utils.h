#pragma once
class Utils {
public:
	template<class T>
	static void normalizeArray(T a[]) {
		T sum{ 0.0f };
		for (int i = 0; i < 9; i++) {
			sum += a[i];
		}
		for (int i = 0; i < 9; i++) {
			a[i] /= sum;
		}
	}
};