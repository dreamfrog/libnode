# Copyright (c) 2013 Plenluno All rights reserved.

cmake_minimum_required(VERSION 2.8)

project(exts)

# options ----------------------------------------------------------------------

option(LIBNODE_USE_JSDP       "Use JSDP"       ON)
option(LIBNODE_USE_JSONRPC    "Use JSON-RPC"   ON)
option(LIBNODE_USE_RSA_CRYPTO "Use RSA Crypto" ON)

# build libraries --------------------------------------------------------------

include_directories(
    jsdp/include
    jsonrpc/include
    rsa_crypto/include
)

## jsdp
if(LIBNODE_USE_JSDP AND LIBNODE_USE_CRYPTO)
    add_subdirectory(jsdp)
endif(LIBNODE_USE_JSDP AND LIBNODE_USE_CRYPTO)

## jsonrpc
if(LIBNODE_USE_JSONRPC AND LIBNODE_USE_THREAD)
    add_subdirectory(jsonrpc)
endif(LIBNODE_USE_JSONRPC AND LIBNODE_USE_THREAD)

## rsa crypto
if(LIBNODE_USE_RSA_CRYPTO AND LIBNODE_USE_CRYPTO)
    add_subdirectory(rsa_crypto)
endif(LIBNODE_USE_RSA_CRYPTO AND LIBNODE_USE_CRYPTO)
