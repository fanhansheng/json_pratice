#include "json.h"
#include "gtest/gtest.h"
using namespace std;
TEST(test, json_create)
{
    JSON *json=NULL;
    json=(JSON *)json_create();
    ASSERT_TRUE(json!=NULL) << "json NULL";
    ASSERT_TRUE(json->TYPE.obj==NULL) << "json->TYPE.obj NULL";
    json_free(json);
}
TEST(test, json_new_int)
{
    JSON *json=NULL;
    json=(JSON *)json_new_int(-1);
    ASSERT_TRUE(json->type==JSON_INT);
    ASSERT_TRUE(json->TYPE.num==-1);
    json_free(json);
}
TEST(test, json_new_bol)
{
    JSON *json=NULL;
    json=(JSON *)json_new_bool( -1);
    ASSERT_TRUE(json->type==JSON_BOOL);
    ASSERT_TRUE(json->TYPE.num==true);
    json_free(json);
}
TEST(test, json_new_str)
{
    JSON *json=NULL;
    char key[10]="abc";
    json=(JSON *)json_new_str(key);
    ASSERT_TRUE(json->type==JSON_STR);
    ASSERT_TRUE(strcmp(json->TYPE.str, key)==0);
    json_free(json);
}
TEST(test, json_new_array)
{
    JSON *json=NULL;
    json=(JSON *)json_new_array();
    ASSERT_TRUE(json->type==JSON_ARRAY);
    ASSERT_TRUE(json->TYPE.arr!=NULL);
    json_free(json);
}
TEST(test, json_new_obj)
{
    JSON *json=NULL;
    json=(JSON *)json_new_object();
    ASSERT_TRUE(json->type==JSON_OBJ);
    ASSERT_TRUE(json->TYPE.obj!=NULL);
    json_free(json);
}

TEST(test,json_new_keyvalue)
{
    JSON *json=NULL;
    char key_int[10]="int"; 
    char key_bool[10]="bool";
    char key_str[10]="str";
    char key_str_modify[10]="strstr";
    char key_array[10]="array";
    char key_obj[10]="obj";
    char key_not_find[10]="not find";
    json=(JSON *)json_new_object();
    //int类型
    json->TYPE.obj->pair.push_back((keyvalue *)json_new_keyvalue(key_int, (JSON *)json_new_int(1)));
    JSON *json_get=(JSON *)json_get_value(json, key_int);
    ASSERT_TRUE(json_get!=NULL);
    ASSERT_TRUE(json_get->type==JSON_INT);
    ASSERT_TRUE(json_get->TYPE.num==1);
    ASSERT_TRUE(json_set_int(json, key_int, 2));
    json_get=(JSON *)json_get_value(json, key_int);
    ASSERT_TRUE(json_get->TYPE.num==2);
    ASSERT_TRUE(json_get_int(json, key_int, -1)==2);
    ASSERT_TRUE(json_get_int(json, key_not_find, -1)==-1);
    //bool类型
    json->TYPE.obj->pair.push_back((keyvalue *)json_new_keyvalue(key_bool, (JSON *)json_new_bool(0)));
    json_get=(JSON *)json_get_value(json, key_bool);
    ASSERT_TRUE(json_get!=NULL);
    ASSERT_TRUE(json_get->type==JSON_BOOL);
    ASSERT_TRUE(json_get->TYPE.bol==false);
    ASSERT_TRUE(json_set_bool(json, key_bool, true));
    ASSERT_TRUE(json_get_bool(json, key_bool)==1);
    ASSERT_TRUE(json_get_bool(json, key_not_find)==false);
    //str类型
    json->TYPE.obj->pair.push_back((keyvalue *)json_new_keyvalue(key_str, (JSON *)json_new_str(key_str)));
    json_get=(JSON *)json_get_value(json, key_str);
    ASSERT_TRUE(json_get!=NULL);
    ASSERT_TRUE(json_get->type==JSON_STR);
    ASSERT_TRUE(strcmp(json_get->TYPE.str,key_str)==0);
    ASSERT_TRUE(json_set_str(json, key_str, key_str_modify));
    ASSERT_TRUE(strcmp(json_get_str(json, key_str, key_not_find),key_str_modify)==0);
    ASSERT_TRUE(json_get_str(json,key_not_find,NULL)==NULL);
    //数组类型
    json->TYPE.obj->pair.push_back((keyvalue *)json_new_keyvalue(key_array, (JSON *)json_new_array()));
    json_get=(JSON *)json_get_value(json, key_array);
    ASSERT_TRUE(json_get!=NULL);
    ASSERT_TRUE(json_get->type==JSON_ARRAY);
    ASSERT_TRUE(json_get->TYPE.arr!=NULL);
    //对象类型
    json->TYPE.obj->pair.push_back((keyvalue *)json_new_keyvalue(key_obj, (JSON *)json_new_object()));
    json_get=(JSON *)json_get_value(json, key_obj);
    ASSERT_TRUE(json_get!=NULL);
    ASSERT_TRUE(json_get->type==JSON_OBJ);
    ASSERT_TRUE(json_get->TYPE.obj!=NULL);

    delete(json->TYPE.obj);
    json=(JSON *)json_new_array();
    json->TYPE.arr->val.push_back((JSON *)json_new_int(1));
    json->TYPE.arr->val.push_back((JSON *)json_new_bool(0));
    ASSERT_TRUE(json_get_index(json, 0)!=NULL);
    ASSERT_TRUE(json_get_index(json ,100)==NULL);

    json_free(json);
}

TEST(test, add_value)
{
     JSON *json=NULL;
     char key[10]="abc";
     json=(JSON*)json_add_value(json_new_int(1));
     ASSERT_TRUE(json->type==JSON_INT);
     ASSERT_TRUE(json->TYPE.num==1);

     json=(JSON*)json_add_value(json_new_bool(1));
     ASSERT_TRUE(json->type==JSON_BOOL);
     ASSERT_TRUE(json->TYPE.bol==true);
     
     json=(JSON*)json_add_value(json_new_str(key));
     ASSERT_TRUE(json->type==JSON_STR);
     ASSERT_TRUE(strcmp(json->TYPE.str,key)==0);

     json=(JSON*)json_add_value(json_new_array());
     ASSERT_TRUE(json->type==JSON_ARRAY);
     ASSERT_TRUE(json->TYPE.arr!=NULL);
     
     json=(JSON*)json_add_value(json_new_object());
     ASSERT_TRUE(json->type==JSON_OBJ);
     ASSERT_TRUE(json->TYPE.obj!=NULL);

     json_free(json);
}
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 
