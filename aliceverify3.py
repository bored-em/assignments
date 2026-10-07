# script: AliceVerify3.py  
from cryptography.hazmat.primitives import hashes  
from cryptography.hazmat.primitives.asymmetric import padding  
from cryptography.hazmat.backends import default_backend  
from cryptography.hazmat.primitives import serialization  
import hashlib  
import json  
from cryptography.exceptions import InvalidSignature  
 
# Read the signed_mesg file  
with open('signed.dat', 'rb') as signed_file:  
    inbound_msg_from_bob = signed_file.read()  
    signed_msg = json.loads(inbound_msg_from_bob)  
 
message = bytes(signed_msg['ciphertext'])  
signature = bytes(signed_msg['signature'])  
file = input("The receiver's private key? ")  
filename = input('name of the public key file? ')  
 
# Deserialization of Bob's public key  
with open(filename, 'rb') as public_file:  
    loaded_public_key = serialization.load_pem_public_key( 
    public_file.read(), backend=default_backend() )  
 
padding_config = padding.PSS( mgf=padding.MGF1(hashes.SHA256()), 
salt_length=padding.PSS.MAX_LENGTH)  
## NOTE: Errors of codes in the book  
public_key = loaded_public_key  
try:  
    public_key.verify( signature, message, padding_config, hashes.SHA256()) 
    print('Trust message')  
except InvalidSignature:  
    print('Do not trust message')  
 
with open(file, 'rb') as private_file:  
    loaded_private_key = serialization.load_pem_private_key( 
    private_file.read(), password=None, backend=default_backend())  
 
padding_config = padding.OAEP( 
mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), 
label=None, )  
 
#assert decrypted_by_private_key == plaintext  
decrypted_by_private_key = loaded_private_key.decrypt( 
ciphertext=message, padding=padding_config)  
print("decrypted message: ", decrypted_by_private_key)