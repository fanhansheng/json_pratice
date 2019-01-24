#ifndef _JSON_H
#define _JSON_H
#include <cstdio>
#include <cstring>
#include <vector>
typedef unsigned int U32;
typedef bool BOOL;
const int MAXN = 1005;
typedef struct value JSON;
typedef struct Array Array;
typedef struct object object;
typedef enum json_e{
   NOTDEFINE=0, JSON_INT,JSON_BOOL,JSON_STR,JSON_ARRAY, JSON_OBJ, JSON_TYPE_MAX
}json_e;
struct keyvalue{
     char *key;
     value *val;
};
struct Array
{
	std::vector<value *> val;
};

struct object{
    std::vector<keyvalue *> pair;
};

struct value{
    int type;                          
	union{
	int num;  
	BOOL bol;	                    
	char *str;
	Array *arr;
	object *obj;
	}TYPE;                                   
};

const JSON *json_get_value(const JSON *json, const char *key);
const JSON *json_get_index(const JSON *json, U32 idx);

int json_get_int(const JSON *json, const char *key, int def);
BOOL json_get_bool(const JSON *json, const char *key);
/**
 * 获取JSON对象中键名为key的值，如果获取不到，则返回缺省值def
 * 如果json不是对象类型，则返回def
 * 如果对应的值为其它类型，先将其转换为字符串
 * 如: 
 *  json: {"key": "str"}
 *  json_get_str(json, "key", NULL) = "str"
 *  json_get_str(json, "noexist", NULL) = NULL
 *  json_get_str(json, "noexist", "") = ""
 */
const char *json_get_str(const JSON *json, const char *key, const char *def);

BOOL json_set_int(JSON *json, const char *key, int val);
BOOL json_set_bool(JSON *json, const char *key, BOOL val);
BOOL json_set_str(JSON *json, const char *key, const char *val);
//增加键值对
const keyvalue *json_add_keyvalue(JSON *json, const char *key, const keyvalue &key_val);
const JSON *json_add_value(const value *val);
BOOL json_add_array(JSON *json, const value &val);
const JSON *json_create();
BOOL json_free(JSON *json);
const JSON *make_value(const JSON *json);
void dfs_print(const JSON *json, int step);
const keyvalue* json_new_keyvalue(const char *key,JSON  *val);
const JSON* json_new_int(int val);
const JSON* json_new_bool(bool val);
const JSON* json_new_str(char* val);
const JSON* json_new_array();
const JSON* json_new_object();
#endif