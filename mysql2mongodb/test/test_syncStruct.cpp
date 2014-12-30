/*
 * test_syncStruct.cpp
 *
 *  Created on: 2014-12-30
 *  Author: lijianwei
 */

#include "syncSturct.h"

int main(int argc, char **argv)
{
	CConfigFileReader  serverConf("../main.conf");

	mongodb_connect_info_t mongodb_config;
	mongodb_config.host = stripLineSep(serverConf.GetConfigName("mongodb.host"));
	mongodb_config.port = (unsigned int)atoi(serverConf.GetConfigName("mongodb.port"));

	mysql_connect_info_t mysql_config;
	mysql_connection_info_init(&mysql_config);
	mysql_config.host = stripLineSep(serverConf.GetConfigName("mysql.host"));
	if (serverConf.GetConfigName("mysql.port")) {
		mysql_config.port =  (unsigned int)atoi(serverConf.GetConfigName("mysql.port"));
	}
	mysql_config.db = stripLineSep(serverConf.GetConfigName("mysql.db"));
	mysql_config.user = stripLineSep(serverConf.GetConfigName("mysql.user"));
	mysql_config.pwd = stripLineSep(serverConf.GetConfigName("mysql.pwd"));


	syncStruct sync(&mysql_config, &mongodb_config);
	sync.sync();
}


