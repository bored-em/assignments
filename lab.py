# This program demonstrate how to do AESGCM encryption and decryption.
import os
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

def encrypt(nonce, data, aa):
    print('\nEncrypting ...')
    ciphertext = aesgcm.encrypt(nonce, data, aa)
    # The output is ciphertext + tag
    print(f"data: {data}, leng(data): {len(data)}")
    print(f"aa: {aa}, len(aa): {len(aa)}")
    print(f"nonce: {nonce.hex()}")
    print(f"Ciphertext: {ciphertext.hex()}, len(ciphertext): {len(ciphertext)}, 16-bit tag: {ciphertext[-16:].hex()}")
    return ciphertext

def decrypt(nonce, ciphertext, aa):
    print('\nDecrypting ...')
    print(f"aa: {aa}, len(aa): {len(aa)}")
    print(f"nonce: {nonce.hex()}")
    print(f"Ciphertext: {ciphertext.hex()}, len(ciphertext): {len(ciphertext)}, 16-bit tag: {ciphertext[-16:].hex()}")
    try:
        decrypted_data = aesgcm.decrypt(nonce, ciphertext, aa)
        print(f"Decrypted: {decrypted_data.decode()}")
    except Exception as e:
        print("Decryption failed: Tag verification failed")
    return decrypted_data
    
# 1. Generate a random 256-bit key (32 bytes)
key = AESGCM.generate_key(bit_length=256)
aesgcm = AESGCM(key)

# 2. Data and Nonce (IV)
data = b"A confidential message"
# GCM recommended nonce size is 96 bits (12 bytes)
nonce = os.urandom(12) 
# Associated data: authenticated but not encrypted
associated_data = b"Header Info: source='encryptor', destination='decryptor', mode='GCM' " 

# 3. Normal encryption/decryption
print(f'normal encryption and decryption')
ciphertext = encrypt(nonce, data, associated_data)
decrypted_data = decrypt(nonce, ciphertext, associated_data)
print('\n')

"""

#trail #0
print(f'Trial #0: encryption and decryption using different nonce')
print(f'A new nonce with the same key and data should generate different ciphertext.')

new_nonce = os.urandom(12)
ciphertext = encrypt(new_nonce, data, associated_data)
decrypted_data = decrypt(new_nonce, ciphertext, associated_data)


#trail #1
print(f'Trial #1: encryption and decryption using different associated data')
print("This should generate a 'Tag verification failed' error")

associated_data2 = b"Header Info: source='xyz', destination='decryptor', mode='GCM' "
ciphertext = encrypt(nonce, data, associated_data)
decrypted_data = decrypt(nonce, ciphertext, associated_data2)


#trail #2
print(f'Trial #2: changing the ciphertext')
print("This should generate a 'Tag verification failed' error")

ciphertext = encrypt(nonce, data, associated_data)
modified_ciphertext = b'\xff' + ciphertext[1:]
print(f"changed ciphertext: {modified_ciphertext.hex()}")
decrypted_data = decrypt(nonce, modified_ciphertext, associated_data)


#trail #3
print(f'Trial #3: changing the tag of the ciphertext')
print("This should generate a 'Tag verification failed' error")

ciphertext = encrypt(nonce, data, associated_data)
modified_ciphertext = ciphertext[:-1] + b'\xff'
print(f"modified ciphertext with changed tag: {modified_ciphertext.hex()}")
decrypted_data = decrypt(nonce, modified_ciphertext, associated_data)


#trail #4
print(f'Trial #4: changing the data and generating a new ciphertext')
print("This is a simulation of a man-in-the-middle attack and should NOT generate a 'Tag verification failed' error.")

data2 = b"xA confidential message"
nonce = os.urandom(12)
associated_data = b"Header Info: source='encryptor', destination='decryptor', mode='GCM' " 
ciphertext2 = encrypt(nonce, data2, associated_data)
print(f"changed data: {data2}, ciphertext.hex(): {ciphertext.hex()}")
decrypted_data = decrypt(nonce, ciphertext2, associated_data)
"""