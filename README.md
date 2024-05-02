# Device-Driver
A device driver that includes open, release, read, write and an iotcl command while using encryption and decryption

Steps on how to run the driver
1. Open the terminal and go to your desired folder
2. Run the command git clone https://github.com/CSC415-2023-Summer/csc415-device-driver- rorymcginnis1.git
3. then cd into csc415-device-driver-rorymcginnis1/Module
4. run make
5. run the command sudo insmod McGinnis_Rory_HW6_main.ko
6. move to the test folder using cd .. then cd Test
7. run make in the test folder
8. run the driver sudo ./McGinnis_Rory_HW6_main <text> <e/d>
(text is whatever string you would like to encrypt or decrypt and e or d is either encrypt or decrypt, if not e or d the driver will maintain the previous preferences for e/d
Example:
sudo ./McGinnis_Rory_HW6_main “hello world” “e”)
9. run sudo rmmod McGinnis_Rory_HW6_main
10. sudo dmesg (this step can be done at any point in time)
