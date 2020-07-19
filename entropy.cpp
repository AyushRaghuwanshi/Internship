#include <bits/stdc++.h> 
#include<map>
using namespace std;


map<string, int> word_dict = {
    {"garden",765},
    {"reject",1447},
    {"beauty",157},
    {"inch",914},
    {"scissors",1547},
    {"rifle",1486},
    {"amazing",62},
    {"couch",391},
    {"bacon",138},
    {"multiply",1163},
    {"swim",1759},
    {"poverty",1352},
    {"impose",912},
    {"spray",1687},
    {"ugly",1888},
    {"term",1787},
    {"stamp",1699},
    {"prevent",1362},
    {"nothing",1206},
    {"mutual",1169},
    {"awful",133},
    {"project",1376},
    {"wrist",2035},
    {"movie",1159},
};

string find_hex(string tmp){
        if      (!tmp.compare("0000")) return "0";
        else if (!tmp.compare("0001")) return "1";
        else if (!tmp.compare("0010")) return "2";
        else if (!tmp.compare("0011")) return "3";
        else if (!tmp.compare("0100")) return "4";
        else if (!tmp.compare("0101")) return "5";
        else if (!tmp.compare("0110")) return "6";
        else if (!tmp.compare("0111")) return "7";
        else if (!tmp.compare("1000")) return "8";
        else if (!tmp.compare("1001")) return "9";
        else if (!tmp.compare("1010")) return "A";
        else if (!tmp.compare("1011")) return "B";
        else if (!tmp.compare("1100")) return "C";
        else if (!tmp.compare("1101")) return "D";
        else if (!tmp.compare("1110")) return "E";
        else if (!tmp.compare("1111")) return "F";
}

string find_entropy(string *mnemonics, int word_len){
    //cout << mnemonics[4];
    int check_sum_len = 8;
    int mnemonics_index[word_len];
    string index_to_binary[word_len];
    string complete_bit_string;
    for(int i = 0; i < word_len; ++i){
        mnemonics_index[i] = word_dict[mnemonics[i]];
    }

    for(int i=0;i<word_len;++i){
        int n = mnemonics_index[i];
        while(n!=0) {index_to_binary[i]=(n%2==0 ?"0":"1")+index_to_binary[i]; n/=2;}
    }

    //cout << "00"+index_to_binary[0];
    //converting it to length 11
    for(int i=0;i<word_len;++i){
        string temp = index_to_binary[i];
        int extra_zeros = 11 - temp.size();
        string extra_zeros_str;
        for(int j=0;j<extra_zeros;++j){
            extra_zeros_str += "0";
        }
        index_to_binary[i] = extra_zeros_str + index_to_binary[i];
    }

    for(int i=0;i<word_len-1;++i){
       complete_bit_string += index_to_binary[i];
    }   

    for(int i=0;i<11-check_sum_len;++i){
        complete_bit_string += index_to_binary[word_len-1][i];
    }
    //cout<<complete_bit_string;
    string entropy;
    for(int i = 0;i < complete_bit_string.size(); i = i + 4){
        string temp;
        for(int j = 0;j < 4 ; j++){
            temp += complete_bit_string[i+j];
        }
        //cout<<find_hex(temp)<<" ";
        entropy += find_hex(temp);
    }
    //cout<<entropy.size();
    return entropy;

}


int main(){
    int word_len = 24;
    string mnemonics[word_len] = {"garden" ,"reject","beauty","inch","scissors","rifle","amazing","couch","bacon","multiply","swim","poverty","impose","spray","ugly","term","stamp","prevent",
    "nothing","mutual","awful","project","wrist","movie"};
    // cout<< mnemonics[3];
    cout << find_entropy(mnemonics, word_len);
}