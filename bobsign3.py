# script: BobSign3.py  
from cryptography.hazmat.primitives import hashes  
from cryptography.hazmat.primitives.asymmetric import padding  
from cryptography.hazmat.backends import default_backend  
from cryptography.hazmat.primitives import serialization  
import json  

filename = input('name of the private key file? ')  
message = input("What's the message to deliver? ")  
message = message.encode('utf-8')  
filename2 = input("What's the file with the receiver's public key? ")  

# Deserialization of Bob's private key  
with open(filename, 'rb') as private_file:  
    loaded_private_key = serialization.load_pem_private_key( 
    private_file.read(), password=None, backend=default_backend())  
 
with open(filename2, 'rb') as public_file: 
    loaded_public_key = serialization.load_pem_public_key( public_file.read(), 
    backend=default_backend())  
 
# Use PSS padding when signing data;  
# Use OAEP when encrypting data.  
padding_config = padding.OAEP( 
mgf=padding.MGF1(hashes.SHA256()),algorithm = hashes.SHA256(), 
label=None)  
 
ciphertext = loaded_public_key.encrypt(plaintext=message, 
padding=padding_config)  
 
padding_config2 = padding.PSS( mgf=padding.MGF1(hashes.SHA256()), 
salt_length=padding.PSS.MAX_LENGTH)  
 
private_key = loaded_private_key  
signature = private_key.sign( ciphertext, padding_config2, 
hashes.SHA256())  
 
signed_msg = { 'ciphertext': list(ciphertext), 'signature': 
list(signature),}  
outbound_msg_to_alice = json.dumps(signed_msg)  
 
# Save the signed message into a separate signed.dat file.  
with open('signed.dat', 'wb') as signed_file:  
    signed_file.write(outbound_msg_to_alice.encode())  
    message = str(signed_msg['ciphertext'])  
    signature = str(signed_msg['signature'])  
 
print("signed mesg and signature in 'signed.dat'.")  
print('ciphertext: ', message)  
print('signature: ', signature)