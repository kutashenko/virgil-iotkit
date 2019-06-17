
#include <helpers.h>
#include <virgil/iot/hsm/hsm_interface.h>

static const char key_raw[] = "Test data for kdf2";
static const char another_key_raw[] = "Another test data for kdf2";

/******************************************************************************/
static bool
_test_kdf2_step(vs_hsm_hash_type_e hash_type, const uint8_t *correct_result, uint16_t result_len) {
    uint8_t result_buf[result_len];
    uint8_t another_result_buf[result_len];

    VS_HSM_CHECK_RET(vs_hsm_kdf(KDF_2, hash_type, (uint8_t *)key_raw, strlen(key_raw), result_buf, result_len),
                     "ERROR while execute kdf");

    MEMCMP_CHECK_RET(result_buf, correct_result, result_len);

    VS_HSM_CHECK_RET(vs_hsm_kdf(KDF_2,
                                hash_type,
                                (uint8_t *)another_key_raw,
                                strlen(another_key_raw),
                                another_result_buf,
                                result_len),
                     "ERROR while execute kdf");

    BOOL_CHECK_RET(0 != memcmp(another_result_buf, correct_result, result_len), "Hash is constant");
    return true;
}

/******************************************************************************/
void
test_kdf2(void) {
    static const uint8_t sha256_result_raw[] = {
            0x85, 0xc0, 0x97, 0xf6, 0x09, 0xfb, 0x8c, 0x9b, 0xe6, 0xc4, 0xfa, 0xf1, 0x10, 0xde, 0xb6, 0xcf,
            0x9a, 0xda, 0xb0, 0xe4, 0x8a, 0x34, 0x50, 0xad, 0x96, 0xcc, 0xb0, 0x7a, 0xd1, 0x78, 0xed, 0xcc,
            0xca, 0x0d, 0x37, 0xfa, 0xc6, 0xba, 0x17, 0x35, 0x2a, 0xcf, 0xb6, 0x38, 0x2b, 0xe4, 0x45, 0xff,
            0xc7, 0x57, 0x15, 0x41, 0x38, 0x66, 0x34, 0xef, 0xb5, 0x5c, 0x7b, 0x06, 0x0a, 0x85, 0x22, 0xfc,
            0x98, 0x30, 0x26, 0x55, 0x71, 0xdd, 0x57, 0xb1, 0xbd, 0x72, 0xdc, 0xf4, 0x9d, 0xb5, 0xa4, 0xb7,
            0xd7, 0x22, 0x12, 0x19, 0x92, 0x59, 0x87, 0x07, 0xf1, 0x59, 0x0e, 0x1f, 0x0f, 0x3f, 0x99, 0x8e};

    static const uint8_t sha384_result_raw[] = {
            0xf8, 0xcb, 0x2b, 0x97, 0x55, 0xbd, 0xae, 0xdb, 0xb4, 0xcf, 0x97, 0x36, 0x00, 0xb9, 0x2f, 0x13,
            0x49, 0xd9, 0x9d, 0xd3, 0x79, 0x09, 0x92, 0x78, 0x38, 0x55, 0x77, 0x35, 0x22, 0x55, 0x82, 0x53,
            0x4b, 0xc0, 0x85, 0x40, 0xf1, 0xad, 0x73, 0x50, 0x4d, 0x71, 0x7f, 0x79, 0x99, 0x1c, 0x36, 0x63,
            0x0a, 0x81, 0xbc, 0x72, 0x58, 0x52, 0x35, 0xc9, 0xbb, 0x3d, 0xda, 0x11, 0x26, 0xc4, 0xee, 0xd2,
            0x51, 0xf7, 0x78, 0x33, 0xfd, 0x28, 0xdc, 0xca, 0x6d, 0x80, 0xa5, 0xea, 0x7f, 0x8d, 0xe1, 0xd1,
            0xde, 0x90, 0x78, 0xa3, 0x00, 0xf3, 0xa4, 0xb3, 0x7a, 0x70, 0x57, 0x97, 0xd0, 0x5d, 0xd6, 0xb9};

    static const uint8_t sha512_result_raw[] = {
            0xfe, 0x4f, 0xc9, 0x6e, 0xc9, 0x31, 0xde, 0x14, 0x3d, 0xec, 0x5f, 0x73, 0x5e, 0xae, 0xe3, 0xd4,
            0xb0, 0x62, 0xc8, 0x29, 0x9f, 0x45, 0xe8, 0xb9, 0xea, 0xaf, 0xed, 0xe7, 0x5e, 0x33, 0x2a, 0x91,
            0x97, 0x01, 0x4b, 0x31, 0x7d, 0xfb, 0x2e, 0xed, 0x75, 0x27, 0x68, 0xa3, 0xc2, 0xb4, 0x25, 0xa4,
            0xee, 0x9b, 0x1f, 0x53, 0xcb, 0x16, 0x22, 0x51, 0x53, 0x28, 0x2c, 0x28, 0xd7, 0xcb, 0xb8, 0xfc,
            0x2c, 0xab, 0xc7, 0x95, 0x1e, 0xb0, 0x6c, 0x39, 0x6b, 0x5b, 0xda, 0x0d, 0x42, 0x17, 0xab, 0x03,
            0x51, 0xc8, 0x15, 0x48, 0x68, 0x9c, 0xbc, 0x23, 0x91, 0xe6, 0x8a, 0xf2, 0x2c, 0xb2, 0x96, 0xc2};

    START_TEST("KDF2 tests");

    TEST_CASE_OK("SHA-256 usage", _test_kdf2_step(VS_HASH_SHA_256, sha256_result_raw, sizeof(sha256_result_raw)));
    TEST_CASE_OK("SHA-384 usage", _test_kdf2_step(VS_HASH_SHA_384, sha384_result_raw, sizeof(sha384_result_raw)));
    TEST_CASE_OK("SHA-512 usage", _test_kdf2_step(VS_HASH_SHA_512, sha512_result_raw, sizeof(sha512_result_raw)));

terminate:;
}
