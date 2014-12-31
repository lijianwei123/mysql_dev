/*
 * syncSturct.h
 *
 *  Created on: 2014-12-30
 *  Author: lijianwei
 */

#ifndef SYNCSTRUCT_H_
#define SYNCSTRUCT_H_


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mysql.h"
#include <mongoc.h>
#include "util.h"
#include "ConfigFileReader.h"

using namespace std;

typedef struct {
	char *host;
	uint16_t port;
} mongodb_connect_info_t;

class syncStruct
{
public:
	syncStruct(mysql_connect_info_t *mysql_config, mongodb_connect_info_t *mongodb_config);
	virtual ~syncStruct();

	bool sync();

private:
	mysql_connect_info_t *_mysql_config;
	mongodb_connect_info_t *_mongodb_config;
};

#endif /* SYNCSTRUCT_H_ */
