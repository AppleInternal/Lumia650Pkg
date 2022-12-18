/** @file PlatformKeyLib.c

  Copyright (C) Microsoft Corporation. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>
#include <UefiSecureBoot.h>
#include <Guid/ImageAuthentication.h>
#include <Library/SecureBootVariableLib.h>

#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

#include "MsSecureBootDefaultVars.h"

#define PLATFORM_SECURE_BOOT_KEY_COUNT  1

SECURE_BOOT_PAYLOAD_INFO  *gSecureBootPayload     = NULL;
UINT8                     gSecureBootPayloadCount = 0;

// Windows On Andromeda Root Platform Key
CONST UINT8  mDevelopmentPlatformKeyCertificate[] = {
  0xA1, 0x59, 0xC0, 0xA5, 0xE4, 0x94, 0xA7, 0x4A, 0x87, 0xB5, 0xAB, 0x15, 0x5C, 0x2B, 0xF0, 0x72, 0x93, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x05, 0x00, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x30, 0x82, 0x05, 0x63, 0x30, 0x82, 0x03, 0x4B, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x10, 0xE1, 0x0A, 0x47, 0x60, 0xAC, 0xDC, 0x9F, 0xB2, 0x49, 0x07, 0x1A, 0x23, 0x80, 0x2F, 0x36, 0x6B, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x0B, 0x05, 0x00, 0x30, 0x31, 0x31, 0x2F, 0x30, 0x2D, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x26, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73, 0x20, 0x4F, 0x6E, 0x20, 0x41, 0x6E, 0x64, 0x72, 0x6F, 0x6D, 0x65, 0x64, 0x61, 0x20, 0x52, 0x6F, 0x6F, 0x74, 0x20, 0x50, 0x6C, 0x61, 0x74, 0x66, 0x6F, 0x72, 0x6D, 0x20, 0x4B, 0x65, 0x79, 0x30, 0x1E, 0x17, 0x0D, 0x32, 0x32, 0x30, 0x35, 0x32, 0x31, 0x31, 0x33, 0x34, 0x31, 0x33, 0x32, 0x5A, 0x17, 0x0D, 0x33, 0x39, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39, 0x5A, 0x30, 0x31, 0x31, 0x2F, 0x30, 0x2D, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x26, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73, 0x20, 0x4F, 0x6E, 0x20, 0x41, 0x6E, 0x64, 0x72, 0x6F, 0x6D, 0x65, 0x64, 0x61, 0x20, 0x52, 0x6F, 0x6F, 0x74, 0x20, 0x50, 0x6C, 0x61, 0x74, 0x66, 0x6F, 0x72, 0x6D, 0x20, 0x4B, 0x65, 0x79, 0x30, 0x82, 0x02, 0x22, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x02, 0x0F, 0x00, 0x30, 0x82, 0x02, 0x0A, 0x02, 0x82, 0x02, 0x01, 0x00, 0xBB, 0x5B, 0x1B, 0x46, 0x82, 0x38, 0x33, 0x6A, 0xCF, 0xB9, 0x18, 0xD6, 0xF7, 0x46, 0x9D, 0xD4, 0x09, 0x48, 0x23, 0x14, 0xCA, 0xAA, 0x5E, 0xAE, 0xD3, 0xCB, 0xDD, 0x95, 0xB5, 0x31, 0x8D, 0xD8, 0xFE, 0x4B, 0xBF, 0xC0, 0xD1, 0x62, 0x9E, 0x4F, 0xA6, 0x75, 0xE7, 0xDF, 0xF9, 0x62, 0x77, 0x74, 0xB6, 0xEF, 0x32, 0xE3, 0xF7, 0x1D, 0x9B, 0x12, 0xF7, 0x13, 0x9C, 0xB5, 0x5D, 0x19, 0x34, 0xD6, 0x85, 0x23, 0x55, 0xDC, 0x73, 0xE9, 0x3A, 0x6C, 0x4F, 0x2B, 0xE4, 0x48, 0x1D, 0xB5, 0x8E, 0xEF, 0x39, 0xB8, 0x5E, 0x97, 0x1E, 0x2E, 0xA8, 0xD5, 0xD8, 0xC2, 0x32, 0x9A, 0x40, 0x1F, 0xEE, 0xB1, 0xA9, 0x2F, 0x19, 0x70, 0x27, 0xCC, 0x5E, 0xA9, 0xA2, 0x48, 0x90, 0x79, 0x3C, 0xF4, 0x38, 0x30, 0xCA, 0x9E, 0x25, 0x05, 0x28, 0x20, 0x22, 0xA3, 0x6E, 0x1A, 0xDD, 0xEC, 0x76, 0xA2, 0x8B, 0xE7, 0x60, 0x3A, 0x13, 0xB5, 0xD8, 0xB2, 0x42, 0x40, 0xB1, 0x28, 0x62, 0x9C, 0x7D, 0x57, 0x40, 0x6A, 0x2E, 0x01, 0xF6, 0x85, 0xD6, 0x3E, 0x36, 0xC2, 0x88, 0x69, 0x16, 0x3D, 0x3C, 0xD1, 0x74, 0xD4, 0x1B, 0xB5, 0xA9, 0x18, 0x56, 0x65, 0x08, 0xA8, 0x5A, 0x5D, 0x1B, 0x63, 0x8E, 0xE5, 0x7F, 0x66, 0xF3, 0x98, 0x10, 0x6F, 0x4F, 0x6B, 0xAF, 0x7F, 0x63, 0x46, 0x7B, 0x3C, 0xBC, 0x46, 0x73, 0x3E, 0xA0, 0xB1, 0x77, 0x4C, 0x40, 0x58, 0xBA, 0xFA, 0x18, 0xA8, 0x66, 0x2D, 0xB6, 0x72, 0x1A, 0x5F, 0xD7, 0x40, 0xC4, 0xA4, 0x44, 0x2E, 0xBB, 0x55, 0x1D, 0x65, 0x14, 0xCB, 0x64, 0x81, 0x8B, 0xB0, 0xED, 0xA8, 0xEA, 0xD9, 0x29, 0xE0, 0x04, 0x36, 0xB7, 0x82, 0xB2, 0x98, 0x76, 0x56, 0x6A, 0xDC, 0x49, 0x95, 0x37, 0xEF, 0x48, 0xC3, 0x0A, 0xB7, 0x5B, 0xA4, 0xFC, 0x90, 0x3D, 0xE9, 0x8B, 0xE3, 0xFC, 0xC5, 0x5E, 0x02, 0xB5, 0x5F, 0x5A, 0x88, 0x7A, 0xC0, 0x32, 0xC8, 0x26, 0x45, 0xE6, 0xF1, 0x16, 0x37, 0x08, 0x79, 0x75, 0x39, 0x49, 0xFE, 0xE8, 0x7F, 0x87, 0x5B, 0xB0, 0x0C, 0x92, 0x5B, 0xCA, 0x53, 0x5F, 0x1A, 0xF5, 0x35, 0xEF, 0x4C, 0x9E, 0xF5, 0xF3, 0x0D, 0x30, 0x44, 0xA4, 0x73, 0x23, 0x3C, 0x56, 0xF9, 0xC6, 0xCD, 0x56, 0x1D, 0x3D, 0x86, 0x57, 0xC4, 0x0F, 0x9B, 0x4B, 0xE3, 0x03, 0x67, 0xCD, 0xBF, 0x20, 0x71, 0x02, 0x4B, 0x29, 0xBC, 0xC4, 0x8E, 0x66, 0x9B, 0xB7, 0xD6, 0x36, 0x3E, 0xBC, 0x04, 0x41, 0x44, 0xF1, 0x6D, 0xDA, 0xE3, 0x11, 0x9A, 0x60, 0xE7, 0xC7, 0xB9, 0x24, 0x84, 0xEC, 0x8C, 0xF4, 0xC2, 0xB6, 0x57, 0x54, 0x11, 0xED, 0xCF, 0xCF, 0xD1, 0x7E, 0x27, 0x65, 0x66, 0x02, 0x19, 0xCD, 0xBF, 0x34, 0x04, 0xC3, 0x1E, 0x09, 0x6F, 0x62, 0xDF, 0x70, 0xE1, 0x29, 0x88, 0xB9, 0xF1, 0x96, 0x64, 0x40, 0xE9, 0x57, 0x3F, 0xBE, 0xE8, 0x96, 0x54, 0xB7, 0xDB, 0xEC, 0x68, 0xA1, 0x99, 0x21, 0x70, 0x8D, 0x9D, 0x6F, 0x0B, 0xB5, 0xCC, 0x19, 0x88, 0xFA, 0x9C, 0xBE, 0xEF, 0xD0, 0x6C, 0xC5, 0x19, 0x87, 0x2A, 0x8D, 0x54, 0xA6, 0x3B, 0xB5, 0xDB, 0x05, 0xD4, 0xB7, 0xA8, 0x55, 0x0B, 0xBA, 0xDB, 0xEE, 0xDC, 0xE1, 0x0D, 0xAE, 0xF0, 0x33, 0xAF, 0x00, 0x57, 0x44, 0xDE, 0x54, 0x67, 0xCB, 0x7A, 0x04, 0x98, 0x9E, 0x18, 0xC3, 0x15, 0x75, 0x7A, 0x3A, 0x68, 0x63, 0x03, 0xCD, 0x2B, 0x82, 0x79, 0xD8, 0xE7, 0xA0, 0xC8, 0x79, 0x82, 0x44, 0x25, 0x60, 0x93, 0x7B, 0xB6, 0x72, 0xBC, 0x32, 0xBF, 0x05, 0xD2, 0xBB, 0x63, 0x39, 0x89, 0xCA, 0x68, 0xB1, 0x0B, 0x96, 0x2A, 0x0F, 0x19, 0x1B, 0x7A, 0x9B, 0xC9, 0x66, 0xCB, 0x15, 0xD2, 0x6F, 0x05, 0xC6, 0x4D, 0x02, 0x03, 0x01, 0x00, 0x01, 0xA3, 0x77, 0x30, 0x75, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x1D, 0x13, 0x01, 0x01, 0xFF, 0x04, 0x05, 0x30, 0x03, 0x01, 0x01, 0xFF, 0x30, 0x62, 0x06, 0x03, 0x55, 0x1D, 0x01, 0x04, 0x5B, 0x30, 0x59, 0x80, 0x10, 0x31, 0x68, 0xC7, 0x48, 0xB9, 0x6A, 0x17, 0x07, 0x19, 0x7F, 0xE8, 0x44, 0xB9, 0xEA, 0x89, 0xA2, 0xA1, 0x33, 0x30, 0x31, 0x31, 0x2F, 0x30, 0x2D, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x26, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73, 0x20, 0x4F, 0x6E, 0x20, 0x41, 0x6E, 0x64, 0x72, 0x6F, 0x6D, 0x65, 0x64, 0x61, 0x20, 0x52, 0x6F, 0x6F, 0x74, 0x20, 0x50, 0x6C, 0x61, 0x74, 0x66, 0x6F, 0x72, 0x6D, 0x20, 0x4B, 0x65, 0x79, 0x82, 0x10, 0xE1, 0x0A, 0x47, 0x60, 0xAC, 0xDC, 0x9F, 0xB2, 0x49, 0x07, 0x1A, 0x23, 0x80, 0x2F, 0x36, 0x6B, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x0B, 0x05, 0x00, 0x03, 0x82, 0x02, 0x01, 0x00, 0x63, 0x92, 0x92, 0x00, 0x57, 0xD8, 0x6C, 0x75, 0xB2, 0x4F, 0xB3, 0xD1, 0x4D, 0x99, 0x2C, 0x3A, 0x0A, 0xF1, 0xB7, 0x04, 0xC7, 0x57, 0x01, 0x21, 0x1B, 0x64, 0xD8, 0xC7, 0x5A, 0xAB, 0xD4, 0xBA, 0xC8, 0x5B, 0x43, 0x3A, 0x70, 0xC5, 0xCC, 0x21, 0x7C, 0xFC, 0xD7, 0x76, 0x5B, 0xC8, 0x64, 0xA5, 0x69, 0x7C, 0xD5, 0xED, 0x3D, 0xCA, 0xE7, 0x73, 0xA7, 0xEC, 0xDB, 0x0B, 0x82, 0xB0, 0x89, 0x97, 0x5C, 0xEF, 0x65, 0x68, 0xDC, 0xCD, 0x7C, 0xC7, 0x85, 0xDF, 0x80, 0x2B, 0xFC, 0xFC, 0xF3, 0x04, 0x21, 0xB7, 0xD2, 0x3A, 0x5E, 0x8A, 0x26, 0xF0, 0xCF, 0x8E, 0xE2, 0x9E, 0x14, 0xCE, 0xDF, 0x2A, 0x6F, 0x86, 0x12, 0x5E, 0x06, 0x0A, 0x6E, 0x68, 0x42, 0x0F, 0x03, 0xCA, 0xE2, 0x38, 0x22, 0xF9, 0xEE, 0x08, 0xB6, 0x01, 0xB3, 0x61, 0x6E, 0x15, 0x26, 0x0B, 0x1A, 0xA6, 0xEF, 0xA6, 0x9C, 0x6E, 0xAC, 0xF3, 0xF6, 0x3C, 0xF1, 0x3E, 0x4A, 0x4F, 0x0A, 0x62, 0x54, 0xB0, 0x69, 0x3D, 0x55, 0x26, 0xCA, 0x10, 0x70, 0xF4, 0x58, 0x41, 0x25, 0x4E, 0x8E, 0x68, 0x31, 0x91, 0xC0, 0xF7, 0x7A, 0xA4, 0xC9, 0xBF, 0xE5, 0x99, 0xEF, 0x0B, 0xC8, 0xBF, 0xE9, 0x4B, 0xD3, 0x3F, 0xC2, 0x17, 0xBE, 0x7C, 0x89, 0xF1, 0xF9, 0xA1, 0x20, 0x9C, 0xE5, 0x88, 0x68, 0x94, 0xE2, 0xD9, 0x26, 0x51, 0x94, 0x0B, 0xCF, 0x5F, 0xA0, 0x7E, 0x6B, 0x67, 0xA6, 0x1B, 0x32, 0x59, 0xFE, 0xDE, 0x23, 0x47, 0xC0, 0x6D, 0xE8, 0x28, 0xE9, 0xA9, 0x40, 0xDB, 0x16, 0xEB, 0x66, 0x76, 0x14, 0x94, 0xD5, 0xC3, 0x0C, 0x1C, 0xB9, 0x54, 0x17, 0xFF, 0x2B, 0x10, 0x0B, 0x66, 0x24, 0x1B, 0x2D, 0xBA, 0x19, 0x04, 0x5B, 0x72, 0x63, 0xD6, 0xF5, 0x2D, 0xAF, 0x1E, 0x6C, 0xF1, 0xE3, 0x57, 0xFB, 0x0C, 0xA7, 0xAD, 0x0F, 0x1B, 0x3F, 0x94, 0x15, 0x3E, 0xDF, 0x72, 0xB7, 0x06, 0xA2, 0xF6, 0xEA, 0xD8, 0xA2, 0x27, 0x31, 0xBF, 0xBF, 0xA2, 0x50, 0x1F, 0x30, 0xD2, 0x9D, 0x47, 0x66, 0x81, 0x4C, 0xA1, 0xC4, 0x2F, 0xD0, 0xF0, 0x5B, 0x33, 0xB4, 0x02, 0x48, 0x16, 0x6D, 0x89, 0xF2, 0x3A, 0x4B, 0x9C, 0x10, 0x5B, 0x3A, 0x71, 0x35, 0xB4, 0x79, 0x7A, 0x58, 0xAB, 0x91, 0x7A, 0x49, 0xDE, 0x97, 0x3D, 0xB1, 0xD7, 0xDC, 0x68, 0xD2, 0xAE, 0xB5, 0x8D, 0x09, 0xAC, 0x51, 0x64, 0x93, 0x02, 0x86, 0x7E, 0xE0, 0x50, 0xC6, 0x06, 0x2B, 0x80, 0xDB, 0x1E, 0x38, 0x3B, 0x03, 0xC5, 0x1C, 0xAE, 0x2E, 0x85, 0x45, 0x50, 0x33, 0x63, 0x46, 0xC0, 0x96, 0x74, 0x5A, 0x6F, 0x63, 0xD3, 0x3F, 0xF2, 0xD6, 0x9D, 0x6F, 0xD6, 0x4B, 0x5D, 0x54, 0xEB, 0x88, 0xF9, 0x9A, 0x30, 0xB6, 0xD3, 0x3B, 0xDC, 0x0A, 0xE4, 0xF9, 0x07, 0xFE, 0xEE, 0x4D, 0x69, 0x7B, 0x1A, 0xC2, 0x5F, 0x3E, 0xE3, 0xF0, 0xDA, 0xC1, 0x9E, 0x9A, 0x68, 0x40, 0x96, 0x48, 0x1C, 0x1F, 0x38, 0x5C, 0xB3, 0x4E, 0xFB, 0xF7, 0x96, 0xEC, 0x94, 0x0B, 0x70, 0x29, 0xFF, 0x57, 0x7D, 0xA7, 0xBC, 0xB3, 0x65, 0x65, 0xEE, 0x48, 0xEF, 0x72, 0x7A, 0x14, 0x7B, 0x92, 0x9C, 0x43, 0x33, 0x66, 0x77, 0x54, 0x0E, 0xC1, 0xFC, 0x58, 0xCC, 0x09, 0x5C, 0x57, 0x37, 0x35, 0x05, 0x45, 0x2D, 0x8C, 0xA3, 0xD3, 0xE7, 0x5C, 0x2C, 0xE2, 0x7B, 0xAE, 0xAB, 0x4E, 0x0F, 0x93, 0xF0, 0x4F, 0x7D, 0xDF, 0x44, 0xF5, 0x89, 0xC6, 0x9E, 0x93, 0x28, 0x2B, 0x6C, 0xCF, 0x8B, 0xBF, 0x3C, 0x1A, 0x19, 0x78, 0x08, 0xF3, 0x73, 0x0B, 0x53, 0xB0, 0x2C, 0xAC, 0xEE, 0x28, 0xBA, 0x71, 0x9B, 0xCB, 0x8C, 0x21, 0xF1, 0xA1, 0x44, 0xE6, 0xBF, 0xA9, 0x03, 0xD5, 0x7B, 0x04, 0x53, 0x50, 0x4B
};

UINT8                     mSecureBootPayloadCount                            = PLATFORM_SECURE_BOOT_KEY_COUNT;
SECURE_BOOT_PAYLOAD_INFO  mSecureBootPayload[PLATFORM_SECURE_BOOT_KEY_COUNT] = {
  {
    .SecureBootKeyName = L"Microsoft Plus 3rd Party Plus Windows On Andromeda",
    .KekPtr            = mKekDefault,
    .KekSize           = sizeof (mKekDefault),
    .DbPtr             = mDbDefault,
    .DbSize            = sizeof (mDbDefault),
    .DbxPtr            = mDbxDefault,
    .DbxSize           = sizeof (mDbxDefault),
    .DbtPtr            = NULL,
    .DbtSize           = 0,
  }
};

/**
  Interface to fetch platform Secure Boot Certificates, each payload
  corresponds to a designated set of db, dbx, dbt, KEK, PK.

  @param[in]  Keys        Pointer to hold the returned sets of keys. The
                          returned buffer will be treated as CONST and
                          permanent pointer. The consumer will NOT free
                          the buffer after use.
  @param[in]  KeyCount    The number of sets available in the returned Keys.

  @retval     EFI_SUCCESS             The Keys are properly fetched.
  @retval     EFI_INVALID_PARAMETER   Inputs have NULL pointers.
  @retval     Others                  Something went wrong. Investigate further.
**/
EFI_STATUS
EFIAPI
GetPlatformKeyStore (
  OUT SECURE_BOOT_PAYLOAD_INFO  **Keys,
  OUT UINT8                     *KeyCount
  )
{
  if ((Keys == NULL) || (KeyCount == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *Keys     = gSecureBootPayload;
  *KeyCount = gSecureBootPayloadCount;

  return EFI_SUCCESS;
}

/**
  The constructor gets the secure boot platform keys populated.

  @retval EFI_SUCCESS     The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
SecureBootKeyStoreLibConstructor (
  VOID
  )
{
  EFI_STATUS                    Status;
  UINTN                         DataSize;
  EFI_SIGNATURE_LIST            *SigListBuffer = NULL;
  SECURE_BOOT_CERTIFICATE_INFO  TempInfo       = {
    .Data     = mDevelopmentPlatformKeyCertificate,
    .DataSize = sizeof (mDevelopmentPlatformKeyCertificate)
  };

  //
  // First, we must build the PK buffer with the correct data.
  //
  Status = SecureBootCreateDataFromInput (&DataSize, &SigListBuffer, 1, &TempInfo);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "%a - Failed to build PK payload!\n", __FUNCTION__));
    ASSERT (FALSE);
  }

  mSecureBootPayload[0].PkPtr  = SigListBuffer;
  mSecureBootPayload[0].PkSize = DataSize;

  gSecureBootPayload      = mSecureBootPayload;
  gSecureBootPayloadCount = mSecureBootPayloadCount;

  return EFI_SUCCESS;
}

/**
  Destructor of SecureBootKeyStoreLib, to free any allocated resources.

  @retval EFI_SUCCESS   The destructor completed successfully.
  @retval Other value   The destructor did not complete successfully.

**/
EFI_STATUS
EFIAPI
SecureBootKeyStoreLibDestructor (
  VOID
  )
{
  VOID  *SigListBuffer;

  // This should be initialized from constructor, so casting here is fine
  SigListBuffer = (VOID *)mSecureBootPayload[0].PkPtr;
  if (SigListBuffer != NULL) {
    FreePool (SigListBuffer);
  }

  return EFI_SUCCESS;
}
