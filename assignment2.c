#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>
#include"bip39.h"
#include"curves.h"
#include"bip32.h"
#include"options.h"

typedef struct 
{
    uint8_t chain_index[4];
    uint8_t address_index[4];
}address_type;

typedef struct 
{
    uint8_t wallet_index[1];
    uint8_t purpose_index[4];
    uint8_t coin_index[4];
    uint8_t account_index[4];
    
    uint8_t input_count[1];
    address_type *input;
    
    uint8_t output_count[1];
    address_type *output;
    
    uint8_t change_count[1];
    address_type *change;

}txn_metadata; 


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

void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array, txn_metadata *txn_metadata_ptr){

    uint32_t offset = 0, len = 0;
    len = sizeof(txn_metadata_ptr->wallet_index);
    memcpy(txn_metadata_ptr, btc_txn_metadata_byte_array, len);
    offset += len;

    len = sizeof(txn_metadata_ptr->purpose_index);
    memcpy(txn_metadata_ptr->purpose_index, btc_txn_metadata_byte_array + offset, len);
    offset += len;

    len = sizeof(txn_metadata_ptr->coin_index);
    memcpy(txn_metadata_ptr->coin_index, btc_txn_metadata_byte_array + offset, len);
    offset += len;

    len = sizeof(txn_metadata_ptr->account_index);
    memcpy(txn_metadata_ptr->account_index, btc_txn_metadata_byte_array + offset, len);
    offset += len;

    len = sizeof(txn_metadata_ptr->input_count);
    memcpy(txn_metadata_ptr->input_count, btc_txn_metadata_byte_array + offset, len);
    offset += len;

    len = (*txn_metadata_ptr->input_count)*sizeof(address_type);
    txn_metadata_ptr->input = (address_type*)malloc(len);

    for(uint8_t i = 0; i < *txn_metadata_ptr->input_count; i++){
        len = sizeof(txn_metadata_ptr->input[i].address_index);
        memcpy(txn_metadata_ptr->input[i].address_index, btc_txn_metadata_byte_array + offset, len);
        offset += len;

        len = sizeof(txn_metadata_ptr->input[i].chain_index);
        memcpy(txn_metadata_ptr->input[i].chain_index, btc_txn_metadata_byte_array + offset, len);
        offset += len;
    }

    len = sizeof(txn_metadata_ptr->output_count);
    memcpy(txn_metadata_ptr->output_count, btc_txn_metadata_byte_array + offset, len);
    offset += len;

    len = (*txn_metadata_ptr->output_count)*sizeof(address_type);
    txn_metadata_ptr->output = (address_type*)malloc(len);

    for(uint8_t i = 0; i < *txn_metadata_ptr->output_count; i++){
        len = sizeof(txn_metadata_ptr->output[i].address_index);
        memcpy(txn_metadata_ptr->output[i].address_index, btc_txn_metadata_byte_array + offset, len);
        offset += len;

        len = sizeof(txn_metadata_ptr->output[i].chain_index);
        memcpy(txn_metadata_ptr->output[i].chain_index, btc_txn_metadata_byte_array + offset, len);
        offset += len;
    }

    len = (*txn_metadata_ptr->change_count)*sizeof(address_type);
    txn_metadata_ptr->change = (address_type*)malloc(len);

    for(uint8_t i = 0; i < *txn_metadata_ptr->change_count; i++){
        len = sizeof(txn_metadata_ptr->change[i].address_index);
        memcpy(txn_metadata_ptr->change[i].address_index, btc_txn_metadata_byte_array + offset, len);
        offset += len;

        len = sizeof(txn_metadata_ptr->change[i].chain_index);
        memcpy(txn_metadata_ptr->change[i].chain_index, btc_txn_metadata_byte_array + offset, len);
        offset += len;
    }


}

int main(){
    
    char hex_string[] = "018000002c80000001800000000100000000000000000200000000000000010000000100000000010000000100000000" ;
    uint8_t byte_array[strlen(hex_string)/2];
    char mnemonic[] = "miss guilt patient orchard poem inch shove rebuild sheriff ozone unveil brief ozone catch base insane among erupt cannon price traffic machine ride book";

    hex_string_to_byte_array(hex_string, strlen(hex_string), byte_array);
    


    txn_metadata txn_metadata_obj;
    uint32_t index;

    byte_array_to_txn_metadata(byte_array, &txn_metadata_obj);
    printf("%d %d",byte_array[13], *txn_metadata_obj.input_count);
    uint8_t seed[64];
    mnemonic_to_seed(mnemonic, "", seed, NULL);
    printf(" %d ", seed[63] );


    HDNode hdnode_out;
    hdnode_from_seed(seed, 64, SECP256K1_NAME, &hdnode_out);
    printf( "%d ", hdnode_out.chain_code[1]);
    
    memcpy(&index, &txn_metadata_obj.purpose_index, 4);
    hdnode_private_ckd(&hdnode_out, index);
    printf( "%d ", hdnode_out.chain_code[1]);

    memcpy(&index, &txn_metadata_obj.coin_index, 4);
    hdnode_private_ckd(&hdnode_out, index);
    printf( "%d ", hdnode_out.chain_code[1]);

    memcpy(&index, &txn_metadata_obj.account_index, 4);
    hdnode_private_ckd(&hdnode_out, index);
    printf( "%d ", hdnode_out.chain_code[1]);

    memcpy(&index, &txn_metadata_obj.input[0].chain_index, 4);
    hdnode_private_ckd(&hdnode_out, index);
    printf( "%d ", hdnode_out.chain_code[1]);

    memcpy(&index, &txn_metadata_obj.input[0].address_index, 4);
    hdnode_private_ckd(&hdnode_out, index);
    printf( "%d ", hdnode_out.chain_code[1]);

        for(int i = 0; i < 33; i++){
        printf(" %d", hdnode_out.public_key[i]);
    }

    hdnode_fill_public_key(&hdnode_out);
    printf( "%d \n", hdnode_out.chain_code[1]);

    for(int i = 0; i < 33; i++){
        printf(" %d", hdnode_out.public_key[i]);
    }

    

}