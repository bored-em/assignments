#servertcp.py
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

serverPort = 12000

serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)

print("The server is ready to receive")

while True:
    connectionSocket, addr = serverSocket.accept()
    
    message = connectionSocket.recv(1024)
    iv, ciphertext = message.split(b"||")
    file = input("what key file? ")
    with open(file, "rb") as key:
        k = key.read()
    dm = decrypt(iv, ciphertext, k)    
    print("decrypted message: ", dm.decode("utf-8"))
    nk = secrets.token_bytes(32)
    en_dm = encrypt(iv, dm, nk)
    en_nk = encrypt(iv, nk, k)
  
    connectionSocket.send(en_nk + b"||" + en_dm)
    connectionSocket.close() 

