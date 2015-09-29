RSA
Bryan Johnson

The source you see here resembles my implementation of the RSA algorithm. The encryption and decryption is not 100% complete but the parts that make up the encryption / decryption are and work as expected (i.e. fermat test, mod inverse, generating prime numbers etc.). I used C++ as my language of choice and also used the proved BigInt class provided by a previous UA student. 

Notice you will see two different classes related to the big integer. To make grading easier, I decided to use the provided class by the previous UA student as a base class and have my own implementation derive from it. For example, I have a BigIntBase (other UA student's work) class and a BigInt (my own work) class. Everything in BigIntBase is NOT my work, everything in BigInt IS my work. 

Things that could be improved:
	generating prime numbers over 10 digits can take awhile
	encrypting and decrypting messages still needs some additional work (sorry)

Running my program. 
I also provided the program to run it via command line call 'rsa'. Below are example of how to run each part of the program:
./rsa 6 // generates a prime number with 6 digits
./rsa 412, 260 // tests the extended euclidean algorithm
./rsa 13, 300017, 9883 // tests the mod inverse function
./rsa 'e' 13, 2965068011, algo // encryption
./rsa 'd' 13, 2965068011, decrypt // decryption