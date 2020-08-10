#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>
#include"bip39.h"
#include"curves.h"
#include"bip32.h"
#include"options.h"
#include"BTC_btc.h"






int main(){
    
    char hex_string[] = "018000002c80000001800000000100000000000000000200000000000000010000000100000000010000000100000000" ;
    uint8_t byte_array[strlen(hex_string)/2];
    char mnemonic[] = "miss guilt patient orchard poem inch shove rebuild sheriff ozone unveil brief ozone catch base insane among erupt cannon price traffic machine ride book";

    hex_string_to_byte_array(hex_string, strlen(hex_string), byte_array);
    
    

    txn_metadata txn_metadata_obj;
    uint32_t index;

    byte_array_to_txn_metadata(byte_array, &txn_metadata_obj);
    
    uint8_t seed[64];
    mnemonic_to_seed(mnemonic, "", seed, NULL);

    


    HDNode hdnode_out;
    hdnode_from_seed(seed, 64, SECP256K1_NAME, &hdnode_out);
   


    
    memcpy(&index, &txn_metadata_obj.purpose_index, 4);
    printf("%02x\n",__builtin_bswap32(index));
    hdnode_private_ckd(&hdnode_out, __builtin_bswap32(index));
    hdnode_fill_public_key(&hdnode_out);
    for(int i = 0;i< 33;i++){
        printf(" %02x ", hdnode_out.public_key[i] );
    }
    printf("\n");

    memcpy(&index, &txn_metadata_obj.coin_index, 4);
    printf("%02x\n",__builtin_bswap32(index));
    hdnode_private_ckd(&hdnode_out, __builtin_bswap32(index));
    hdnode_fill_public_key(&hdnode_out);
     for(int i = 0;i< 33;i++){
        printf(" %02x ", hdnode_out.public_key[i] );
    }
    printf("\n");

    memcpy(&index, &txn_metadata_obj.account_index, 4);
    printf("%02x\n",__builtin_bswap32(index));
    hdnode_private_ckd(&hdnode_out, __builtin_bswap32(index));
    hdnode_fill_public_key(&hdnode_out);
         for(int i = 0;i< 33;i++){
        printf(" %02x ", hdnode_out.public_key[i] );
    }
    printf("\n");

    memcpy(&index, &txn_metadata_obj.input[0].chain_index, 4);
    printf("%02x\n",__builtin_bswap32(index));
    hdnode_private_ckd(&hdnode_out, __builtin_bswap32(index));
    hdnode_fill_public_key(&hdnode_out);
         for(int i = 0;i< 33;i++){
        printf(" %02x ", hdnode_out.public_key[i] );
    }
    printf("\n");

    memcpy(&index, &txn_metadata_obj.input[0].address_index, 4);
    printf("%02x\n",__builtin_bswap32(index));
    hdnode_private_ckd(&hdnode_out, __builtin_bswap32(index));
    hdnode_fill_public_key(&hdnode_out);
         for(int i = 0;i< 33;i++){
        printf(" %02x ", hdnode_out.public_key[i] );
    }
    printf("\n");


 

    

}