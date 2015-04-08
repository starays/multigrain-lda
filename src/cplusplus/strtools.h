/*
 * strtools.h
 *
 *  Created on: 2014年1月17日
 *      Author: zhangrui04
 */

#ifndef STRTOOLS_H_
#define STRTOOLS_H_

#include <string>
#include <vector>

int StrSplit(const std::string & input,
		const char split_border,
		std::vector<std::string> * result);

#endif /* STRTOOLS_H_ */
