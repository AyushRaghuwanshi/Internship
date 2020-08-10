#include"BTC_btc.h"
#include <stdint.h>



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

uint8_t hex_to_dec(unsigned char hex[])
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


void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr)
    {

      uint32_t offset = 0, len = 0;
    
      len = sizeof(unsigned_txn_ptr->network_version);
      memcpy(unsigned_txn_ptr->network_version, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->input_count);
      memcpy(unsigned_txn_ptr->input_count, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = (*unsigned_txn_ptr->input_count)*sizeof(unsigned_txn_input); 
      unsigned_txn_ptr->input = (unsigned_txn_input*)malloc(len);
    
      for (uint8_t i = 0; i < *unsigned_txn_ptr->input_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        memcpy(unsigned_txn_ptr->input[i].previous_txn_hash, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
        memcpy(unsigned_txn_ptr->input[i].previous_output_index, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_length);
        memcpy(unsigned_txn_ptr->input[i].script_length, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_public_key);
        memcpy(unsigned_txn_ptr->input[i].script_public_key, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].sequence);
        memcpy(unsigned_txn_ptr->input[i].sequence, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->output_count);
      memcpy(unsigned_txn_ptr->output_count, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = (*unsigned_txn_ptr->output_count)*sizeof(txn_output); 
      unsigned_txn_ptr->output = (txn_output*)malloc(len);

      for (uint8_t i = 0; i < *unsigned_txn_ptr->output_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->output[i].value);
        memcpy(unsigned_txn_ptr->output[i].value, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_length);
        memcpy(unsigned_txn_ptr->output[i].script_length, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
        memcpy(unsigned_txn_ptr->output[i].script_public_key, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->locktime);
      memcpy(unsigned_txn_ptr->locktime, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->sighash);
      memcpy(unsigned_txn_ptr->sighash, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

    }

void serialize_unsigned_txn_to_sign(unsigned_txn *unsigned_txn_ptr, uint8_t input_index, uint8_t *btc_serialized_unsigned_txn){
    uint32_t offset = 0, len = 0;
    
    len = sizeof(unsigned_txn_ptr->network_version);
    memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->network_version, len);
    offset += len;

    len = sizeof(unsigned_txn_ptr->input_count);
    memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->input_count, len);
    offset += len;

    for(uint8_t i = 0; i < *unsigned_txn_ptr->input_count; i++){

        len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->input[i].previous_txn_hash, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[input_index].previous_output_index);
        memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->input[input_index].previous_output_index, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[input_index].script_length);
        memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->input[input_index].script_length, len);
        offset += len;

        len = unsigned_txn_ptr->input[input_index].script_length;
        if ( i == input_index){
            memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->input[i].script_public_key, len);
            offset += len;

        }
        else{
            memcpy(btc_serialized_unsigned_txn + offset, 0,1);
            offset += 1;
        }

        len = unsigned_txn_ptr->input[i].sequence;
        memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->input[i].sequence, len);
        offset += len;

    }


    len = sizeof(unsigned_txn_ptr->output_count);
    memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->output, len);
    offset += len;

    for(uint8_t i = 0; i < unsigned_txn_ptr->output_count; i++){
        
        len = sizeof(unsigned_txn_ptr->output[i].value);
        memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->output[i].value, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_length);
        memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->output[i].script_length, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
        memcpy(btc_serialized_unsigned_txn + offset, unsigned_txn_ptr->output[i].script_public_key, len);
        offset += len;


    }

    len = sizeof(unsigned_txn_ptr->locktime);
    memcpy(byte_array_to_txn_metadata + offset, unsigned_txn_ptr->locktime, len);
    offset += len;

    len = sizeof(unsigned_txn_ptr->sighash);
    memcpy(byte_array_to_txn_metadata + offset, unsigned_txn_ptr->sighash, len);
    offset += len;

}

uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr){

    uint32_t offset = 0;
    

}








