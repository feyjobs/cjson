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
        sd_start = 0,
        sd_zero,
        sd_dig,
        sd_point,
        sd_point_dig,
        sd_science,
        sd_science_neg,
        sd_science_dig,
        sd_end
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
                    dig_state = sd_dig;
                }
                if(ch == '0'){
                    state = sl_dig;
                    pre = ch;
                    dig_state = sd_zero;
                }
                if(ch == '-'){
                    state = sl_dig;
                    dig_state = sd_start;
                    pre = ch;
                }
                ch++;
                pos++;
                break;
            case sl_dig:
                switch (dig_state){
                    case sd_start:
                        if(ch >= '1' && ch <= '9'){
                            dig_state = sd_dig;
                            break;
                        }
                        if(ch == '0'){
                            dig_state = sd_zero;
                            break;
                        }
                        return JSON_ERR;
                    case sd_zero:
                        if(ch == '.'){
                            dig_state = sd_point;
                            break;
                        }
                        if(ch == ' '||ch =='\n'||ch == '\r'||ch == '\t'||ch == ','|| ch == ']'||ch == '}'){
                            dig_state = sd_end;
                            state = sl_start;
                            break;
                        }
                        return JSON_ERR;
                    case sd_dig:
                        if(ch >= '0' && ch <= 9){
                            break;
                        }
                        if(ch == ' '||ch =='\n'||ch == '\r'||ch == '\t'||ch == ','|| ch == ']'||ch == '}'){
                            dig_state = sd_end;
                            state = sl_start;
                            break;
                        }
                        if(ch == '.'){
                            dig_state = sd_point;
                            break;
                        }
                        return JSON_ERR;
                    case sd_point:
                        if(ch >= '0' && ch <= '9'){
                            dig_state = sd_point_dig;
                            break;
                        }
                        return JSON_ERR;
                    case sd_point_dig:
                        if(ch >= '0' && ch <= 9){
                            break;
                        }
                        if(ch == ' '||ch =='\n'||ch == '\r'||ch == '\t'){
                            state = sl_start;
                            dig_state = sd_end; 
                            break;
                        }
                        if(ch == 'e' || ch == 'E'){
                            dig_state = sd_science;
                            break;
                        }
                        return JSON_ERR;
                    case sd_science:
                        if(ch == '-' || ch == '+'){
                            dig_state = sd_science_neg;
                            break;
                        }
                        if(ch >= '0' && ch <= 9){
                            dig_state = sd_science_dig;
                            break;
                        }
                        return JSON_ERR;
                    case sd_science_dig:
                        if(ch >= '0' && ch <= 9){
                            dig_state = sd_science_dig;
                            break;
                        }
                        if(ch == ' '||ch =='\n'||ch == '\r'||ch == '\t'){
                            state = sl_start;
                            dig_state = sd_end; 
                            break;
                        }
                        return JSON_ERR;
                }

                ch++;
                pos++;

            case sl_end:
                token->next = (struct token*)malloc(sizeof(struct token));
                token = token->next;
                state = sl_start;
                break;
        }


    }

}
