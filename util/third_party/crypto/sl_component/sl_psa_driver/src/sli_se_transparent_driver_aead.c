#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include "psa/crypto.h"
#include "sli_se_transparent_types.h"
#include "sli_se_transparent_functions.h"

#include <string.h>

psa_status_t sli_se_transparent_aead_encrypt(const psa_key_attributes_t *attributes,
                                             const uint8_t *key_buffer,
                                             size_t key_buffer_size,
                                             psa_algorithm_t alg,
                                             const uint8_t *nonce,
                                             size_t nonce_length,
                                             const uint8_t *additional_data,
                                             size_t additional_data_length,
                                             const uint8_t *plaintext,
                                             size_t plaintext_length,
                                             uint8_t *ciphertext,
                                             size_t ciphertext_size,
                                             size_t *ciphertext_length)
{
  return sli_se_driver_aead_encrypt(attributes,
                                    key_buffer,
                                    key_buffer_size,
                                    alg,
                                    nonce,
                                    nonce_length,
                                    additional_data,
                                    additional_data_length,
                                    plaintext,
                                    plaintext_length,
                                    ciphertext,
                                    ciphertext_size,
                                    ciphertext_length);
}

psa_status_t sli_se_transparent_aead_decrypt(const psa_key_attributes_t *attributes,
                                             const uint8_t *key_buffer,
                                             size_t key_buffer_size,
                                             psa_algorithm_t alg,
                                             const uint8_t *nonce,
                                             size_t nonce_length,
                                             const uint8_t *additional_data,
                                             size_t additional_data_length,
                                             const uint8_t *ciphertext,
                                             size_t ciphertext_length,
                                             uint8_t *plaintext,
                                             size_t plaintext_size,
                                             size_t *plaintext_length)
{
  return sli_se_driver_aead_decrypt(attributes,
                                    key_buffer,
                                    key_buffer_size,
                                    alg,
                                    nonce,
                                    nonce_length,
                                    additional_data,
                                    additional_data_length,
                                    ciphertext,
                                    ciphertext_length,
                                    plaintext,
                                    plaintext_size,
                                    plaintext_length);
}

psa_status_t sli_se_transparent_aead_encrypt_setup(sli_se_transparent_aead_operation_t *operation,
                                                   const psa_key_attributes_t *attributes,
                                                   const uint8_t *key_buffer,
                                                   size_t key_buffer_size,
                                                   psa_algorithm_t alg)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Start by resetting context
  memset(operation, 0, sizeof(*operation));

  // Setup generic context struct
  return sli_se_driver_aead_encrypt_decrypt_setup(&(operation->operation),
                                                  attributes,
                                                  key_buffer,
                                                  key_buffer_size,
                                                  alg,
                                                  SL_SE_ENCRYPT,
                                                  operation->key,
                                                  sizeof(operation->key),
                                                  0);
}

psa_status_t sli_se_transparent_aead_decrypt_setup(sli_se_transparent_aead_operation_t *operation,
                                                   const psa_key_attributes_t *attributes,
                                                   const uint8_t *key_buffer,
                                                   size_t key_buffer_size,
                                                   psa_algorithm_t alg)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Start by resetting context
  memset(operation, 0, sizeof(*operation));

  // Setup generic context struct
  return sli_se_driver_aead_encrypt_decrypt_setup(&(operation->operation),
                                                  attributes,
                                                  key_buffer,
                                                  key_buffer_size,
                                                  alg,
                                                  SL_SE_DECRYPT,
                                                  operation->key,
                                                  sizeof(operation->key),
                                                  0);
}

psa_status_t sli_se_transparent_aead_generate_nonce(sli_se_transparent_aead_operation_t *operation,
                                                    uint8_t *nonce,
                                                    size_t nonce_size,
                                                    size_t *nonce_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return sli_se_driver_aead_generate_nonce(&(operation->operation),
                                           nonce,
                                           nonce_size,
                                           nonce_length);
}

psa_status_t sli_se_transparent_aead_set_nonce(sli_se_transparent_aead_operation_t *operation,
                                               const uint8_t *nonce,
                                               size_t nonce_size)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return sli_se_driver_aead_set_nonce(&(operation->operation),
                                      nonce,
                                      nonce_size);
}

psa_status_t sli_se_transparent_aead_set_lengths(sli_se_transparent_aead_operation_t *operation,
                                                 size_t ad_length,
                                                 size_t plaintext_length)
{
  // TODO: when implementing AES-CCM, this will need to be fleshed out
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return sli_se_driver_aead_set_lengths(&(operation->operation),
                                        ad_length,
                                        plaintext_length);
}

psa_status_t sli_se_transparent_aead_update_ad(sli_se_transparent_aead_operation_t *operation,
                                               const uint8_t *input,
                                               size_t input_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  return sli_se_driver_aead_update_ad(&(operation->operation), operation->key, input, input_length);
}

psa_status_t sli_se_transparent_aead_update(sli_se_transparent_aead_operation_t *operation,
                                            const uint8_t *input,
                                            size_t input_length,
                                            uint8_t *output,
                                            size_t output_size,
                                            size_t *output_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  return sli_se_driver_aead_update(&(operation->operation),
                                   operation->key,
                                   input,
                                   input_length,
                                   output,
                                   output_size,
                                   output_length);
}

psa_status_t sli_se_transparent_aead_finish(sli_se_transparent_aead_operation_t *operation,
                                            uint8_t *ciphertext,
                                            size_t ciphertext_size,
                                            size_t *ciphertext_length,
                                            uint8_t *tag,
                                            size_t tag_size,
                                            size_t *tag_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return sli_se_driver_aead_finish(&(operation->operation),
                                   operation->key,
                                   ciphertext,
                                   ciphertext_size,
                                   ciphertext_length,
                                   tag,
                                   tag_size,
                                   tag_length);
}

psa_status_t sli_se_transparent_aead_verify(sli_se_transparent_aead_operation_t *operation,
                                            uint8_t *plaintext,
                                            size_t plaintext_size,
                                            size_t *plaintext_length,
                                            const uint8_t *tag,
                                            size_t tag_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return sli_se_driver_aead_verify(&(operation->operation),
                                   operation->key,
                                   plaintext,
                                   plaintext_size,
                                   plaintext_length,
                                   tag,
                                   tag_length);
}

psa_status_t sli_se_transparent_aead_abort(sli_se_transparent_aead_operation_t *operation)
{
  // No state is ever left in HW, so zeroing context should do the trick
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  memset(operation, 0, sizeof(*operation));
  return PSA_ERROR_NOT_SUPPORTED;
}

#endif // defined(SEMAILBOX_PRESENT)
