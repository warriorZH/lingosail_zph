#ifndef _RC4_DECODE_H_
#define _RC4_DECODE_H_
/*********************
file name: RC4_decode.h
description: decode one file content by specified key and output decode content to specified file
date:2016-7-14
author: yuzhi-zhangpeihua
log:
*********************/
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class RC4
{
private:
    unsigned char S[256]; //״̬��������256�ֽ�
    unsigned char T[256]; //��ʱ��������256�ֽ�
    vector<char> keyStream;	  //��Կ��
public:

    void KSA_function(string const key_path);
    void PRGA_function(int textLen);
    void RC4_encoder(string const &src, string &tar);
    void file_encode(string const input_path, string const output_path);
    void RC4_decoder(string const &tar, string &src);
    void file_decode(string const input_path, string const output_path);
};


#endif // _RC4_DECODE_H_

