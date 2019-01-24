#include "json.h"
using namespace std;
const JSON *json_get_value(const JSON *json, const char *key)
{
	assert(json!=NULL);
	assert(key!=NULL);
	assert(json->type==JSON_OBJ);
	assert(json->TYPE.obj!=NULL);
	for(int i=0;i<json->TYPE.obj->pair.size();++i)
	{
		if(strcmp(json->TYPE.obj->pair[i]->key, key)==0)
			return json->TYPE.obj->pair[i]->val;
	}
	return NULL;
}
const JSON *json_get_index(const JSON *json, U32 idx)
{
	assert(json!=NULL);
	assert(idx>=0);
	assert(json->type==JSON_ARRAY); 
	assert(json->TYPE.arr!=NULL);   
	if(json->TYPE.arr->val.size()>idx)
		return json->TYPE.arr->val[idx];
	return NULL;
}

int json_get_int(const JSON *json, const char *key, int def)
{
	assert(json!=NULL);
	assert(key!=NULL);
	const JSON *p=json_get_value(json,key);
	if(p==NULL||p->type!=JSON_INT)
		return def;
	return p->TYPE.num;
}
BOOL json_get_bool(const JSON *json, const char *key)
{
	assert(json!=NULL);
	assert(key!=NULL);
	const JSON *p=json_get_value(json,key);
	if(p==NULL||p->type!=JSON_BOOL)
		return false;
	return p->TYPE.bol;
}
const char *json_get_str(const JSON *json, const char *key, const char *def)
{
	assert(json!=NULL);
	assert(key!=NULL);
	const JSON *p=json_get_value(json,key);
	if(p==NULL||p->type!=JSON_STR)
		return def;
	return p->TYPE.str;
}

const keyvalue* json_new_keyvalue(const char *key, JSON *val)
{
    assert(key!=NULL);
    assert(val!=NULL);
     keyvalue *p=new keyvalue();
     p->key=strdup(key);
     p->val=val;
     return p;
}
const JSON* json_new_int(int val)
{
	JSON *p=new JSON();
    p->type=JSON_INT;
    p->TYPE.num=val;
	return p;
}
const JSON* json_new_bool(bool val)
{
    JSON *p=new JSON();
    p->type=JSON_BOOL;
    p->TYPE.bol=val;
    return p;
}
const JSON* json_new_str(char* val)
{
    assert(val!=NULL);
    JSON *p=new JSON();
    p->type=JSON_STR;
    p->TYPE.str=strdup(val);
    return p;
}
const JSON* json_new_array()
{
    JSON *p=new JSON();
    p->type=JSON_ARRAY;
    p->TYPE.arr=new Array();
    return p;
}
const JSON* json_new_object()
{
    JSON *p=new JSON();
    p->type=JSON_OBJ;
    p->TYPE.obj=new object();
    return p;
}
BOOL json_set_int(JSON *json, const char *key, int val)
{
    assert(json!=NULL);
    assert(key!=NULL);
    JSON *p=new JSON();
    p=NULL;
    p=(JSON *)json_get_value(json, key);
    if(p==NULL)
        return false;
    p->TYPE.num=val;
    return true;
}

BOOL json_set_bool(JSON *json, const char *key, BOOL val)
{
	assert(json!=NULL);
	assert(key!=NULL);
	JSON *p=(JSON *)json_get_value(json,key);
	if(p==NULL)
		return false;
	p->TYPE.bol=val;
	return true;
}
BOOL json_set_str(JSON *json, const char *key, const char *val)
{
	assert(json!=NULL);
	assert(key!=NULL);
	JSON *p=(JSON *)json_get_value(json,key);
	if(p==NULL)
         return false;
	p->TYPE.str=strdup(val);
	return true;
}
/*
const keyvalue *json_add_keyvalue(const JSON *json)
{
	assert(json!=NULL);
	keyvalue *key_val=NULL;
	key_val->val=NULL;
	char key[MAXN];
	printf("请输入key\n");
	scanf("%s", key);
	U32 len=strlen(key);
	key_val->key=new char[len+1];
	memcpy(key_val->key, key, len);
	key_val->key[len]='\0';
	return key_val;
}
*/
const JSON *json_add_value(const value *val)
{
	JSON *p=NULL;
	p=new JSON();
	const int type = val->type;
	switch(type)
	{
		case JSON_INT:
			{
				p->type=JSON_INT;
				p->TYPE.num=val->TYPE.num;
				break;
			}
		case JSON_BOOL:
			{
				p->type=JSON_BOOL;
				p->TYPE.bol=val->TYPE.bol;
				break;
			}
		case JSON_STR:
			{
				p->type=JSON_STR;
				U32 len=strlen(val->TYPE.str);
				p->TYPE.str=new char[len+1];
				memcpy(p->TYPE.str,val->TYPE.str, len);
				p->TYPE.str[len]='\0';
				break;
			}
		case JSON_ARRAY:
			{
				p->type=JSON_ARRAY;
				p->TYPE.arr=new Array();
				for(int i=0;i<val->TYPE.arr->val.size();++i)
				{
					p->TYPE.arr->val.push_back(val->TYPE.arr->val[i]);
				}
				break;
			}
		case JSON_OBJ:
			{
				p->type=JSON_OBJ;
				p->TYPE.obj=new object();
				for(int i=0;i<val->TYPE.obj->pair.size();++i)
				{
					p->TYPE.obj->pair.push_back(val->TYPE.obj->pair[i]);
				}
				break;
			}
		default:{
				perror("wrong type\n");
				break;
			}
	}
	return p;
}
const JSON *json_create()
{
	JSON *p=NULL;
	p=new JSON();
	p->type=JSON_OBJ;
	p->TYPE.obj=NULL;
	return p;
}
//优先级不高 先不考虑
BOOL json_free(JSON *json)
{
	int type=json->type;
	switch(type)
	{
        case NOTDEFINE: delete(json); break;
		case JSON_INT: delete(json);break;
		case JSON_BOOL: delete(json);break;
		case JSON_STR: delete(json);break;
		case JSON_ARRAY:{
					if(json->TYPE.arr==NULL)
					{
						delete(json);
						break;
					} 
					for(int i=0;i<json->TYPE.arr->val.size();++i)
					{
						json_free(json->TYPE.arr->val[i]);
					}
					delete(json->TYPE.arr);
					delete(json);
                    break;
				}
		case JSON_OBJ:{
				      if(json->TYPE.obj==NULL)
				      {
					      delete(json);
					      break;
				      }
				      for(int i=0;i<json->TYPE.obj->pair.size();++i)
				      {
					      json_free(json->TYPE.obj->pair[i]->val);
				      }
				      delete(json->TYPE.obj);
				      delete(json);
                      break;
			      }
		default:{
				perror("error TYPE\n");
				return false;
			}
	}
	json->TYPE.obj=NULL;
	json=NULL;
	return true;
}
/*
const JSON *make_value(JSON *json)
{
	int type, num, bol;
	char key[MAXN];
	JSON *p=new JSON();
	printf("input type\n");
	scanf("%d", &type);
	switch(type)
	{
		case JSON_INT:
			{p->type=JSON_INT;
				printf("input num\n");
				scanf("%d", &num);
				p->TYPE.num=num;break;
			}case JSON_BOOL:
			{printf("input bool\n");
				p->type=JSON_BOOL;
				scanf("%d", &bol);
				p->TYPE.bol=bol;break;
			}case JSON_STR:
			{printf("input str\n");
				p->type=JSON_STR;
				scanf("%s", key);
				int len=strlen(key);
				p->TYPE.str=new char[len+1];
				memcpy(p->TYPE.str,key, len);
				p->TYPE.str[len]='\0';
				break;
			}case JSON_ARRAY:
			{printf("input array\n");
				p->type=JSON_ARRAY;
				if(p->TYPE.arr==NULL)
					p->TYPE.arr=new Array();
				int n;
				scanf("%d", &n);
				for(int i=0;i<n;++i)
				{
					p->TYPE.arr->val.push_back((JSON *)make_value(json));
				}
				break;
			}
		case JSON_OBJ:
			{
				printf("input OBJ\n");
				p->type=JSON_OBJ;
				if(p->TYPE.obj==NULL)
					p->TYPE.obj=new object();
				keyvalue *key_val=new keyvalue();
				scanf("%s", key); 
				U32 len=strlen(key);
				key_val->key=new char[len+1];
				memcpy(key_val->key, key, len);
				key_val->key[len]='\0'; 
				key_val->val=(JSON *)make_value(json);
				p->TYPE.obj->pair.push_back(key_val);
				break;
			}
		default:{
				perror("wrong type\n");
				break;
			}
	}
	return p;
}
void dfs_print(const JSON* json, int step)
{
	assert(json != NULL);
	int type = json->type;

	if(type == JSON_BOOL)
	{
		printf("%s", json->TYPE.bol ? "true" : "false");
	}
	if(type == JSON_INT)
	{
		printf("%d", json->TYPE.num);
	}
	if(type == JSON_STR)
	{
		printf("\"%s\"", json->TYPE.str);
	}
	if(type == JSON_ARRAY)
	{
		int cnt = json->TYPE.arr->val.size();
		printf("\n");
		for(int i=0;i<step;++i)
			printf(" ");
		printf("[");
		for(int i = 0; i < cnt; i++)
		{
			dfs_print(json->TYPE.arr->val[i], step+1);
			if(i != cnt - 1)printf(",");
		}
		printf("\n");
		for(int i=0;i<step;++i)
			printf(" ");
		printf("]");
	}
	if(type == JSON_OBJ)
	{
		int cnt = json->TYPE.obj->pair.size();
		printf("\n");
		for(int i=0;i<step;++i)
			printf(" ");
		printf("{");
		for(int i = 0; i < cnt; i++)
		{
			printf("\"%s\":", json->TYPE.obj->pair[i]->key);
			dfs_print(json->TYPE.obj->pair[i]->val, step+1);
			if(i != cnt - 1) printf(",");
		}
		printf("\n");
		for(int i=0;i<step;++i)
			printf(" ");
		printf("}");
	}
}
void menu()
{
	printf("\n");
	printf("请输入一个选项\n");
	printf("1.增加一个json的键值对\n");
	printf("2.得到对应key的json字段\n");
	printf("3.得到对应数组下标的json字段\n");
	printf("4.查找key对应的整型value\n");
	printf("5.查找key对应的布尔value\n");
	printf("6.查找key对应的字符串value\n");
	printf("7.查找key对应的数组value\n");
	printf("8.修改key对应的整型value\n");
	printf("9.修改key对应的布尔value\n");
	printf("10.修改key对应的字符串value\n");
	printf("11.打印json\n");
	printf("12.add_value\n");
	printf("13.预留\n");
	printf("14.exit\n");
}

int _main()
{
	int op=0;
	char key[MAXN];
	JSON *json=NULL;
	json=(JSON *)json_create();
	while(1)
	{
		menu();
		scanf("%d", &op);
		switch(op)
		{
			case 1:{ 
				       if(json->TYPE.obj==NULL)
					       json->TYPE.obj=new object();
				       json->TYPE.obj->pair.push_back((keyvalue *)json_add_keyvalue(json));
				       break;
			       }
			case 2: 
			       scanf("%s", key);
			       json_get_value(json, key);break;
			     case 3: json_get_index();break;
				 case 4: json_get_int();break;
				 case 5: json_get_bool();break;
				 case 6: json_get_str();break;
				 case 7: json_get_index();break;
				 case 8: json_set_int();break;
				 case 9: json_set_bool();break;
				 case 10: json_set_str();break;
			case 11: dfs_print(json, 0);break;
			case 12: {
					 JSON *val=new JSON();
					 val=(JSON *)make_value(json);
					 json=(JSON*)json_add_value(json, val);
				 }break;
			case 13: break;
			case 14: return 0;
			default:
				 {
					 perror("wrong input\n");
					 continue;
				 }
		}
	}
	json_free(json);
	return 0;
} 
*/