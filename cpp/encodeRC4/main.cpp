#include <iostream>
#include "RC4_encode.h"


using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 4)
    {
        RC4 rc4Obj = RC4();
        rc4Obj.KSA_function(argv[1]);
        rc4Obj.file_encode(argv[2], argv[3]);
        //rc4Obj.file_decode(argv[3], argv[4]);
    }
    else
    {
        cout<<"input form: encodeRC4 key_path input_path output_path"<<endl;
    }
    //cout << "Hello world!" << endl;
    return 0;
}
