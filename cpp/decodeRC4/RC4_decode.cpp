/*********************
file name: RC4_decode.cpp
description: decode one file content by specified key and output decode content to specified file
date:2016-7-14
author: yuzhi-zhangpeihua
log:
*********************/
#include "RC4_decode.h"
using namespace std;

/*********************
function name: KSA_function(string const key_path)
description: first step in RC4 algorithm, initial state of S and T for creating key-stream
parameters:
    key_path: file storage the key
return:
    none
*********************/
void RC4::KSA_function(string const key_path)
{
    string key;
    int keylen = 0;
    int j = 0;
    char tmp='a';
    ifstream in(key_path.c_str(), ios::in);
    if(!in.is_open())
    {
        cout<<"open key file error!!"<<endl;
        //exit(1);
    }
    //getline(in, key);
    istreambuf_iterator<char> beg(in), end;
    string strdata(beg, end);
    key = strdata;
    keylen = key.length();
    cout<<"key: "<<key<<endl;
    for(int i=0; i<256; i++)
    {
        this->S[i] = char(i);
        this->T[i] = key[i%keylen];
    }
    for(int i=0; i<256; i++)
    {
        j = (j + int(this->S[i]) + int(this->T[i]))%256;
        tmp = this->S[i];
        this->S[i] = this->S[j];
        this->S[j] = tmp;
    }
}

/*********************
function name: PRGA_function(int textLen)
description: second step in RC4 algorithm, creating key-stream
parameters:
    textLen: length of encrypted content
return:
    none
*********************/
void RC4::PRGA_function(int textLen)
{
    int i=0;
    int j=0;
    int k=0;
    char tmp;
    this->keyStream.clear();
    unsigned char SS[256];
    for(int i=0; i<256; i++)
    {
        SS[i] = this->S[i];
    }
    i=0;
    j=0;
    k=0;
    this->keyStream.clear();
    while(k<textLen)
    {
        i = (i+1)%256;
        j = (j+int(SS[i]))%256;
        tmp = SS[i];
        SS[i] = SS[j];
        SS[j] = tmp;
        this->keyStream.push_back(SS[(int(SS[i])+int(SS[j]))%256]);
        k++;
    }
    cout<<"SS:";
    cout<<endl;
    for(i=0; i<256; i++)
    {
        cout<<SS[i];
    }
    cout<<endl;
    cout<<"key stream:";
    for(vector<char>::iterator iter=this->keyStream.begin(); iter!=keyStream.end(); ++iter)
    {
        cout<<*iter;
    }
    cout<<endl;
}

/*********************
function name: RC4_encoder(string const &src, string &tar)
description: encode source into target by RC4
parameters:
    src: source content
    tar: target content
return:
    none
*********************/
void RC4::RC4_encoder(string const &src, string &tar)
{
    int textLen = src.length();
    cout<<"src length:"<<textLen<<endl;
    //this->PRGA_function(textLen);
    for(int i=0; i<textLen; i++)
    {
        tar += src[i]^this->keyStream[i];
    }
}

/*********************
function name: file_encode(string const input_path, string const output_path)
description: encode input file content into output file content by RC4
parameters:
    input_path: path of input file
    output_path: path of output file
return:
    none
*********************/
void RC4::file_encode(string const input_path, string const output_path)
{
    string inputline = "aa";
    string outputline = "bb";
    ifstream input_fd(input_path.c_str(), ios::in|ios::binary);
    ofstream output_fd(output_path.c_str(), ios::out|ios::binary);
    if(!input_fd.is_open())
    {
        cout<<"open input file error!!"<<endl;
        //exit(1);
    }
    if(!output_fd.is_open())
    {
        cout<<"open output file error!!"<<endl;
        //exit(1);
    }
    istreambuf_iterator<char> beg(input_fd), end;
    string strdata(beg, end);
    inputline = strdata;
    outputline.clear();
    cout<<"input_line:"<<inputline.c_str()<<endl;
    this->PRGA_function(inputline.length());
    this->RC4_encoder(inputline, outputline);
    outputline = outputline;
    cout<<"output_line:"<<outputline.c_str()<<endl;
    output_fd.write(outputline.c_str(), outputline.length());
}

/*********************
function name: RC4_decoder(string const &src, string &tar)
description: decode target into source by RC4
parameters:
    src: source content
    tar: target content
return:
    none
*********************/
void RC4::RC4_decoder(string const &tar, string &src)
{
    int textLen = tar.length();
    cout<<"tar length:"<<textLen<<endl;
    for(int i=0; i<textLen; i++)
    {
        src += tar[i]^this->keyStream[i];
    }
}

/*********************
function name: file_decode(string const input_path, string const output_path)
description: decode input file content into output file content by RC4
parameters:
    input_path: path of input file
    output_path: path of output file
return:
    none
*********************/
void RC4::file_decode(string const input_path, string const output_path)
{
    string inputline = "aa";
    string outputline = "bb";
    ifstream input_fd(input_path.c_str(), ios::in|ios::binary);
    ofstream output_fd(output_path.c_str(), ios::out|ios::binary);
    if(!input_fd.is_open())
    {
        cout<<"open input file error!!"<<endl;
        //exit(1);
    }
    if(!output_fd.is_open())
    {
        cout<<"open output file error!!"<<endl;
        //exit(1);
    }
    istreambuf_iterator<char> beg(input_fd), end;
    string strdata(beg, end);
    inputline = strdata;
    outputline.clear();
    cout<<"input_line:"<<inputline.c_str()<<endl;
    this->PRGA_function(inputline.length());
    this->RC4_encoder(inputline, outputline);
    outputline = outputline;
    cout<<"output_line:"<<outputline.c_str()<<endl;
    output_fd.write(outputline.c_str(), outputline.length());
}
