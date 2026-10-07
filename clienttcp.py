#clienttcp.py
from socket import *

import secrets
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import (Cipher, algorithms, modes)
from cryptography.hazmat.primitives import padding
import os

def encrypt(iv, data, key):
    padder = padding.PKCS7(algorithms.AES.block_size).padder()
    padded_data = padder.update(data) + padder.finalize()
    cipher = Cipher(
        algorithms.AES(key),
        modes.CBC(iv),
        backend=default_backend())
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(padded_data) + encryptor.finalize()
    return ciphertext

def decrypt (iv, ciphertext, key):
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend()) 
    decryptor = cipher.decryptor() 
    padded_text = decryptor.update(ciphertext) + decryptor.finalize() 
    data = padded_text 
    unpadder = padding.PKCS7(algorithms.AES.block_size).unpadder() 
    unpadded_data = unpadder.update(data) + unpadder.finalize() 
    return unpadded_data 

serverName = '127.0.0.1'
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName,serverPort))

message = input("original message: ")
m = message.encode("utf-8")

with open("key.bin", "rb") as key:
    k = key.read()
    
iv = secrets.token_bytes(16)
ciphertext = encrypt(iv, m, k)

clientSocket.send(iv + b"||" + ciphertext)

recv_data = clientSocket.recv(1024)
en_nk, en_dm = recv_data.split(b"||")

new_key = decrypt(iv, en_nk, k)
dm = decrypt(iv, en_dm, new_key)
dm = dm.decode("utf-8")

if dm == message:
    print("decrypted message from server: ", dm)
    print("\n--messages match--\n")
else:
    print("\n--ERROR: messages do not match--\n")

clientSocket.close()

