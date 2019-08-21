/*
 * =====================================================================================
 *
 *       Filename:  json.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/19 03:17:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  hao.gao (feyjobs), hao.gao@ele.me
 *   Organization:  inf
 *
 * =====================================================================================
 */

typedef int NODETYPE

#define STR 1
#define DIG 2
#define OBJ 3
#define ARR 4
#define TRU 5 
#define FAL 6
#define NUL 7
#define VAL 8
#define LBR 9
#define RBR 10
#define LBT 11
#define RBT 12
#define COL 13

#define JSON_ERR -1

struct node{
    NODETYPE type;
    void *value;
};

typedef struct {
    size_t len;
    char *data;
} string;

struct token{
    NODETYPE type;
    string* str;
    struct token *next;
};

typedef struct node* json;

json parse(char* const source, int len);
