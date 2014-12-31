#include "util.h"

/*
 * 	@desc 剔除换行符
 *
 *	\r\n windows 换行
 *	\n 类unix 换行
 *	\r 其他
*/
char *stripLineSep(char *str)
{
	if (str == NULL) return str;

	int len = 0;
	while ((len = strlen(str))) {
		if (str[len - 1] == '\r' || str[len - 1] == '\n') {
			str[len - 1] = '\0';
		} else {
			break;
		}
	}
	return str;
}

