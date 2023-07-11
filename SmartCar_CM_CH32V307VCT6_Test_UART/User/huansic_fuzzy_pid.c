/*
 * huansic_fuzzy_pid.c
 *
 *  Created on: Jul 11, 2023
 *      Author: ZonghuanWu
 */

#include <huansic_fuzzy_pid.h>

#define fzand(x, y) 	(x > y ? x : y)
#define fzor(x, y) 		(x > y ? y : x)
#define fznot(x) 		(1 - x)

inline float map_Error_S(float input) {	// in m/s
	input = input < 0 ? -input : input;
	if (input < 0.01)
		return 1;
	if (input < 0.02)
		return 1 - ((input - 0.01) / 0.01);
	return 0;
}

inline float map_Error_M(float input) {	// in m/s
	input = input < 0 ? -input : input;
	if (input < 0.01)
		return 0;
	if (input < 0.02)
		return (input - 0.01) / 0.01;
	if (input < 0.04)
		return 1;
	if (input < 0.06)
		return 1 - ((input - 0.04) / 0.02);
	return 0;
}

inline float map_Error_L(float input) {	// in m/s
	input = input < 0 ? -input : input;
	if (input < 0.04)
		return 0;
	if (input < 0.1)
		return (input - 0.04) / 0.06;
	return 1;
}

inline float map_dError_S(float input) {	// in m/s2
	input = input < 0 ? -input : input;
	if (input < 0.003)
		return 1;
	if (input < 0.005)
		return 1 - ((input - 0.003) / 0.002);
	return 0;
}

inline float map_dError_M(float input) {	// in m/s2
	input = input < 0 ? -input : input;
	if (input < 0.003)
		return 0;
	if (input < 0.005)
		return (input - 0.003) / 0.002;
	if (input < 0.008)
		return 1;
	if (input < 0.01)
		return 1 - ((input - 0.008) / 0.002);
	return 0;
}

inline float map_dError_L(float input) {	// in m/s2
	input = input < 0 ? -input : input;
	if (input < 0.008)
		return 0;
	if (input < 0.01)
		return (input - 0.008) / 0.002;
	return 1;
}

inline float map_sError_S(float input) {	// in m
	input = input < 0 ? -input : input;
	if (input < 0.01)
		return 1;
	if (input < 0.02)
		return 1 - ((input - 0.01) / 0.01);
	return 0;
}

inline float map_sError_M(float input) {	// in m
	input = input < 0 ? -input : input;
	if (input < 0.01)
		return 0;
	if (input < 0.02)
		return (input - 0.01) / 0.01;
	if (input < 0.05)
		return 1;
	if (input < 0.08)
		return 1 - ((input - 0.05) / 0.03);
	return 0;
}

inline float map_sError_L(float input) {	// in m
	input = input < 0 ? -input : input;
	if (input < 0.08)
		return 0;
	if (input < 0.1)
		return (input - 0.08) / 0.02;
	return 1;
}

void huansic_fuzzy_Error2Fuzzy(FuzzyVariable3 *var, float error) {
	var->SMALL = map_Error_S(error);
	var->MEDIUM = map_Error_M(error);
	var->LARGE = map_Error_L(error);
}

void huansic_fuzzy_dError2Fuzzy(FuzzyVariable3 *var, float derror) {
	var->SMALL = map_dError_S(derror);
	var->MEDIUM = map_dError_M(derror);
	var->LARGE = map_dError_L(derror);
}

void huansic_fuzzy_sError2Fuzzy(FuzzyVariable3 *var, float serror) {
	var->SMALL = map_sError_S(serror);
	var->MEDIUM = map_sError_M(serror);
	var->LARGE = map_sError_L(serror);
}
