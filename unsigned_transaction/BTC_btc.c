#include"BTC_btc.h"



int getNum(char ch)
{
    int num=0;
    if(ch>='0' && ch<='9')
    {
        num=ch-0x30;
    }
    else
    {
        switch(ch)
        {
            case 'A': case 'a': num=10; break;
            case 'B': case 'b': num=11; break;
            case 'C': case 'c': num=12; break;
            case 'D': case 'd': num=13; break;
            case 'E': case 'e': num=14; break;
            case 'F': case 'f': num=15; break;
            default: num=0;
        }
    }
    return num;
}

unsigned int hex_to_dec(unsigned char hex[])
{
    unsigned int x=0;
    x=(getNum(hex[0]))*16+(getNum(hex[1]));
}

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array){

    unsigned char temp[2];    

    for(uint32_t i = 0; i < string_length; i = i + 2){
        for(uint32_t j = 0; j < 2; j++){
            temp[j] = hex_string[i+j];
        }
        byte_array[i/2] = hex_to_dec(temp);
    }

}

void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr){

    memcpy(unsigned_txn_ptr, btc_unsigned_txn_byte_array, 4 + 1);
    unsigned_txn_ptr->input = (unsigned_txn_input*)malloc(sizeof(unsigned_txn_input)*unsigned_txn_ptr->input_count);
    uint32_t offset = 4 + 1;
    for(uint8_t i = 0; i < unsigned_txn_ptr->input_count; i++){
        memcpy((void*)&unsigned_txn_ptr->input[i], btc_unsigned_txn_byte_array + offset, 32 + 4 + 1 + 25 + 4);
        offset += 32 + 4 + 1 + 25 + 4;
    }

    memcpy((void*)&unsigned_txn_ptr->output_count, btc_unsigned_txn_byte_array + offset, 1);
    offset += 1;

    unsigned_txn_ptr->output = (txn_output*)malloc(sizeof(txn_output)*unsigned_txn_ptr->output_count);

    for(uint8_t i = 0; i < unsigned_txn_ptr->output_count; i++){
        memcpy((void*)&unsigned_txn_ptr->output[i], btc_unsigned_txn_byte_array + offset, 8 + 1 + 25);
        offset += 8 + 1 + 25;
    }   

    memcpy(unsigned_txn_ptr->locktime, btc_unsigned_txn_byte_array + offset, 4 + 4);


}



