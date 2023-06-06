# XOR Cipher
KEY = b"my_secret_key"  # This could be any bytes object


def xor_cypher(input_bytes, key=KEY):
    """
    Performs XOR encryption or decryption on the input bytes using the given key.

    Args:
        input_bytes (bytes): The input bytes to encrypt or decrypt.
        key (bytes, optional): The key to use for encryption or decryption. Defaults to KEY.

    Returns:
        bytes: The result of the XOR operation.

    Examples:
        >>> xor_cipher(b"Hello World")
        b'\x1c\x12\x1e\x1e\n\x15\x0c\x1f\x00\x1e\x0b'
    """
    return bytes([b ^ key[i % len(key)] for i, b in enumerate(input_bytes)])


def encrypt_data(data):
    """
    Encrypts the input data using the XOR cipher.

    Args:
        data (bytes): The input data to encrypt.

    Returns:
        bytes: The encrypted data.

    Examples:
        >>> encrypt_data(b"Hello World")
        b'\x1c\x12\x1e\x1e\n\x15\x0c\x1f\x00\x1e\x0b'
    """
    return xor_cypher(data)


def decrypt_data(data):
    """
    Decrypts the input data using the XOR cipher.

    Args:
        data (bytes): The input data to decrypt.

    Returns:
        bytes: The decrypted data.

    Examples:
        >>> decrypt_data(b'\x1c\x12\x1e\x1e\n\x15\x0c\x1f\x00\x1e\x0b')
        b"Hello World"
    """
    return xor_cypher(data)
