#include <virgil/iot/tests/helpers.h>
#include <virgil/iot/converters/crypto_format_converters.h>
static const uint8_t virgil_SHA256_SECP192R1_sign[] = {
        0x30, 0x49, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01,
        0x05, 0x00, 0x04, 0x38, 0x30, 0x36, 0x02, 0x19, 0x00, 0x9F, 0x1A, 0x52, 0xD6, 0x9A, 0x0E,
        0xCD, 0x40, 0xEA, 0x7A, 0xA9, 0x9A, 0x4B, 0xCB, 0xA5, 0xFC, 0xE8, 0xD1, 0xDA, 0xB5, 0x58,
        0x5A, 0x3B, 0x37, 0x02, 0x19, 0x00, 0x80, 0x2E, 0xFF, 0xA9, 0x55, 0x54, 0xFD, 0x4E, 0x47,
        0x58, 0xDC, 0x7E, 0x33, 0x81, 0x08, 0xED, 0x46, 0xA9, 0x3B, 0xBD, 0x10, 0x1B, 0xEB, 0xEE};

static const uint8_t raw_SHA256_SECP192R1_sign[] = {
        0x9F, 0x1A, 0x52, 0xD6, 0x9A, 0x0E, 0xCD, 0x40, 0xEA, 0x7A, 0xA9, 0x9A, 0x4B, 0xCB, 0xA5, 0xFC,
        0xE8, 0xD1, 0xDA, 0xB5, 0x58, 0x5A, 0x3B, 0x37, 0x80, 0x2E, 0xFF, 0xA9, 0x55, 0x54, 0xFD, 0x4E,
        0x47, 0x58, 0xDC, 0x7E, 0x33, 0x81, 0x08, 0xED, 0x46, 0xA9, 0x3B, 0xBD, 0x10, 0x1B, 0xEB, 0xEE};

static const uint8_t virgil_SHA256_SECP224R1_sign[] = {
        0x30, 0x50, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00,
        0x04, 0x3F, 0x30, 0x3D, 0x02, 0x1C, 0x49, 0x80, 0x65, 0x6A, 0xE0, 0x1E, 0xA7, 0x33, 0x41, 0x4B, 0xAF,
        0x25, 0x7B, 0x1A, 0xBB, 0x7C, 0x50, 0x81, 0x90, 0xDC, 0xA0, 0x0F, 0x19, 0x0D, 0x1E, 0xFD, 0xB0, 0x2D,
        0x02, 0x1D, 0x00, 0x9C, 0x13, 0xDF, 0x28, 0xE1, 0x42, 0xE5, 0x72, 0x2D, 0x6B, 0x94, 0x86, 0xF9, 0x14,
        0x45, 0x0F, 0x12, 0xEA, 0xAC, 0x35, 0xCA, 0x87, 0x52, 0x19, 0x0E, 0x45, 0x93, 0x4E};

static const uint8_t raw_SHA256_SECP224R1_sign[] = {
        0x49, 0x80, 0x65, 0x6A, 0xE0, 0x1E, 0xA7, 0x33, 0x41, 0x4B, 0xAF, 0x25, 0x7B, 0x1A,
        0xBB, 0x7C, 0x50, 0x81, 0x90, 0xDC, 0xA0, 0x0F, 0x19, 0x0D, 0x1E, 0xFD, 0xB0, 0x2D,
        0x9C, 0x13, 0xDF, 0x28, 0xE1, 0x42, 0xE5, 0x72, 0x2D, 0x6B, 0x94, 0x86, 0xF9, 0x14,
        0x45, 0x0F, 0x12, 0xEA, 0xAC, 0x35, 0xCA, 0x87, 0x52, 0x19, 0x0E, 0x45, 0x93, 0x4E};

static const uint8_t virgil_SHA256_SECP256R1_sign[] = {
        0x30, 0x58, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04,
        0x47, 0x30, 0x45, 0x02, 0x21, 0x00, 0x89, 0x85, 0x8A, 0x30, 0x10, 0xE8, 0x3B, 0x88, 0x85, 0x9A, 0x3E, 0xED,
        0x95, 0xCF, 0xA0, 0xD9, 0xDB, 0xBD, 0x6B, 0x7A, 0xF0, 0x33, 0xAF, 0x59, 0xEB, 0x0E, 0x23, 0x89, 0x07, 0x48,
        0x8D, 0x5F, 0x02, 0x20, 0x0C, 0x5D, 0xE0, 0x76, 0x98, 0xF6, 0xFD, 0x02, 0x77, 0xFC, 0x27, 0x43, 0xFE, 0x53,
        0x59, 0xAB, 0xD9, 0x81, 0xE8, 0xDC, 0xEB, 0x33, 0xD5, 0xE8, 0x72, 0x82, 0xE3, 0x73, 0x7C, 0x31, 0xB3, 0xA4};

static const uint8_t raw_SHA256_SECP256R1_sign[] = {
        0x89, 0x85, 0x8A, 0x30, 0x10, 0xE8, 0x3B, 0x88, 0x85, 0x9A, 0x3E, 0xED, 0x95, 0xCF, 0xA0, 0xD9,
        0xDB, 0xBD, 0x6B, 0x7A, 0xF0, 0x33, 0xAF, 0x59, 0xEB, 0x0E, 0x23, 0x89, 0x07, 0x48, 0x8D, 0x5F,
        0x0C, 0x5D, 0xE0, 0x76, 0x98, 0xF6, 0xFD, 0x02, 0x77, 0xFC, 0x27, 0x43, 0xFE, 0x53, 0x59, 0xAB,
        0xD9, 0x81, 0xE8, 0xDC, 0xEB, 0x33, 0xD5, 0xE8, 0x72, 0x82, 0xE3, 0x73, 0x7C, 0x31, 0xB3, 0xA4};

static const uint8_t virgil_SHA256_SECP384R1_sign[] = {
        0x30, 0x78, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04,
        0x67, 0x30, 0x65, 0x02, 0x31, 0x00, 0xE3, 0xAF, 0xB4, 0x82, 0xFF, 0x62, 0x33, 0x64, 0x3C, 0xFD, 0x59, 0x3C,
        0x7C, 0x7F, 0xBA, 0xC2, 0x5E, 0xBB, 0xA7, 0x7B, 0x2F, 0xCD, 0xA0, 0x24, 0x23, 0xB9, 0xAE, 0xFD, 0xE3, 0x85,
        0x4B, 0xC1, 0x5C, 0x95, 0x73, 0xC0, 0x0A, 0xC0, 0x53, 0x11, 0xAA, 0x70, 0x94, 0xB0, 0xB4, 0x61, 0xF9, 0xDF,
        0x02, 0x30, 0x60, 0xD7, 0x91, 0x76, 0x62, 0x77, 0xDD, 0x6C, 0x7C, 0xC3, 0x51, 0x1D, 0xC1, 0xBF, 0x0F, 0x8F,
        0x8E, 0xF0, 0x15, 0xCC, 0x3B, 0xD8, 0xA1, 0x8C, 0xCA, 0x2E, 0xF3, 0x61, 0x71, 0xA9, 0x41, 0x77, 0x77, 0xF8,
        0x17, 0x24, 0x2D, 0x4E, 0x90, 0x6D, 0x0D, 0x3C, 0x33, 0x22, 0x07, 0x29, 0x7B, 0x7D};

static const uint8_t raw_SHA256_SECP384R1_sign[] = {
        0xE3, 0xAF, 0xB4, 0x82, 0xFF, 0x62, 0x33, 0x64, 0x3C, 0xFD, 0x59, 0x3C, 0x7C, 0x7F, 0xBA, 0xC2,
        0x5E, 0xBB, 0xA7, 0x7B, 0x2F, 0xCD, 0xA0, 0x24, 0x23, 0xB9, 0xAE, 0xFD, 0xE3, 0x85, 0x4B, 0xC1,
        0x5C, 0x95, 0x73, 0xC0, 0x0A, 0xC0, 0x53, 0x11, 0xAA, 0x70, 0x94, 0xB0, 0xB4, 0x61, 0xF9, 0xDF,
        0x60, 0xD7, 0x91, 0x76, 0x62, 0x77, 0xDD, 0x6C, 0x7C, 0xC3, 0x51, 0x1D, 0xC1, 0xBF, 0x0F, 0x8F,
        0x8E, 0xF0, 0x15, 0xCC, 0x3B, 0xD8, 0xA1, 0x8C, 0xCA, 0x2E, 0xF3, 0x61, 0x71, 0xA9, 0x41, 0x77,
        0x77, 0xF8, 0x17, 0x24, 0x2D, 0x4E, 0x90, 0x6D, 0x0D, 0x3C, 0x33, 0x22, 0x07, 0x29, 0x7B, 0x7D};

static const uint8_t virgil_SHA256_SECP521R1_sign[] = {
        0x30, 0x81, 0x9C, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00,
        0x04, 0x81, 0x8A, 0x30, 0x81, 0x87, 0x02, 0x42, 0x01, 0xC6, 0xA8, 0x30, 0x9C, 0x0F, 0xEA, 0xBD, 0x4D, 0xDD,
        0x22, 0x7F, 0x8E, 0x75, 0xBF, 0xA5, 0x1B, 0xBD, 0x09, 0x1D, 0x9A, 0x19, 0x45, 0x35, 0x3B, 0x3E, 0xDE, 0x84,
        0x5C, 0x5F, 0x63, 0x70, 0x31, 0x6A, 0xD2, 0xD3, 0xE0, 0x04, 0xEA, 0x66, 0xF8, 0x5B, 0x4A, 0xB5, 0x44, 0x29,
        0x38, 0x0B, 0x75, 0xBF, 0x85, 0xCB, 0xEB, 0x57, 0xF1, 0x41, 0xA3, 0xF2, 0x7D, 0x73, 0x77, 0x87, 0x88, 0xE8,
        0xDC, 0x01, 0x02, 0x41, 0x7D, 0x2D, 0x72, 0x8D, 0x37, 0x70, 0xCA, 0x83, 0x04, 0xCC, 0x8C, 0x89, 0x4D, 0x1A,
        0xD0, 0x55, 0x41, 0x4B, 0x35, 0x01, 0x21, 0x28, 0x1E, 0x3A, 0xE9, 0x73, 0x4B, 0x58, 0xA9, 0x6A, 0x60, 0xEE,
        0x3D, 0x7F, 0xC7, 0x10, 0x6F, 0xBD, 0x68, 0x4D, 0x33, 0xA0, 0x10, 0x58, 0xA4, 0x7B, 0xBE, 0x88, 0x31, 0xF4,
        0xBF, 0xD3, 0x1D, 0xB7, 0xE5, 0x9F, 0x55, 0x1D, 0x4B, 0xF5, 0x8E, 0xE9, 0x29, 0x25, 0x70};

static const uint8_t raw_SHA256_SECP521R1_sign[] = {
        0x01, 0xC6, 0xA8, 0x30, 0x9C, 0x0F, 0xEA, 0xBD, 0x4D, 0xDD, 0x22, 0x7F, 0x8E, 0x75, 0xBF, 0xA5, 0x1B,
        0xBD, 0x09, 0x1D, 0x9A, 0x19, 0x45, 0x35, 0x3B, 0x3E, 0xDE, 0x84, 0x5C, 0x5F, 0x63, 0x70, 0x31, 0x6A,
        0xD2, 0xD3, 0xE0, 0x04, 0xEA, 0x66, 0xF8, 0x5B, 0x4A, 0xB5, 0x44, 0x29, 0x38, 0x0B, 0x75, 0xBF, 0x85,
        0xCB, 0xEB, 0x57, 0xF1, 0x41, 0xA3, 0xF2, 0x7D, 0x73, 0x77, 0x87, 0x88, 0xE8, 0xDC, 0x01, 0x00, 0x7D,
        0x2D, 0x72, 0x8D, 0x37, 0x70, 0xCA, 0x83, 0x04, 0xCC, 0x8C, 0x89, 0x4D, 0x1A, 0xD0, 0x55, 0x41, 0x4B,
        0x35, 0x01, 0x21, 0x28, 0x1E, 0x3A, 0xE9, 0x73, 0x4B, 0x58, 0xA9, 0x6A, 0x60, 0xEE, 0x3D, 0x7F, 0xC7,
        0x10, 0x6F, 0xBD, 0x68, 0x4D, 0x33, 0xA0, 0x10, 0x58, 0xA4, 0x7B, 0xBE, 0x88, 0x31, 0xF4, 0xBF, 0xD3,
        0x1D, 0xB7, 0xE5, 0x9F, 0x55, 0x1D, 0x4B, 0xF5, 0x8E, 0xE9, 0x29, 0x25, 0x70};

static const uint8_t virgil_SHA256_ED25519_sign[] = {
        0x30, 0x51, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00,
        0x04, 0x40, 0x37, 0x91, 0x72, 0x95, 0x1A, 0x04, 0x4B, 0x6D, 0x5D, 0x8B, 0xCD, 0x09, 0x6A, 0xB7, 0xD6,
        0x98, 0x40, 0x38, 0xCB, 0x98, 0x9E, 0xC3, 0xC4, 0x66, 0x11, 0x6E, 0x10, 0xA2, 0x22, 0x2E, 0x54, 0xE6,
        0x00, 0x92, 0xE2, 0x3A, 0xF6, 0x55, 0x3B, 0xBD, 0xA4, 0x79, 0xD2, 0x0C, 0x2A, 0xF7, 0x6C, 0x26, 0xC1,
        0xAB, 0xED, 0xAF, 0x2B, 0x35, 0x3D, 0xCA, 0xCB, 0xF2, 0x6E, 0x4F, 0x99, 0x23, 0x7E, 0x09};

static const uint8_t raw_SHA256_ED25519_sign[] = {
        0x37, 0x91, 0x72, 0x95, 0x1A, 0x04, 0x4B, 0x6D, 0x5D, 0x8B, 0xCD, 0x09, 0x6A, 0xB7, 0xD6, 0x98,
        0x40, 0x38, 0xCB, 0x98, 0x9E, 0xC3, 0xC4, 0x66, 0x11, 0x6E, 0x10, 0xA2, 0x22, 0x2E, 0x54, 0xE6,
        0x00, 0x92, 0xE2, 0x3A, 0xF6, 0x55, 0x3B, 0xBD, 0xA4, 0x79, 0xD2, 0x0C, 0x2A, 0xF7, 0x6C, 0x26,
        0xC1, 0xAB, 0xED, 0xAF, 0x2B, 0x35, 0x3D, 0xCA, 0xCB, 0xF2, 0x6E, 0x4F, 0x99, 0x23, 0x7E, 0x09};

static const uint8_t virgil_SHA384_SECP256R1_sign[] = {
        0x30, 0x59, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02, 0x05,
        0x00, 0x04, 0x48, 0x30, 0x46, 0x02, 0x21, 0x00, 0x9C, 0x26, 0x2F, 0x82, 0x79, 0x54, 0xB9, 0xE4,
        0xDF, 0xCB, 0x29, 0x3C, 0x54, 0xEE, 0x31, 0xEE, 0x19, 0x37, 0x12, 0xE2, 0x74, 0xE2, 0x5C, 0x6B,
        0x6F, 0x44, 0x32, 0x8D, 0xFF, 0x21, 0xC4, 0x5B, 0x02, 0x21, 0x00, 0x92, 0x72, 0x41, 0x05, 0x14,
        0x7A, 0x7C, 0x0D, 0xF6, 0xBC, 0x88, 0xD7, 0x2A, 0x9C, 0xA6, 0x2F, 0x01, 0x15, 0xE6, 0x1C, 0xCE,
        0xDA, 0x6B, 0x2A, 0x53, 0x7B, 0x82, 0xFA, 0xDF, 0x67, 0xED, 0x9D};

static const uint8_t raw_SHA384_SECP256R1_sign[] = {
        0x9C, 0x26, 0x2F, 0x82, 0x79, 0x54, 0xB9, 0xE4, 0xDF, 0xCB, 0x29, 0x3C, 0x54, 0xEE, 0x31, 0xEE,
        0x19, 0x37, 0x12, 0xE2, 0x74, 0xE2, 0x5C, 0x6B, 0x6F, 0x44, 0x32, 0x8D, 0xFF, 0x21, 0xC4, 0x5B,
        0x92, 0x72, 0x41, 0x05, 0x14, 0x7A, 0x7C, 0x0D, 0xF6, 0xBC, 0x88, 0xD7, 0x2A, 0x9C, 0xA6, 0x2F,
        0x01, 0x15, 0xE6, 0x1C, 0xCE, 0xDA, 0x6B, 0x2A, 0x53, 0x7B, 0x82, 0xFA, 0xDF, 0x67, 0xED, 0x9D};

static const uint8_t virgil_SHA512_SECP256R1_sign[] = {
        0x30, 0x59, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03, 0x05,
        0x00, 0x04, 0x48, 0x30, 0x46, 0x02, 0x21, 0x00, 0xE3, 0x5A, 0x43, 0x72, 0x4F, 0xB8, 0x20, 0x66,
        0x6B, 0x62, 0xE3, 0x0E, 0xE6, 0x61, 0x09, 0x02, 0x0C, 0x61, 0x99, 0x65, 0x53, 0x53, 0x44, 0x98,
        0xE8, 0x56, 0xE2, 0xCB, 0xB0, 0xB2, 0x69, 0xD4, 0x02, 0x21, 0x00, 0x9F, 0xC4, 0xB4, 0x1F, 0x83,
        0x77, 0x20, 0x37, 0x95, 0x9C, 0xBE, 0xA2, 0x59, 0xBD, 0x0E, 0x96, 0x4D, 0xFB, 0x62, 0xCB, 0x06,
        0xAC, 0x42, 0xEC, 0x77, 0xD9, 0xAB, 0x19, 0x18, 0xDF, 0xEF, 0xF5};

static const uint8_t raw_SHA512_SECP256R1_sign[] = {
        0xE3, 0x5A, 0x43, 0x72, 0x4F, 0xB8, 0x20, 0x66, 0x6B, 0x62, 0xE3, 0x0E, 0xE6, 0x61, 0x09, 0x02,
        0x0C, 0x61, 0x99, 0x65, 0x53, 0x53, 0x44, 0x98, 0xE8, 0x56, 0xE2, 0xCB, 0xB0, 0xB2, 0x69, 0xD4,
        0x9F, 0xC4, 0xB4, 0x1F, 0x83, 0x77, 0x20, 0x37, 0x95, 0x9C, 0xBE, 0xA2, 0x59, 0xBD, 0x0E, 0x96,
        0x4D, 0xFB, 0x62, 0xCB, 0x06, 0xAC, 0x42, 0xEC, 0x77, 0xD9, 0xAB, 0x19, 0x18, 0xDF, 0xEF, 0xF5};

/******************************************************************************/
static bool
_test_case_converters_sign_pass(vs_hsm_hash_type_e hash_alg,
                                vs_hsm_keypair_type_e keypair_type,
                                const uint8_t *virgil_sign,
                                uint16_t virgil_sign_sz,
                                const uint8_t *raw_sign,
                                uint16_t raw_sign_sz) {
    uint8_t result_buf[RESULT_BUF_SIZE];
    uint16_t result_sz;

    BOOL_CHECK_RET(vs_converters_virgil_sign_to_raw(
                           keypair_type, virgil_sign, virgil_sign_sz, result_buf, sizeof(result_buf), &result_sz),
                   "ERROR while convert signature virgil to raw");

    BOOL_CHECK_RET(result_sz == raw_sign_sz, "ERROR raw signature has wrong size");
    MEMCMP_CHECK_RET(result_buf, raw_sign, raw_sign_sz);

    BOOL_CHECK_RET(vs_converters_raw_sign_to_virgil(
                           keypair_type, hash_alg, raw_sign, raw_sign_sz, result_buf, sizeof(result_buf), &result_sz),
                   "ERROR while convert signature raw to virgil");

    BOOL_CHECK_RET(result_sz == virgil_sign_sz, "ERROR virgil signature has wrong size");
    MEMCMP_CHECK_RET(result_buf, virgil_sign, virgil_sign_sz);

    return true;
}


/******************************************************************************/
uint16_t
test_sign_converters(void) {
    uint16_t failed_test_result = 0;

#define TEST_CONVERTERS_SIGN_PASS(HASH, KEYPAIR)                                                                       \
    do {                                                                                                               \
        vs_hsm_hash_type_e hash_alg = VS_HASH_SHA_##HASH;                                                              \
        vs_hsm_keypair_type_e keypair_type = VS_KEYPAIR_EC_##KEYPAIR;                                                  \
        const uint8_t *virgil_sign = virgil_SHA##HASH##_##KEYPAIR##_sign;                                              \
        uint16_t virgil_sign_sz = sizeof(virgil_SHA##HASH##_##KEYPAIR##_sign);                                         \
        const uint8_t *raw_sign = raw_SHA##HASH##_##KEYPAIR##_sign;                                                    \
        uint16_t raw_sign_sz = sizeof(raw_SHA##HASH##_##KEYPAIR##_sign);                                               \
        TEST_CASE_OK("hash " #HASH ", key " #KEYPAIR,                                                                  \
                     _test_case_converters_sign_pass(                                                                  \
                             hash_alg, keypair_type, virgil_sign, virgil_sign_sz, raw_sign, raw_sign_sz));             \
    } while (0)

    START_TEST("Signatures converters");
    TEST_CONVERTERS_SIGN_PASS(256, SECP192R1);
    TEST_CONVERTERS_SIGN_PASS(256, SECP224R1);
    TEST_CONVERTERS_SIGN_PASS(256, SECP256R1);
    TEST_CONVERTERS_SIGN_PASS(256, SECP384R1);
    TEST_CONVERTERS_SIGN_PASS(256, SECP521R1);
    TEST_CONVERTERS_SIGN_PASS(256, ED25519);
    TEST_CONVERTERS_SIGN_PASS(384, SECP256R1);
    TEST_CONVERTERS_SIGN_PASS(512, SECP256R1);

terminate:
    return failed_test_result;

#undef TEST_CONVERTERS_SIGN_PASS
}
