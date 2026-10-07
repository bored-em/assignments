#key.py
from cryptography.hazmat.primitives import hashes
import os

key = os.urandom(32) 

with open("key.bin", "wb") as f:
    f.write(key)

print("key generated and saved to key.bin")