#pragma once
#include<string>
#include<assert.h>

/*!
 * 空白(スペース，タブ)を削除
 * @param[inout] buf 処理文字列
 */
static void deleteSpace( std::string *buf )
{
    size_t pos;
    while((pos = buf->find_first_of(" 　\t")) != std::string::npos){
        buf->erase(pos, 1);
    }
}


/*!
 * 空白(スペース，タブ),改行を削除
 * @param[inout] buf 処理文字列
 */
static void deleteExtraChars( std::string *buf )
{
    size_t pos;
    while((pos = buf->find_first_of(" 　\t\n\r")) != std::string::npos){
        buf->erase(pos, 1);
    }
}
