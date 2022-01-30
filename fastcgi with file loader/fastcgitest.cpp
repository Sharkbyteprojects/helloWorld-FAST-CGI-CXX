#include <iostream>
#include <fstream>
#include <string>
#include "fcgio.h"

using namespace std;

int main(void) {
    // Backup the stdio streambufs
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    ifstream indexhtml;
    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        indexhtml.open("./asset/index.html", ios::in);
        cout << "Content-type: text/html\r\n"
                << "X-Powered-By: Sharkbyteprojects\r\n"
                << "\r\n";
        if (indexhtml.is_open()){
            string tp;
            while(getline(indexhtml, tp)){  //read data from file object and put it into string.
                cout << tp << "\n";   //print the data of the string
            }
            indexhtml.close();
            cout << "\n";
        }else{
            cout << "<!DOCTYPE html><html><head><h1>Error to ReadFile</h1></head><body><h1>ERROR TO READ INDEX.HTML</h1></body></html>";
        }
        // Note: the fcgi_streambuf destructor will auto flush
    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}
