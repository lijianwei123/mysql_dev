/*
 * syncStruct.cpp
 *
 *  Created on: 2014-12-30
 *  Author: lijianwei
 */
#include "syncStruct.h"

syncStruct::syncStruct(mysql_connect_info_t *mysql_config, mongodb_connect_info_t *mongodb_config)
{
	_mongodb_config = mongodb_config;
	_mysql_config = mysql_config;
}

syncStruct::~syncStruct()
{
}

bool syncStruct::sync()
{
	//连接mysql
	MYSQL conn;
	int retCode = -1;

	retCode = mysql_user_connect(&conn, _mysql_config);
	assert(retCode == 0);

	//必须要指定个db
	assert(_mysql_config->db != NULL);
	retCode = mysql_select_db(&conn, _mysql_config->db);
	assert(retCode == 0);

	//连接mongodb
	mongoc_client_t *client = NULL;
    mongoc_collection_t *collection = NULL;
    bson_t *doc = NULL;
    bson_error_t error;
    char uri_string[200] = {0};
	sprintf(uri_string, "mongodb://%s:%d", _mongodb_config->host, _mongodb_config->port);

	mongoc_init();
	client = mongoc_client_new(uri_string);

	//查询所有表
	result_data_t result_data;
	memset(&result_data, 0, sizeof(result_data_t));
	int i = 0;

	char *show_tables_sql = "show tables";
	retCode = mysql_select(&conn, show_tables_sql, &result_data);
	assert(retCode == 0);
	printf("db %s have %d table\n", _mysql_config->db, result_data.rows);

	mysql_field_value_t **data_ptr = result_data.data;
	mysql_field_value_t *pointer = *data_ptr;

	//输出数据
	vector<string> tableList;
	for (i = 0; i < result_data.rows; i++) {
		tableList.push_back(string(*(data_ptr + i)->next->fieldValue));
	}
	free_result_data(&result_data);

	vector<string>::iterator tableIter;
	char select_sql[200] = {0};
	for(tableIter = tableList.begin(); tableIter != tableList.end(); ++tableIter) {
		cout << "table: " << *tableIter << endl;

		sprintf(select_sql, "select * from `%s` limit 1", *tableIter.c_str());

		result_data_t result_data;
		retCode = mysql_select(&conn, select_sql, &result_data);
		assert(retCode == 0);

		//mongodb 集合
		collection = mongoc_client_get_collection(client, _mysql_config->db, *tableIter.c_str());
		doc = bson_new();

		for (i = 0; i < result_data.rows; i++) {
			pointer = *(data_ptr + i);
			for (j = 0; j < result_data.columns; j++) {
				BSON_APPEND_UTF8(doc, pointer->next->fieldName, pointer->next->fieldValue);
			}
		}

		if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
			cout <<  error.message << endl;
		}

		bson_destroy(doc);
		mongoc_collection_destroy(collection);


		free_result_data(&result_data);
		memset(select_sql, 0, sizeof(select_sql));
	}

	mysql_close(&conn);
	mongoc_client_destroy(client);
}
