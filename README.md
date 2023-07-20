Encryption and Decryption Program (with mapping files)

## Purpose

The purpose of this program is to provide a simple implementation of an encryption and decryption algorithm. It accepts a mapping file and an input file as inputs and generates encrypted or decrypted text as output, depending on the specified mode.


## Execution

To execute the program, use the following command format:

`make` to turn encrypt.c to an executable

`./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>`

Where:

<mappingfile> is the path to the mapping file that defines the encryption or decryption rules.
<encryption mode> specifies the desired mode of operation, which can be either "encryption" or "decryption".
<inputfile> is the input file that contains the text to be encrypted or decrypted.


## Example

To encrypt a file using the provided mapping and input files, you can use the following command:

`./encrypt -t mapping_encryption.csv -m encryption -i input_encryption.txt`

This command will encrypt the contents of "input_encryption.txt" using the rules defined in "mapping_encryption.csv" and output the encrypted text.

To decrypt a file, you can use a similar command but with the appropriate mapping and input files:

`./encrypt -t mapping_decryption.csv -m decryption -i input_decryption.txt`


## Files Included

The following files are included in this package:

encrypt.c: The C source code file that implements the encryption and decryption program.

test_encryption.sh: An executable bash script that contains the correct command to run the program for encryption using the provided mapping and input files in the sampletests folder. Running this script will produce the expected output, which is provided in "output_encryption.txt".

test_decryption.sh: An executable bash script that contains the correct command to run the program for decryption using the provided mapping and input files in the sampletests folder. Running this script will produce the expected output, which is provided in "output_decryption.txt".


sampletests folder:

input_encryption.txt: The input file containing the text to be encrypted.
output_encryption.txt: The expected output file for the encryption process.
input_decryption.txt: The input file containing the text to be decrypted.
output_decryption.txt: The expected output file for the decryption process.
mapping_encryption.csv: The mapping file used for the encryption process.
mapping_decryption.csv: The mapping file used for the decryption process.


## Usage Tips

Ensure that the mapping file provided (<mappingfile>) follows the correct format and contains the necessary rules for the encryption or decryption process.

Verify that the input file (<inputfile>) exists and contains the text to be encrypted or decrypted.

Use the appropriate encryption mode (-m) to specify whether the program should perform encryption or decryption.

Review the expected output files (output_encryption.txt and output_decryption.txt) to confirm the correctness of the program's output.


## References and Resources 

https://stackoverflow.com/questions/21592994/processing-command-line-arguments-allowing-for-any-order





 
