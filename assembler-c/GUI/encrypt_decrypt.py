# XOR Cipher
KEY = b"my_secret_key"  # This could be any bytes object


def xor_cypher(input_bytes, key=KEY):
    return bytes([b ^ key[i % len(key)] for i, b in enumerate(input_bytes)])


def encrypt_data(data):
    return xor_cypher(data)


def decrypt_data(data):
    return xor_cypher(data)
