## Network Clock

### 1./How to install the network clock ?

To install the network clock project you will run this command in root project

    sudo make

This command will compile this project and install these command : nc_client, ts, server_nc.

### 2./ How to use <i>server_nc</i> command

If you run the network clock server you will run into yout terminal this command

    nc_server

Now the nc_server open a command line wich allows 2 command <i>time</i> and <i>set</i>

    root@pc:~# server_nc
    > time "format_date"
    > set "your_date"

The format that you can use with <i>time</i> command are describe below :

    DD/MM/YYYY
    DD/MM/YYYY hh:mm:ss
    MM/DD/YYYY
    MM/DD/YYYY hh:mm:ss
    hh:mm:ss

the format to set the time are describe below:
    
    %d-%m-%Y %H:%M:%S
    %d/%m/%Y %H:%M:%S
    %H:%M:%S

The default port of this server is 8080 and he used the TCP protocol to established communication links with nc_client

### 2./How to use the nc_client ?

The nc_client is used to return the current date of nc_server.
To use this command you will run this command

    user@pc:~# nc_client "@IPV4" "port" "format_date"

The format date are describe above in <i>"How to use the network clock ?"</i> part.

### 3./ How to uninstall this program ?

To uninstall this program you will execute this command

    sudo make clean