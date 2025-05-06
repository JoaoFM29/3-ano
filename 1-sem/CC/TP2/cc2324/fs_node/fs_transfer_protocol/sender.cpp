#include <iostream>
using namespace std;


void reciever_mode(){

}

void sender_mode(char* socket){
    cout << "comunicar com" << socket <<"\n";
}

int main (int argc, char* argv[]) {

    if (argc == 1){

        reciever_mode();
    }
    else{
        sender_mode(argv[1]);
    }

    cout << "Thank you. Exiting." << endl;
    return 0;
}
