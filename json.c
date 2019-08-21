/*
 * =====================================================================================
 *
 *       Filename:  json.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/19 06:06:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  hao.gao (feyjobs), hao.gao@ele.me
 *   Organization:  inf
 *
 * =====================================================================================
 */

#include "sds/sds.h"
#include "json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

json parse(char* const source, int len);

int main(){
    char *source = "{\"name\":\"BeJson\",\"url\":\"http://www.bejson.com\",\"page\":88,\"isNonProfit\":true,\"address\":{\"street\":\"科技园路.\",\"city\":\"江苏苏州\",\"country\":\"中国\"},\"links\":[{\"name\":\"Google\",\"url\":\"http://www.google.com\"},{\"name\":\"Baidu\",\"url\":\"http://www.baidu.com\"},{\"name\":\"SoSo\",\"url\":\"http://www.SoSo.com\"}]}";
    int len = strlen(source);
    printf("%s",source);
    parse(source, len);
}

json parse(char* const source, int len){
    struct token *token;
    string *sourceFlow = (string*)malloc(sizeof(string));
    sourceFlow->data = source;
    sourceFlow->len = len;

    token = (struct token*)malloc(sizeof(struct token));
    token->next = NULL;
}

int lex(string *sourceFlow, struct token *token){
    char *ch = sourceFlow->data;
    char *pre;
    size_t pos = 0;
    int brCount = 0;
    int btCount = 0;

    enum {
        sl_start = 0,
        sl_str,
        sl_dig,
        sl_end
    } state;
    state = 0

    enum {
    } dig_state;
    state = 0
    while(pos < sourceFlow->len){
        switch (state):
        {
            case sl_start:
                switch(ch)
                {
                    case '{':
                        token->tyle = LBR;
                        state = sl_end;
                        brCount++;
                        break;
                    case '}':
                        token->tyle = RBR;
                        state = sl_end;
                        brCount--;
                        break;
                    case '[':
                        token->tyle = LBT;
                        state = sl_end;
                        btCount++;
                        break;
                    case ']':
                        token->tyle = RBT;
                        state = sl_end;
                        btCount--;
                        break;
                    case ':':
                        token->tyle = COL;
                        state = sl_end;
                        break;
                    case '"':
                        state = sl_str;
                        pre = ch;
                        break;
                }
                if(brCount < 0){
                    return JSON_ERR;
                }
                if(btCount < 0){
                    return JSON_ERR;
                }
                if(ch == ' ' || ch == '\t' || ch == '\n'|| ch == '\r'){
                    ch++;
                    pos++;
                    break;
                }
                if(ch >= '1' && ch <= '9'){
                    state = sl_dig;
                    pre = ch;
                }
                if(ch == '-'){
                    state = sl_dig;
                    pre = ch;
                }
                ch++;
                pos++;
                break;
            case sl_dig:

            case sl_end:
                token->next = (struct token*)malloc(sizeof(struct token));
                token = token->next;
                state = sl_start;
                break;
        }


    }

}
